/* File: main-gcu.c */

/*
 * File: main-gcu.c
 * Purpose: Support for "curses" systems
 *
 * Copyright (c) 1997 Ben Harrison, and others
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */


/*
 * This file helps Angband run on Unix/Curses machines.
 *
 *
 * To use this file, you must define "USE_GCU" in the Makefile.
 *
 *
 * Hack -- note that "angband.h" is included AFTER the #ifdef test.
 * This was necessary because of annoying "curses.h" silliness.
 *
 * Note that this file is not "intended" to support non-Unix machines,
 * nor is it intended to support VMS or other bizarre setups.
 *
 * Also, this package assumes that the underlying "curses" handles both
 * the "nonl()" and "cbreak()" commands correctly, see the "OPTION" below.
 *
 * This code should work with most versions of "curses" or "ncurses",
 * and the "main-ncu.c" file (and USE_NCU define) are no longer used.
 *
 * This file provides up to 4 term windows.
 *
 * This file will attempt to redefine the screen colors to conform to
 * standard Angband colors.  It will only do so if the terminal type
 * indicates that it can do so.  See the page:
 *
 *     http://www.umr.edu/~keldon/ang-patch/ncurses_color.html
 *
 * for information on this.
 *
 * Consider the use of "savetty()" and "resetty()".  XXX XXX XXX
 */


#include "angband.h"


#ifdef USE_GCU

/*
 * Include the proper "header" file
 */
#ifdef USE_NCURSES
# ifdef HAVE_STDBOOL_H
#  define NCURSES_ENABLE_STDBOOL_H 0
# endif

# include <ncurses.h>
#else
# include <curses.h>
#endif

/*
 * Try redefining the colors at startup.
 */
#define REDEFINE_COLORS


/*
 * Use POSIX terminal I/O
 */
#define USE_TPOSIX



/*
 * POSIX stuff
 */
#ifdef USE_TPOSIX
# include <termios.h>
#endif

/*
 * If you have errors relating to curs_set(), comment out the following line
 */
#define USE_CURS_SET

/*
 * OPTION: some machines lack "cbreak()"
 * On these machines, we use an older definition
 */
/* #define cbreak() crmode() */


/*
 * OPTION: some machines cannot handle "nonl()" and "nl()"
 * On these machines, we can simply ignore those commands.
 */
/* #define nonl() */
/* #define nl() */

/*
 * Save the "normal" and "angband" terminal settings
 */

#ifdef USE_TPOSIX

static struct termios  norm_termios;
static struct termios  game_termios;

#endif


/*
 * Information about a term
 */
typedef struct term_data
{
	term t;                 /* All term info */
	WINDOW *win;            /* Pointer to the curses window */
} term_data;

/* Max number of windows on screen */
#define MAX_TERM_DATA 4

/* Information about our windows */
static term_data data[MAX_TERM_DATA];


/* Number of initialized "term" structures */
static int active = 0;


#ifdef A_COLOR

/*
 * Hack -- define "A_BRIGHT" to be "A_BOLD", because on many
 * machines, "A_BRIGHT" produces ugly "inverse" video.
 */
#ifndef A_BRIGHT
# define A_BRIGHT A_BOLD
#endif

/*
 * Software flag -- we are allowed to use color
 */
static int can_use_color = FALSE;

/*
 * Software flag -- we are allowed to change the colors
 */
static int can_fix_color = FALSE;

/*
 * Simple Angband to Curses color conversion table
 */
static int colortable[BASIC_COLORS];

/* Screen info: use one big Term 0, or other subwindows? */
static bool use_big_screen = FALSE;
static bool bold_extended = FALSE;

/*
 * Background color we should draw with; either BLACK or DEFAULT
 */
static int bg_color = COLOR_BLACK;


#define PAIR_WHITE 0
#define PAIR_RED 1
#define PAIR_GREEN 2
#define PAIR_YELLOW 3
#define PAIR_BLUE 4
#define PAIR_MAGENTA 5
#define PAIR_CYAN 6
#define PAIR_BLACK 7

