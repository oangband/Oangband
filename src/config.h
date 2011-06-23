
/* File: config.h */

/* Compilation options.
 *
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */


/*
 * Look through the following lines, and where a comment includes the
 * tag "OPTION:", examine the associated "#define" statements, and decide
 * whether you wish to keep, comment, or uncomment them.  You should not
 * have to modify any lines not indicated by "OPTION".
 *
 * Note: Also examine the "system" configuration file "h-config.h"
 * and the variable initialization file "variable.c".  If you change
 * anything in "variable.c", you only need to recompile that file.
 *
 * And finally, remember that the "Makefile" will specify some rather
 * important compile time options, like what visual module to use.
 */


/*
 * OPTION: See the Makefile(s), where several options may be declared.
 *
 * Some popular options include "USE_GCU" (allow use with Unix "curses"),
 * "USE_X11" (allow basic use with Unix X11).
 *
 * The old "USE_NCU" option has been replaced with "USE_GCU".
 *
 * Several other such options are available for non-unix machines,
 * such as "MACINTOSH", "WINDOWS".
 */


/*
 * OPTION: Use the POSIX "termios" methods in "main-gcu.c"
 */
/* #define USE_TPOSIX */


/*
 * OPTION: Include "ncurses.h" instead of "curses.h" in "main-gcu.c"
 */
/* #define USE_NCURSES */





/*
 * OPTION: Verify savefile Checksums (Angband 2.7.0 and up)
 * This option can help prevent "corruption" of savefiles, and also
 * stop intentional modification by amateur users.
 */
#define VERIFY_CHECKSUMS


/*
 * OPTION: Forbid the use of "fiddled" savefiles.  As far as I can tell,
 * a fiddled savefile is one with an internal timestamp different from
 * the actual timestamp.  Thus, turning this option on forbids one from
 * copying a savefile to a different name.  Combined with disabling the
 * ability to save the game without quitting, and with some method of
 * stopping the user from killing the process at the tombstone screen,
 * this should prevent the use of backup savefiles.  It may also stop
 * the use of savefiles from other platforms, so be careful.
 */
/* #define VERIFY_TIMESTAMP */


/*
 * OPTION: Forbid the "savefile over-write" cheat, in which you simply
 * run another copy of the game, loading a previously saved savefile,
 * and let that copy over-write the "dead" savefile later.  This option
 * either locks the savefile, or creates a fake "xxx.lok" file to prevent
 * the use of the savefile until the file is deleted.  Not ready yet.
 */
/* #define VERIFY_SAVEFILE */



/*
 * OPTION: Hack -- Compile in support for "Borg mode"
 */
/* #define ALLOW_BORG */

/*
 * OPTION: Hack -- Compile in support for "Debug Commands"
 */
#define ALLOW_DEBUG

/*
 * OPTION: Hack -- Compile in support for "Spoiler Generation"
 */
#define ALLOW_SPOILERS


/*
 * OPTION: Allow "do_cmd_colors" at run-time
 */
#define ALLOW_COLORS

/*
 * OPTION: Allow "do_cmd_visuals" at run-time
 */
#define ALLOW_VISUALS

/*
 * OPTION: Allow "do_cmd_macros" at run-time
 */
#define ALLOW_MACROS


/*
 * OPTION: Allow characters to be "auto-rolled"
 */
#define ALLOW_AUTOROLLER


/*
 * OPTION: Allow parsing of the ascii template files in "init.c".
 * This must be defined if you do not have valid binary image files.
 * It should be usually be defined anyway to allow easy "updating".
 */
#define ALLOW_TEMPLATES

/*
 * OPTION: Delay the loading of the "f_text" array until it is actually
 * needed, saving ~1K, since "feature" descriptions are unused.
 */
#define DELAY_LOAD_F_TEXT

/*
 * OPTION: Delay the loading of the "k_text" array until it is actually
 * needed, saving ?K, but slowing down the display of object descriptions.
 */
/* #define DELAY_LOAD_K_TEXT */

