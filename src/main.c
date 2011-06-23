/* File: main.c */

/*
 * Copyright (c) 1997 Ben Harrison, and others
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */

#include "angband.h"


/*
 * Some machines have a "main()" function in their "main-xxx.c" file,
 * all the others use this file for their "main()" function.
 */


#if !defined(MACINTOSH) && !defined(WINDOWS)

#ifdef USE_SCRIPT

#include "Python.h"

#endif /* USE_SCRIPT */


/*
 * A hook for "quit()".
 *
 * Close down, then fall back into "quit()".
 */
static void quit_hook(const char * s)
{
	int j;

	/* Scan windows */
	for (j = TERM_WIN_MAX - 1; j >= 0; j--)
	{
		/* Unused */
		if (!angband_term[j]) continue;

		/* Nuke it */
		term_nuke(angband_term[j]);
	}
}



/*
 * Initialize and verify the file paths, and the score file.
 *
 * Use the ANGBAND_PATH environment var if possible, else use
 * DEFAULT_PATH, and in either case, branch off appropriately.
 *
 * First, we'll look for the ANGBAND_PATH environment variable,
 * and then look for the files in there.  If that doesn't work,
 * we'll try the DEFAULT_PATH constant.  So be sure that one of
 * these two things works...
 *
 * We must ensure that the path ends with "PATH_SEP" if needed,
 * since the "init_file_paths()" function will simply append the
 * relevant "sub-directory names" to the given path.
 *
 * Make sure that the path doesn't overflow the buffer.  We have
 * to leave enough space for the path separator, directory, and
 * filenames.
 */
static void init_stuff(void)
{
	char path[1024];

	const char * tail;

	/* Get the environment variable */
	tail = getenv("ANGBAND_PATH");

	/* Use the angband_path, or a default */
	strncpy(path, tail ? tail : DEFAULT_PATH, 511);

	/* Make sure it's terminated */
	path[511] = '\0';

	/* Hack -- Add a path separator (only if needed) */
	if (!suffix(path, PATH_SEP)) strcat(path, PATH_SEP);

	/* Initialize */
	init_file_paths(path);
}



/*
 * Handle a "-d<what>=<path>" option
 *
 * The "<what>" can be any string starting with the same letter as the
 * name of a subdirectory of the "lib" folder (i.e. "i" or "info").
 *
 * The "<path>" can be any legal path for the given system, and should
 * not end in any special path separator (i.e. "/tmp" or "~/.ang-info").
 */
static void change_path(const char *info)
{
	if (!info || !info[0])
		quit_fmt("Try '-d<path>'.", info);

	string_free(ANGBAND_DIR_USER);
	ANGBAND_DIR_USER = string_make(info);
}


/*
 * Simple "main" function for multiple platforms.
 *
 * Note the special "--" option which terminates the processing of
 * standard options.  All non-standard options (if any) are passed
 * directly to the "init_xxx()" function.
 */