#endif


#ifdef USE_GRAPHICS

static bool use_blocks = FALSE;

#endif

/*
 * Place the "keymap" into its "normal" state
 */
static void keymap_norm(void)
{
#ifdef USE_TPOSIX

	/* restore the saved values of the special chars */
	(void)tcsetattr(0, TCSAFLUSH, &norm_termios);
#endif
}


/*
 * Place the "keymap" into the "game" state
 */
static void keymap_game(void)
{
#ifdef USE_TPOSIX
	/* Set the game's termios settings */
	(void)tcsetattr(0, TCSAFLUSH, &game_termios);
#endif
}


/*
 * Save the normal keymap
 */
static void keymap_norm_prepare(void)
{
#ifdef USE_TPOSIX
	/* Restore the normal termios settings */
	tcgetattr(0, &norm_termios);
#endif
}


/*
 * Save the keymaps (normal and game)
 */
static void keymap_game_prepare(void)
{
#ifdef USE_TPOSIX
	/* Save the current termios settings */
	tcgetattr(0, &game_termios);

	/* Force "Ctrl-C" to interupt */
	game_termios.c_cc[VINTR] = (char)3;

	/* Force "Ctrl-Z" to suspend */
	game_termios.c_cc[VSUSP] = (char)26;

	/* Hack -- Leave "VSTART/VSTOP" alone */

	/* Disable the standard control characters */
	game_termios.c_cc[VQUIT] = (char)-1;
	game_termios.c_cc[VERASE] = (char)-1;
	game_termios.c_cc[VKILL] = (char)-1;
	game_termios.c_cc[VEOF] = (char)-1;
	game_termios.c_cc[VEOL] = (char)-1;

	/* Normally, block until a character is read */
	game_termios.c_cc[VMIN] = 1;
	game_termios.c_cc[VTIME] = 0;

	/* Turn off flow control (enable ^S) */
	game_termios.c_iflag &= ~IXON;
#endif
}


/*
 * Suspend/Resume
 */
static errr Term_xtra_gcu_alive(int v)
{
	/* Suspend */
	if (!v)
	{
		int x, y;

		/* Go to normal keymap mode */
		keymap_norm();

		/* Restore modes */
		nocbreak();
		echo();
		nl();

		/* Hack -- make sure the cursor is visible */
		Term_xtra(TERM_XTRA_SHAPE, 1);

		/* Flush the curses buffer */
		refresh();

		/* Get current cursor position */
		getyx(stdscr, y, x);

		/* Move the cursor to bottom right corner */
		mvcur(y, x, LINES - 1, 0);

		/* Exit curses */
		endwin();

		/* Flush the output */
		fflush(stdout);
	}

	/* Resume */
	else
	{
		/* Refresh */
		/* (void)touchwin(curscr); */
		/* (void)wrefresh(curscr); */

		/* Restore the settings */
		cbreak();
		noecho();
		nonl();

		/* Go to angband keymap mode */
		keymap_game();
	}

	/* Success */
	return 0;
}




/*
 * Init the "curses" system
 */
static void Term_init_gcu(term *t)
{
	term_data *td = (term_data *)(t->data);

	/*
	 * This is necessary to keep the first call to getch()
	 * from clearing the screen
	 */
	wrefresh(stdscr);

	/* Count init's, handle first */
	if (active++ != 0) return;

	/* Erase the window */
	wclear(td->win);

	/* Reset the cursor */
	wmove(td->win, 0, 0);

	/* Flush changes */
	wrefresh(td->win);

	/* Game keymap */
	keymap_game();
}


/*
 * Nuke the "curses" system
 */
static void Term_nuke_gcu(term *t)
{
	int x, y;
	term_data *td = (term_data *)(t->data);

	/* Delete this window */
	delwin(td->win);

	/* Count nuke's, handle last */
	if (--active != 0) return;

	/* Hack -- make sure the cursor is visible */
	Term_xtra(TERM_XTRA_SHAPE, 1);

#ifdef A_COLOR
	/* Reset colors to defaults */
	start_color();
#endif

	/* Get current cursor position */
	getyx(stdscr, y, x);

	/* Move the cursor to bottom right corner */
	mvcur(y, x, LINES - 1, 0);

	/* Flush the curses buffer */
	refresh();

	/* Exit curses */
	endwin();

	/* Flush the output */
	fflush(stdout);

	/* Normal keymap */
	keymap_norm();
}