/*
 * OPTION: Delay the loading of the "a_text" array until it is actually
 * needed, saving ?K, but slowing down the display of artifact descriptions.
 */
/* #define DELAY_LOAD_A_TEXT */

/*
 * OPTION: Delay the loading of the "e_text" array until it is actually
 * needed, saving ?K, but slowing down the display of ego-item descriptions.
 */
/* #define DELAY_LOAD_E_TEXT */

/*
 * OPTION: Delay the loading of the "r_text" array until it is actually
 * needed, saving ~60K, but "simplifying" the "monster" descriptions.
 */
/* #define DELAY_LOAD_R_TEXT */

/*
 * OPTION: Delay the loading of the "v_text" array until it is actually
 * needed, saving ~1K, but "destroying" the "vault" generation.
 */
/* #define DELAY_LOAD_V_TEXT */

/*
 * OPTION: Do not generate themed levels. -LM-
 */
/* #define NO_THEMED_LEVELS */


/*
 * OPTION: Handle signals
 */
#define HANDLE_SIGNALS


/*
 * Allow "Wizards" to yield "high scores"
 */
/* #define SCORE_WIZARDS */

/*
 * Allow "Borgs" to yield "high scores"
 */
/* #define SCORE_BORGS */

/*
 * Allow "Cheaters" to yield "high scores"
 */
/* #define SCORE_CHEATERS */



/*
 * OPTION: Allow monsters to use noise and scent information to better
 * track the character.  This feature requires a significant amount of
 * memory.
 */
#define MONSTER_FLOW


/*
 * OPTION: Support multiple "player" grids in "map_info()"
 */
/* #define MAP_INFO_MULTIPLE_PLAYERS */


/*
 * OPTION: Use the "complex" wall illumination code
 */
/* #define UPDATE_VIEW_COMPLEX_WALL_ILLUMINATION */


/*
 * OPTION: Check the modification time of *_info.raw files
 */
#define CHECK_MODIFICATION_TIME


/*
 * OPTION: Allow the use of "sound" in various places.
 */
#define USE_SOUND

/*
 * OPTION: Allow the use of "graphics" in various places
 */
/* #define USE_GRAPHICS TNB */


/*
 * OPTION: Hack -- Macintosh stuff
 */
#ifdef MACINTOSH

/* Do not handle signals */
# undef HANDLE_SIGNALS

#endif


/*
 * OPTION: Hack -- Windows stuff
 */
#ifdef WINDOWS

/* Do not handle signals */
# undef HANDLE_SIGNALS

#endif


/*
 * OPTION: Set the "default" path to the angband "lib" directory.
 *
 * See "main.c" for usage, and note that this value is only used on
 * certain machines, primarily Unix machines.
 *
 * The configure script overrides this value.  Check the "--prefix=<dir>"
 * option of the configure script.
 *
 * This value will be over-ridden by the "ANGBAND_PATH" environment
 * variable, if that variable is defined and accessable.  The final
 * "slash" is required if the value supplied is in fact a directory.
 *
 * Using the value "./lib/" below tells Angband that, by default,
 * the user will run "angband" from the same directory that contains
 * the "lib" directory.  This is a reasonable (but imperfect) default.
 *
 * If at all possible, you should change this value to refer to the
 * actual location of the "lib" folder, for example, "/tmp/angband/lib/"
 * or "/usr/games/lib/angband/", or "/pkg/angband/lib".
 */
#ifndef DEFAULT_PATH
# define DEFAULT_PATH "./lib/"
#endif /* DEFAULT_PATH */


/*
 * OPTION: Create and use a hidden directory in the users home directory
 * for storing pref-files and character-dumps.
 */
#ifdef SET_UID
# ifndef PRIVATE_USER_PATH
#  define PRIVATE_USER_PATH "~/.angband"
# endif /* PRIVATE_USER_PATH */
#endif /* SET_UID */


/*
 * OPTION: Create and use hidden directories in the users home directory
 * for storing save files, data files, and high-scores
 */
#ifdef PRIVATE_USER_PATH
/* # define USE_PRIVATE_PATHS */
#endif /* PRIVATE_USER_PATH */


