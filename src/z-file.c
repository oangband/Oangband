/*
 * File: z-file.c
 * Purpose: Low-level file (and directory) handling
 *
 * Copyright (c) 1997-2007 Ben Harrison, pelpel, Andrew Sidwell, Matthew Jones
 */
#include "angband.h"

#include <sys/types.h>

#ifdef WINDOWS
# include <windows.h>
# include <io.h>
# include <direct.h>
#endif

#ifdef MACH_O_CARBON
# include <Carbon/Carbon.h>
#endif

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif


/*
 * Player info
 */
int player_uid;
int player_egid;

/*
 * Hack -- drop permissions
 */
void safe_setuid_drop(void)
{

#ifdef SET_UID

	if (setuid(getuid()) != 0)
	{
		quit("setuid(): cannot set permissions correctly!");
	}
	if (setgid(getgid()) != 0)
	{
		quit("setgid(): cannot set permissions correctly!");
	}

#endif

}


/*
 * Hack -- grab permissions
 */
void safe_setuid_grab(void)
{

#ifdef SET_UID

	if (setuid(player_euid) != 0)
	{
		quit("setuid(): cannot set permissions correctly!");
	}
	if (setgid(player_egid) != 0)
	{
		quit("setgid(): cannot set permissions correctly!");
	}

#endif

}