/*
 * For a given term number (i) set the upper left corner (x, y) and the
 * correct dimensions. Terminal layout: 0|2
 *                                      1|3
 */
void get_gcu_term_size(int i, int *rows, int *cols, int *y, int *x)
{
	if (use_big_screen && i == 0)
	{
		*rows = LINES;
		*cols = COLS;
		*y = *x = 0;
	}
	else if (use_big_screen)
	{
		*rows = *cols = *y = *x = 0;
	}
	else if (i == 0)
	{
		*rows = 24;
		*cols = 80;
		*y = *x = 0;
	}
	else if (i == 1)
	{
		*rows = LINES - 25;
		*cols = 80;
		*y = 25;
		*x = 0;
	}
	else if (i == 2)
	{
		*rows = 24;
		*cols = COLS - 81;
		*y = 0;
		*x = 81;
	}
	else if (i == 3)
	{
		*rows = LINES - 25;
		*cols = COLS - 81;
		*y = 25;
		*x = 81;
	}
	else
	{
		*rows = *cols = *y = *x = 0;
	}
}

/*
 * Process events, with optional wait
 */
static errr Term_xtra_gcu_event(int v)
{
	int i, k;

	/* Wait */
	if (v)
	{
		/* Paranoia -- Wait for it */
		nodelay(stdscr, FALSE);

		/* Get a keypress */
		i = getch();

		/* Mega-Hack -- allow graceful "suspend" */
		for (k = 0; (k < 10) && (i == ERR); k++) i = getch();

		/* Broken input is special */
		if (i == ERR) exit_game_panic();
		if (i == EOF) exit_game_panic();
	}

	/* Do not wait */
	else
	{
		/* Do not wait for it */
		nodelay(stdscr, TRUE);

		/* Check for keypresses */
		i = getch();

		/* Wait for it next time */
		nodelay(stdscr, FALSE);

		/* None ready */
		if (i == ERR) return (1);
		if (i == EOF) return (1);
	}

	/* Enqueue the keypress */
	Term_keypress(i);

	/* Success */
	return (0);
}

int scale_color(int i, int j, int scale)
{
	return (angband_color_table[i][j] * (scale - 1) + 127) / 255;
}

int create_color(int i, int scale)
{
	int r = scale_color(i, 1, scale);
	int g = scale_color(i, 2, scale);
	int b = scale_color(i, 3, scale);
	int rgb = 16 + scale * scale * r + scale * g + b;

	/* In the case of white and black we need to use the ANSI colors */
	if (r == g && g == b)
	{
		if (b == 0) rgb = 0;
		if (b == scale) rgb = 15;
	}

	return rgb;
}


/*
 * React to changes
 */
static errr Term_xtra_gcu_react(void)
{
#ifdef A_COLOR

	/* Cannot handle color redefinition */
	if (!can_fix_color) return (0);

	if (COLORS == 256 || COLORS == 88)
	{
		/* If we have more than 16 colors, find the best matches. These numbers
		 * correspond to xterm/rxvt's builtin color numbers--they do not
		 * correspond to curses' constants OR with curses' color pairs.
		 *
		 * XTerm has 216 (6*6*6) RGB colors, with each RGB setting 0-5.
		 * RXVT has 64 (4*4*4) RGB colors, with each RGB setting 0-3.
		 *
		 * Both also have the basic 16 ANSI colors, plus some extra grayscale
		 * colors which we do not use.
		 */
		int i;
		int scale = COLORS == 256 ? 6 : 4;

		for (i = 0; i < BASIC_COLORS; i++)
		{
			int fg = create_color(i, scale);
			init_pair(i + 1, fg, bg_color);
			if (bold_extended)
				colortable[i] = COLOR_PAIR(i + 1) | A_BRIGHT;
			else
				colortable[i] = COLOR_PAIR(i + 1);
		}
	}
#endif

	return 0;
}