/*
 * On multiuser systems, add the "uid" to savefile names
 */
#ifdef SET_UID
# define SAVEFILE_USE_UID
#endif /* SET_UID */


/*
 * Allow the user to execute his own scripts in debug mode.
 *
 * The user-script code has not been checked for security issues yet,
 * so the user shouldn't be allowed to execute his own scripts from
 * a setgid executable.
 */
#ifndef SET_UID
# define ALLOW_USER_SCRIPTS
#endif /* SET_UID */


/*
 * OPTION: Prevent usage of the "ANGBAND_PATH" environment variable and
 * the '-d<what>=<path>' command line option (except for '-du=<path>').
 *
 * This prevents cheating in multi-user installs as well as possible
 * security problems when running setgid.
 */
#ifdef SET_UID
#define FIXED_PATHS
#endif /* SET_UID */


/*
 * OPTION: For some brain-dead computers with no command line interface,
 * namely Macintosh, there has to be some way of "naming" your savefiles.
 * The current "Macintosh" hack is to make it so whenever the character
 * name changes, the savefile is renamed accordingly.  But on normal
 * machines, once you manage to "load" a savefile, it stays that way.
 * Macintosh is particularly weird because you can load savefiles that
 * are not contained in the "lib:save:" folder, and if you change the
 * player's name, it will then save the savefile elsewhere.  Note that
 * this also gives a method of "bypassing" the "VERIFY_TIMESTAMP" code.
 */
#if defined(MACINTOSH)
# define SAVEFILE_MUTABLE
#endif

/*
 * OPTION: Capitalize the "user_name" (for "default" player name)
 * This option is only relevant on SET_UID machines.
 */
#define CAPITALIZE_USER_NAME


/*
 * OPTION: Person to bother if something goes wrong.
 */
#define MAINTAINER	"bahman@topped-with-meat.com"

/*
 * OPTION: Default font (when using X11).
 */
#define DEFAULT_X11_FONT		"9x15"


/*
 * OPTION: Default fonts (when using X11)
 */
#define DEFAULT_X11_FONT_0		"10x20"
#define DEFAULT_X11_FONT_1		"9x15"
#define DEFAULT_X11_FONT_2		"9x15"
#define DEFAULT_X11_FONT_3		"5x8"
#define DEFAULT_X11_FONT_4		"5x8"
#define DEFAULT_X11_FONT_5		"5x8"
#define DEFAULT_X11_FONT_6		"5x8"
#define DEFAULT_X11_FONT_7		"5x8"


/*
 * OPTION: Default fonts (when using X11)
 */
#define DEFAULT_X11_FONT_SCREEN		DEFAULT_X11_FONT
#define DEFAULT_X11_FONT_MIRROR		DEFAULT_X11_FONT
#define DEFAULT_X11_FONT_RECALL		DEFAULT_X11_FONT
#define DEFAULT_X11_FONT_CHOICE		DEFAULT_X11_FONT




/*
 * OPTION: Gamma correct X11 colours.
 */

#define SUPPORT_GAMMA


/*
 * OPTION: Attempt to prevent all "cheating"
 */
/* #define VERIFY_HONOR */


/*
 * React to the "VERIFY_HONOR" flag
 */
#ifdef VERIFY_HONOR
# define VERIFY_SAVEFILE
# define VERIFY_CHECKSUMS
# define VERIFY_TIMESTAMP
#endif

/*
 * OPTION: Repeat last command -- TNB
 */
#define ALLOW_REPEAT

/*
 * OPTION: Make opening and closing things easy -- TNB
 */
#define ALLOW_EASY_OPEN

/*
 * OPTION: Make disarming traps easy -- TNB
 */
#define ALLOW_EASY_DISARM

/*
 * Hack -- Mach-O (native binary format of OS X) is basically a Un*x
 * but has Mac OS/Windows-like user interface
 */
#ifdef MACH_O_CARBON
# ifdef SAVEFILE_USE_UID
#  undef SAVEFILE_USE_UID
# endif
#endif