int main(int argc, char *argv[])
{
	int i;

	bool done = FALSE;

	bool new_game = FALSE;

	int show_score = 0;

	const char * mstr = NULL;

	bool args = TRUE;


	/* Save the "program name" XXX XXX XXX */
	argv0 = argv[0];

#ifdef SET_UID

	/* Default permissions on files */
	(void)umask(022);

#endif


	/* Get the file paths */
	init_stuff();


#ifdef SET_UID

	/* Get the user id */
	player_uid = getuid();

	/* Save the effective GID for later recall */
	player_egid = getegid();

#  if 0	/* XXX XXX XXX */

	/* Redundant setting necessary in case root is running the game */
	/* If not root or game not setuid the following two calls do nothing */

	if (setgid(getegid()) != 0)
	{
		quit("setgid(): cannot set permissions correctly!");
	}

	if (setuid(geteuid()) != 0)
	{
		quit("setuid(): cannot set permissions correctly!");
	}

#  endif

#endif /* SET_UID */


#ifdef SET_UID

#ifdef PRIVATE_USER_PATH

	/* Create directories for the users files */
	create_user_dirs();

#endif /* PRIVATE_USER_PATH */

	/* Acquire the "user name" as a default player name */
	user_name(op_ptr->full_name, player_uid);

#endif /* SET_UID */


	/* Process the command line arguments */
	for (i = 1; args && (i < argc); i++)
	{
		/* Require proper options */
		if (argv[i][0] != '-') goto usage;

		/* Analyze option */
		switch (argv[i][1])
		{
			case 'N':
			case 'n':
			{
				new_game = TRUE;
				break;
			}

			case 'F':
			case 'f':
			{
				arg_fiddle = TRUE;
				break;
			}

			case 'W':
			case 'w':
			{
				arg_wizard = TRUE;
				break;
			}

			case 'V':
			case 'v':
			{
				arg_sound = TRUE;
				break;
			}

			case 'R':
			case 'r':
			{
				arg_force_roguelike = TRUE;
				break;
			}

			case 'O':
			case 'o':
			{
				arg_force_original = TRUE;
				break;
			}

			case 'S':
			case 's':
			{
				show_score = atoi(&argv[i][2]);
				if (show_score <= 0) show_score = 10;
				break;
			}

			case 'u':
			case 'U':
			{
				if (!argv[i][2]) goto usage;
				strncpy(op_ptr->base_name, &argv[i][2], 32);
				op_ptr->base_name[31] = '\0';
				break;
			}

			case 'm':
			{
				if (!argv[i][2]) goto usage;
				mstr = &argv[i][2];
				break;
			}

			case 'M':
			{
				arg_monochrome = TRUE;
				break;
			}

			case 'd':
			case 'D':
			{
				change_path(&argv[i][2]);
				break;
			}

			case '-':
			{
				argv[i] = argv[0];
				argc = argc - i;
				argv = argv + i;
				args = FALSE;
				break;
			}

			default:
			usage:
			{
				/* Dump usage information */
				puts("Usage: angband [options] [-- subopts]");
				puts("  -n        Start a new character");
				puts("  -f        Request fiddle mode");
				puts("  -w        Request wizard mode");
				puts("  -v        Request sound mode");
				puts("  -g        Request graphics mode");
				puts("  -o        Request original keyset");
				puts("  -r        Request rogue-like keyset");
				puts("  -M        Request monochrome mode");
				puts("  -s<num>   Show <num> high scores");
				puts("  -u<who>   Use your <who> savefile");
				puts("  -d<path>  Store pref files and screendumps in <path>");

#ifdef USE_X11
				puts("  -mx11     To use X11");
				puts("  --        Sub options");
				puts("  -- -d     Set display name");
				puts("  -- -s     Turn off smoothscaling graphics");
				puts("  -- -n#    Number of terms to use");
#endif /* USE_X11 */

#ifdef USE_GCU
				puts("  -mgcu     To use GCU (GNU Curses)");
				puts("  --        Sub options");
				puts("  -- -x     No extra sub-windows");
#endif /* USE_GCU */

#ifdef USE_SLA
				puts("  -msla     To use SLA (SLANG)");
#endif /* USE_SLA */

				/* Actually abort the process */
				quit(NULL);
			}
		}
	}

	/* Process the player name (but only if one is specified) */
	if (strlen(op_ptr->base_name)) process_player_name(FALSE);

	/* Hack -- Forget standard args */
	if (args)
	{
		argc = 1;
		argv[1] = NULL;
	}


	/* Install "quit" hook */
	quit_aux = quit_hook;


	/* Drop privs (so X11 will work correctly) */
 	safe_setuid_drop();

#ifdef USE_X11
	/* Attempt to use the "main-x11.c" support */
	if (!done && (!mstr || (streq(mstr, "x11"))))
	{
		extern errr init_x11(int, char**);
		if (0 == init_x11(argc, argv))
		{
			ANGBAND_SYS = "x11";
			done = TRUE;
		}
	}
#endif

#ifdef USE_GCU
	/* Attempt to use the "main-gcu.c" support */
	if (!done && (!mstr || (streq(mstr, "gcu"))))
	{
		extern errr init_gcu(int, char**);
		if (0 == init_gcu(argc, argv))
		{
			ANGBAND_SYS = "gcu";
			done = TRUE;
		}
	}
#endif

#ifdef USE_SLA
	/* Attempt to use the "main-sla.c" support */
	if (!done && (!mstr || (streq(mstr, "sla"))))
	{
		extern errr init_sla(void);
		if (0 == init_sla())
		{
			ANGBAND_SYS = "sla";
			done = TRUE;
		}
	}
#endif

	/* Grab privs (dropped above for X11) */
 	safe_setuid_grab();

	/* Make sure we have a display! */
	if (!done) quit("Unable to prepare any 'display module'!");

	/* Catch nasty signals */
	signals_init();

	/* Initialize */
	init_angband();

	/* Hack -- If requested, display scores and quit */
	if (show_score > 0) display_scores(0, show_score);

	/* Wait for response */
	pause_line(23);

	/* Play the game */
	play_game(new_game);

	/* Quit */
	quit(NULL);

	/* Exit */
	return (0);
}

#endif /* MACINTOSH / WINDOWS */