/*
 * Handle a "special request"
 */
static errr Term_xtra_gcu(int n, int v)
{
	term_data *td = (term_data *)(Term->data);

	/* Analyze the request */
	switch (n)
	{
		/* Clear screen */
		case TERM_XTRA_CLEAR:
		touchwin(td->win);
		(void)wclear(td->win);
		return (0);

		/* Make a noise */
		case TERM_XTRA_NOISE:
		(void)write(1, "\007", 1);
		return (0);

		/* Flush the Curses buffer */
		case TERM_XTRA_FRESH:
		(void)wrefresh(td->win);
		return (0);

#ifdef USE_CURS_SET

		/* Change the cursor visibility */
		case TERM_XTRA_SHAPE:
		curs_set(v);
		return (0);

#endif

		/* Suspend/Resume curses */
		case TERM_XTRA_ALIVE:
		return (Term_xtra_gcu_alive(v));

		/* Process events */
		case TERM_XTRA_EVENT:
		return (Term_xtra_gcu_event(v));

		/* Flush events */
		case TERM_XTRA_FLUSH:
		while (!Term_xtra_gcu_event(FALSE));
		return (0);

		/* Delay */
		case TERM_XTRA_DELAY:
		usleep(1000 * v);
		return (0);

		/* React to events */
		case TERM_XTRA_REACT:
		Term_xtra_gcu_react();
		return (0);
	}

	/* Unknown event */
	return 1;
}


/*
 * Actually MOVE the hardware cursor
 */
static errr Term_curs_gcu(int x, int y)
{
	term_data *td = (term_data *)(Term->data);
	wmove(td->win, y, x);
	return 0;
}


/*
 * Erase a grid of space
 * Hack -- try to be "semi-efficient".
 */
static errr Term_wipe_gcu(int x, int y, int n)
{
	term_data *td = (term_data *)(Term->data);

	wmove(td->win, y, x);

	if (x + n >= td->t.wid)
	{
		/* Clear to end of line */
		wclrtoeol(td->win);
	}

	/* Clear some characters */
	else
	{
		while (n-- > 0) waddch(td->win, ' ');
	}

	return 0;
}


/*
 * Place some text on the screen using an attribute
 */
static errr Term_text_gcu(int x, int y, int n, byte a, const char *s)
{
	term_data *td = (term_data *)(Term->data);

	int i;
#ifdef USE_GRAPHICS
	int pic;
#endif

#ifdef A_COLOR
	/* Set the color */
	if (can_use_color) wattrset(td->win, colortable[a & 0x0F]);
#endif

	/* Move the cursor */
	wmove(td->win, y, x);

	/* Draw each character */
	for (i = 0; i < n; i++)
	{
#ifdef USE_GRAPHICS
		/* Special characters? */
		if (use_blocks)
		{

			/* Determine picture to use */
			if (s[i] == '#')
			{
				/* Walls */
				pic = ACS_CKBOARD;

				/*
				 *  Note that veins are '#' as well now.
				 *  Trees are '%' now - and this looks bad when redefined.
				 */
			}
			else
			{
			        pic = s[i];
			}

			/* Draw the picture */
			waddch(td->win, pic);

			/* Next character */
			continue;
		}
#endif

		/* Draw a normal character */
		waddch(td->win, s[i]);
	}

	/* Success */
	return (0);
}

/*
 * Create a window for the given "term_data" argument.
 *
 * Assumes legal arguments.
 */
