/* File: main-gcu.c */

/*
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
 * Hack -- play games with "bool"
 */
#undef bool

/*
 * Include the proper "header" file
 */
#ifdef USE_NCURSES
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

static bool           split_window=TRUE;

/*
 * Information about a term
 */
typedef struct term_data term_data;

struct term_data
{
	term t;                 /* All term info */

	WINDOW *win;            /* Pointer to the curses window */
};

/* Max number of windows on screen */
#define MAX_TERM_DATA 4

/* minimum dimensions to split into multiple windows */
#define MIN_ROWS_SPLIT 30
#define MIN_COLS_SPLIT 105

/* Information about our windows */
static term_data data[MAX_TERM_DATA];


/*
 * Hack -- Number of initialized "term" structures
 */
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
static int colortable[16];

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

	/* restore the saved values of the special chars */
	(void)tcsetattr(0, TCSAFLUSH, &game_termios);

#endif

}


/*
 * Save the normal keymap
 */
static void keymap_norm_prepare(void)
{

#ifdef USE_TPOSIX

	/* Get the normal keymap */
	tcgetattr(0, &norm_termios);

#endif

}


/*
 * Save the keymaps (normal and game)
 */
static void keymap_game_prepare(void)
{

#ifdef USE_TPOSIX

	/* Acquire the current mapping */
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
		/* Go to normal keymap mode */
		keymap_norm();

		/* Restore modes */
		nocbreak();
		echo();
		nl();

		/* Hack -- make sure the cursor is visible */
		Term_xtra(TERM_XTRA_SHAPE, 1);

		/* Flush the curses buffer */
		(void)refresh();

#ifdef SPECIAL_BSD
		/* this moves curses to bottom right corner */
		mvcur(curscr->cury, curscr->curx, LINES - 1, 0);
#else
		/* this moves curses to bottom right corner */
		mvcur(curscr->_cury, curscr->_curx, LINES - 1, 0);
#endif

		/* Exit curses */
		endwin();

		/* Flush the output */
		(void)fflush(stdout);
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
	return (0);
}




/*
 * Init the "curses" system
 */
static void Term_init_gcu(term *t)
{
	term_data *td = (term_data *)(t->data);

	/* Count init's, handle first */
	if (active++ != 0) return;

	/* Erase the window */
	(void)wclear(td->win);

	/* Reset the cursor */
	(void)wmove(td->win, 0, 0);

	/* Flush changes */
	(void)wrefresh(td->win);

	/* Game keymap */
	keymap_game();
}


/*
 * Nuke the "curses" system
 */
static void Term_nuke_gcu(term *t)
{
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

#ifdef SPECIAL_BSD
	/* This moves curses to bottom right corner */
	mvcur(curscr->cury, curscr->curx, LINES - 1, 0);
#else
	/* This moves curses to bottom right corner */
	mvcur(curscr->_cury, curscr->_curx, LINES - 1, 0);
#endif

	/* Flush the curses buffer */
	(void)refresh();

	/* Exit curses */
	endwin();

	/* Flush the output */
	(void)fflush(stdout);

	/* Normal keymap */
	keymap_norm();
}




#ifdef USE_GETCH

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

#else	/* USE_GETCH */

/*
 * Process events (with optional wait)
 */
static errr Term_xtra_gcu_event(int v)
{
	int i, k;

	char buf[2];

	/* Wait */
	if (v)
	{
		/* Wait for one byte */
		i = read(0, buf, 1);

		/* Hack -- Handle bizarre "errors" */
		if ((i <= 0) && (errno != EINTR)) exit_game_panic();
	}

	/* Do not wait */
	else
	{
		/* Get the current flags for stdin */
		k = fcntl(0, F_GETFL, 0);

		/* Oops */
		if (k < 0) return (1);

		/* Tell stdin not to block */
		if (fcntl(0, F_SETFL, k | O_NONBLOCK) < 0) return (1);

		/* Read one byte, if possible */
		i = read(0, buf, 1);

		/* Replace the flags for stdin */
		if (fcntl(0, F_SETFL, k)) return (1);
	}

	/* Ignore "invalid" keys */
	if ((i != 1) || (!buf[0])) return (1);

	/* Enqueue the keypress */
	Term_keypress(buf[0]);

	/* Success */
	return (0);
}

#endif	/* USE_GETCH */

/*
 * React to changes
 */
static errr Term_xtra_gcu_react(void)
{
#ifdef A_COLOR

	int i;

	/* Cannot handle color redefinition */
	if (!can_fix_color) return (0);

	/* Set the colors */
	for (i = 0; i < 16; i++)
	{
		/* Set one color (note scaling) */
		init_color(i, angband_color_table[i][1] * 1000 / 255,
		              angband_color_table[i][2] * 1000 / 255,
		              angband_color_table[i][3] * 1000 / 255);
	}

#endif

	/* Success */
	return (0);
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

	/* Unknown */
	return (1);
}


/*
 * Actually MOVE the hardware cursor
 */
static errr Term_curs_gcu(int x, int y)
{
	term_data *td = (term_data *)(Term->data);

	/* Literally move the cursor */
	wmove(td->win, y, x);

	/* Success */
	return (0);
}


/*
 * Erase a grid of space
 * Hack -- try to be "semi-efficient".
 */
static errr Term_wipe_gcu(int x, int y, int n)
{
	term_data *td = (term_data *)(Term->data);

	/* Place cursor */
	wmove(td->win, y, x);

	/* Clear to end of line */
	if (x + n >= td->t.wid)
	{
		wclrtoeol(td->win);
	}

	/* Clear some characters */
	else
	{
		while (n-- > 0) waddch(td->win, ' ');
	}

	/* Success */
	return (0);
}


/*
 * Place some text on the screen using an attribute
 */
