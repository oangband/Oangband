/* File: h-system.h */

#ifndef INCLUDED_H_SYSTEM_H
#define INCLUDED_H_SYSTEM_H

/*
 * Include the basic "system" files.
 *
 * Make sure all "system" constants/macros are defined.
 * Make sure all "system" functions have "extern" declarations.
 *
 * This file is a big hack to make other files less of a hack.
 * This file has been rebuilt -- it may need a little more work.
 */

/** ANSI C headers **/
#include <ctype.h>
#include <errno.h>
#include <limits.h>
/* assert.h */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
/* stddef.h */
#include <string.h>
#include <time.h>

/** POSIX headers **/

#if defined(SET_UID) || defined(MACH_O_CARBON)
# include <pwd.h>
# include <sys/stat.h>
# include <unistd.h>
#endif /* SET_UID */



/** Other headers **/

#ifdef SET_UID

# include <sys/types.h>

#endif /* SET_UID */


#if defined(MACINTOSH) && defined(__MWERKS__)
# include <unix.h>
#endif

#if defined(WINDOWS)
# include <io.h>
#endif

#if !defined(MACINTOSH) && \
    !defined(RISCOS) && !defined(__MWERKS__)
# if defined(__TURBOC__) || defined(__WATCOMC__)
#  include <mem.h>
# else
#  include <memory.h>
# endif
#endif

#if !defined(NeXT) && !defined(RISCOS)
# include <fcntl.h>
#endif

#if defined(__DJGPP__) || defined(__MWERKS__)
#include <unistd.h>
#endif /* __DJGPP__ || __MWERKS__ */

#endif /* INCLUDE_H_SYSTEM_H */