static errr term_data_init_gcu(term_data *td, int rows, int cols, int y, int x)
{
	term *t = &td->t;

	/* Create new window */
	td->win = newwin(rows, cols, y, x);

	/* Check for failure */
	if (!td->win)
		quit("Failed to setup curses window.");

	/* Initialize the term */
	term_init(t, cols, rows, 256);

	/* Avoid bottom right corner */
	t->icky_corner = TRUE;

	/* Erase with "white space" */
	t->attr_blank = TERM_WHITE;
	t->char_blank = ' ';

	/* Set some hooks */
	t->init_hook = Term_init_gcu;
	t->nuke_hook = Term_nuke_gcu;

	/* Set some more hooks */
	t->text_hook = Term_text_gcu;
	t->wipe_hook = Term_wipe_gcu;
	t->curs_hook = Term_curs_gcu;
	t->xtra_hook = Term_xtra_gcu;

	/* Save the data */
	t->data = td;

	/* Activate it */
	Term_activate(t);

	/* Success */
	return (0);
}

static void hook_quit(const char *str)
{
	endwin();
}

/*
 * Prepare "curses" for use by the file "z-term.c"
 *
 * Installs the "hook" functions defined above, and then activates
 * the main screen "term", which clears the screen and such things.
 *
 * Someone should really check the semantics of "initscr()"
 */