static errr Term_text_gcu(int x, int y, int n, byte a, cptr s)
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
 */
static errr term_data_init_gcu(term_data *td, int rows, int cols, int y, int x, int i)
{
	term *t = &td->t;

	/* Check window size */
	if (rows <= 0 || cols <= 0) return (0);

	/* Create new window */
	td->win = newwin(rows, cols, y, x);

	/* Check for failure */
	if (!td->win)
	{
		/* Error */
		quit("Failed to setup curses window.");
	}

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

	/* Reset map size if required */
	if (i == 0)
	{
		/* Mega-Hack -- no panel yet */
		panel_row_min = 0;
		panel_row_max = 0;
		panel_col_min = 0;
		panel_col_max = 0;

		/* Reset the panels */
		map_panel_size();
	}

	/* Success */
	return (0);
}


/*
 * Prepare "curses" for use by the file "term.c"
 *
 * Installs the "hook" functions defined above, and then activates
 * the main screen "term", which clears the screen and such things.
 *
 * Someone should really check the semantics of "initscr()"
 */
errr init_gcu(int argc, char *argv[])
{
	int i;

	int num_term = MAX_TERM_DATA, next_win = 0;

	/* Parse args */
	for (i = 1; i < argc; i++)
	{
		if (prefix(argv[i], "-x"))
		{
		        split_window=FALSE;
			continue;
		}

		plog_fmt("Ignoring option: %s", argv[i]);
	}


	/* Extract the normal keymap */
	keymap_norm_prepare();


	/* Initialize */
	if (initscr() == NULL) return (-1);


	/* Hack -- Require large screen, or Quit with message */
	i = ((LINES < 24) || (COLS < 80));
	if (i) quit("Angband needs an 80x24 'curses' screen");

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
	else if (can_use_color)
	{
		/* Color-pair 0 is *always* WHITE on BLACK */

		/* Prepare the color pairs */
		init_pair(1, COLOR_RED,     COLOR_BLACK);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
		init_pair(4, COLOR_BLUE,    COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_CYAN,    COLOR_BLACK);
		init_pair(7, COLOR_BLACK,   COLOR_BLACK);

		/* Prepare the "Angband Colors" -- Bright white is too bright */
		colortable[0] = (COLOR_PAIR(7) | A_NORMAL);	/* Black */
		colortable[1] = (COLOR_PAIR(0) | A_NORMAL);	/* White */
		colortable[2] = (COLOR_PAIR(6) | A_NORMAL);	/* Grey XXX */
		colortable[3] = (COLOR_PAIR(1) | A_BRIGHT);	/* Orange XXX */
		colortable[4] = (COLOR_PAIR(1) | A_NORMAL);	/* Red */
		colortable[5] = (COLOR_PAIR(2) | A_NORMAL);	/* Green */
		colortable[6] = (COLOR_PAIR(4) | A_NORMAL);	/* Blue */
		colortable[7] = (COLOR_PAIR(3) | A_NORMAL);	/* Umber */
		colortable[8] = (COLOR_PAIR(7) | A_BRIGHT);	/* Dark-grey XXX */
		colortable[9] = (COLOR_PAIR(6) | A_BRIGHT);	/* Light-grey XXX */
		colortable[10] = (COLOR_PAIR(5) | A_NORMAL);	/* Purple */
		colortable[11] = (COLOR_PAIR(3) | A_BRIGHT);	/* Yellow */
		colortable[12] = (COLOR_PAIR(5) | A_BRIGHT);	/* Light Red XXX */
		colortable[13] = (COLOR_PAIR(2) | A_BRIGHT);	/* Light Green */
		colortable[14] = (COLOR_PAIR(4) | A_BRIGHT);	/* Light Blue */
		colortable[15] = (COLOR_PAIR(3) | A_NORMAL);	/* Light Umber XXX */
	}

#endif


	/*** Low level preparation ***/

#ifdef USE_GETCH

	/* Paranoia -- Assume no waiting */
	nodelay(stdscr, FALSE);

#endif

	/* Prepare */
	cbreak();
	noecho();
	nonl();

	/* Extract the game keymap */
	keymap_game_prepare();


	/*** Now prepare the term(s) ***/

	if (!split_window) num_term=1;

	/* Create one or several terms */
	for (i = 0; i < num_term; i++)
	{
		int rows, cols, y, x;

		if (split_window)
		{
		        /* Hack - the main window is huge */
		        /* Sub windows require a width of at least 25 and a height
			 * if at least 6.  Furth excess height is split between the
			 * main window and the others.
			 */
		        if (COLS > MIN_COLS_SPLIT) cols = 80 + (COLS - MIN_COLS_SPLIT) / 2;
			else cols = COLS;
			if (LINES > MIN_ROWS_SPLIT) rows = 24 + (LINES - MIN_ROWS_SPLIT) / 2;
			else rows = LINES;
		}
		else
		{
		        cols=COLS;
			rows=LINES;
		}

		/* Decide on size and position */
		switch (i)
		{
			/* Upper left */
			case 0:
				y = x = 0;
				break;

			/* Lower left */
			case 1:
				y = rows + 1;
				x = 0;
				rows = LINES - (rows + 1);
				break;

			/* Upper right */
			case 2:
				y = 0;
				x = cols + 1;
				cols = COLS - (cols + 1);
				break;

			/* Lower right */
			case 3:
				y = rows + 1;
				x = cols + 1;
				rows = LINES - (rows + 1);
				cols = COLS - (cols + 1);
				break;

			/* XXX */
			default:
				rows = cols = y = x = 0;
				break;
		}

		/* Skip non-existant windows */
		if (rows <= 0 || cols <= 0) continue;

		/* Create a term */
		term_data_init_gcu(&data[next_win], rows, cols, y, x, i);

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