errr init_gcu(int argc, char **argv)
{
	int i;

	int rows, cols, y, x;
	int num_term = MAX_TERM_DATA, next_win = 0;

	/* Parse args */
	for (i = 1; i < argc; i++)
	{
		if (prefix(argv[i], "-b"))
			use_big_screen = TRUE;
		else
			plog_fmt("Ignoring option: %s", argv[i]);
	}


	/* Extract the normal keymap */
	keymap_norm_prepare();


	/* Initialize */
	if (initscr() == NULL) return (-1);

	/* Activate hooks */
	quit_aux = hook_quit;

	/* Require standard size screen */
	if (LINES < 24 || COLS < 80)
		quit("Angband needs at least an 80x24 'curses' screen");

#ifdef USE_GRAPHICS
	/* Set graphics flag */
	use_graphics = FALSE;

	/* Use the graphical wall tiles? */
	use_blocks = arg_graphics;
#endif

#ifdef A_COLOR

	/*** Init the Color-pairs and set up a translation table ***/

	/* Do we have color, and enough color, available? */
	can_use_color = ((start_color() != ERR) && has_colors() &&
	                 (COLORS >= 8) && (COLOR_PAIRS >= 8));

#ifdef REDEFINE_COLORS
	/* Can we change colors? */
	can_fix_color = (can_use_color && can_change_color() &&
	                 (COLORS >= 16) && (COLOR_PAIRS > 8));
#endif

	/* Attempt to use customized colors */
	if (can_fix_color)
	{
		/* Prepare the color pairs */
		for (i = 1; i <= 8; i++)
		{
			/* Reset the color */
			if (init_pair(i, i - 1, 0) == ERR)
			{
				quit("Color pair init failed");
			}

			/* Set up the colormap */
			colortable[i - 1] = (COLOR_PAIR(i) | A_NORMAL);
			colortable[i + 7] = (COLOR_PAIR(i) | A_BRIGHT);
		}

		/* XXX XXX XXX Take account of "gamma correction" */

		/* Prepare the "Angband Colors" */
		Term_xtra_gcu_react();
	}

	/* Attempt to use colors */
	if (can_use_color)
	{
		/* Prepare the color pairs */
		/* PAIR_WHITE (pair 0) is *always* WHITE on BLACK */
		init_pair(PAIR_RED, COLOR_RED, bg_color);
		init_pair(PAIR_GREEN, COLOR_GREEN, bg_color);
		init_pair(PAIR_YELLOW, COLOR_YELLOW, bg_color);
		init_pair(PAIR_BLUE, COLOR_BLUE, bg_color);
		init_pair(PAIR_MAGENTA, COLOR_MAGENTA, bg_color);
		init_pair(PAIR_CYAN, COLOR_CYAN, bg_color);
		init_pair(PAIR_BLACK, COLOR_BLACK, bg_color);

		/* Prepare the colors */
		colortable[TERM_DARK]     = (COLOR_PAIR(PAIR_BLACK));
		colortable[TERM_WHITE]    = (COLOR_PAIR(PAIR_WHITE) | A_BRIGHT);
		colortable[TERM_SLATE]    = (COLOR_PAIR(PAIR_WHITE));
		colortable[TERM_ORANGE]   = (COLOR_PAIR(PAIR_YELLOW) | A_BRIGHT);
		colortable[TERM_RED]      = (COLOR_PAIR(PAIR_RED));
		colortable[TERM_GREEN]    = (COLOR_PAIR(PAIR_GREEN));
		colortable[TERM_BLUE]     = (COLOR_PAIR(PAIR_BLUE));
		colortable[TERM_UMBER]    = (COLOR_PAIR(PAIR_YELLOW));
		colortable[TERM_L_DARK]   = (COLOR_PAIR(PAIR_BLACK) | A_BRIGHT);
		colortable[TERM_L_WHITE]  = (COLOR_PAIR(PAIR_WHITE));
		colortable[TERM_L_PURPLE] = (COLOR_PAIR(PAIR_MAGENTA));
		colortable[TERM_YELLOW]   = (COLOR_PAIR(PAIR_YELLOW) | A_BRIGHT);
		colortable[TERM_L_RED]    = (COLOR_PAIR(PAIR_MAGENTA) | A_BRIGHT);
		colortable[TERM_L_GREEN]  = (COLOR_PAIR(PAIR_GREEN) | A_BRIGHT);
		colortable[TERM_L_BLUE]   = (COLOR_PAIR(PAIR_BLUE) | A_BRIGHT);
		colortable[TERM_L_UMBER]  = (COLOR_PAIR(PAIR_YELLOW));

		colortable[TERM_PURPLE]      = (COLOR_PAIR(PAIR_MAGENTA));
		colortable[TERM_VIOLET]      = (COLOR_PAIR(PAIR_MAGENTA));
		colortable[TERM_TEAL]        = (COLOR_PAIR(PAIR_CYAN));
		colortable[TERM_MUD]         = (COLOR_PAIR(PAIR_YELLOW));
		colortable[TERM_L_YELLOW]    = (COLOR_PAIR(PAIR_YELLOW | A_BRIGHT));
		colortable[TERM_MAGENTA]     = (COLOR_PAIR(PAIR_MAGENTA | A_BRIGHT));
		colortable[TERM_L_TEAL]      = (COLOR_PAIR(PAIR_CYAN | A_BRIGHT));
		colortable[TERM_L_VIOLET]    = (COLOR_PAIR(PAIR_MAGENTA | A_BRIGHT));
		colortable[TERM_L_PINK]      = (COLOR_PAIR(PAIR_MAGENTA | A_BRIGHT));
		colortable[TERM_MUSTARD]     = (COLOR_PAIR(PAIR_YELLOW));
		colortable[TERM_BLUE_SLATE]  = (COLOR_PAIR(PAIR_BLUE));
		colortable[TERM_DEEP_L_BLUE] = (COLOR_PAIR(PAIR_BLUE));
	}
#endif


	/*** Low level preparation ***/

	/* Paranoia -- Assume no waiting */
	nodelay(stdscr, FALSE);

	/* Prepare */
	cbreak();
	noecho();
	nonl();

	/* Extract the game keymap */
	keymap_game_prepare();


	/*** Now prepare the term(s) ***/

	for (i = 0; i < num_term; i++)
	{
		if (use_big_screen && i > 0) break;

		/* Get the terminal dimensions; if the user asked for a big screen
		 * then we'll put the whole screen in term 0; otherwise we'll divide
		 * it amongst the available terms */
		get_gcu_term_size(i, &rows, &cols, &y, &x);

		/* Skip non-existant windows */
		if (rows <= 0 || cols <= 0) continue;

		/* Create a term */
		term_data_init_gcu(&data[next_win], rows, cols, y, x);

		/* Remember the term */
		angband_term[next_win] = &data[next_win].t;

		/* One more window */
		next_win++;
	}

	/* Activate the "Angband" window screen */
	Term_activate(&data[0].t);

	/* Remember the active screen */
	term_screen = &data[0].t;

	/* Success */
	return (0);
}

#endif /* USE_GCU */
