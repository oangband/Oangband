/* File: h-basic.h */

#ifndef INCLUDED_H_BASIC_H
#define INCLUDED_H_BASIC_H

/*
 * The most basic "include" file.
 *
 * This file simply includes other low level header files.
 */

/* Autoconf Support */
#ifdef HAVE_CONFIG_H
#include "autoconf.h"

#else /* HAVE_CONFIG_H */

/*
 * Everyone except RISC OS has fcntl.h and sys/stat.h
 */
#define HAVE_FCNTL_H
#define HAVE_STAT

#endif /* HAVE_CONFIG_H */

/* System Configuration */
#include "h-config.h"

/*** Include the library header files ***/

/* Use various POSIX functions if available */
#undef _GNU_SOURCE
#define _GNU_SOURCE

/** ANSI C headers **/
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

/** POSIX headers **/

#if defined(SET_UID) || defined(MACH_O_CARBON)
# include <pwd.h>
# include <sys/stat.h>
# include <unistd.h>
#endif /* SET_UID */



/** Other headers **/

#include <fcntl.h>

/*** Define the basic game types ***/

/*
 * errr is an error code
 *
 * A "byte" is an unsigned byte of memory.
 * s16b/u16b are exactly 2 bytes (where possible)
 * s32b/u32b are exactly 4 bytes (where possible)
 */

/* C++ defines its own bool type, so we hack around it */
#undef bool
#define bool bool_hack

typedef int errr;


/*
 * Use a real bool type where possible
 */
#ifdef HAVE_STDBOOL_H

  #include <stdbool.h>

  #define TRUE  true
  #define FALSE false

#else

  /* Use a char otherwise */
  typedef char bool;

  #undef TRUE
  #undef FALSE

  #define TRUE   1
  #define FALSE  0

#endif



/*
 * Use guaranteed-size ints where possible
 */
#ifdef HAVE_STDINT_H

  /* Use guaranteed-size types */
  #include <stdint.h>

  typedef uint8_t byte;

  typedef uint16_t u16b;
  typedef int16_t s16b;

  typedef uint32_t u32b;
  typedef int32_t s32b;

  typedef uint64_t u64b;
  typedef int64_t s64b;

#define MAX_UCHAR		UINT8_MAX
#define MAX_SHORT		INT16_MAX

#else /* HAVE_STDINT_H */

  /* Try hacks instead (not guaranteed to work) */
  typedef unsigned char byte;
  typedef signed short s16b;
  typedef unsigned short u16b;

#define MAX_UCHAR		UCHAR_MAX
#define MAX_SHORT		32767

  /* Detect >32-bit longs */
  #if (UINT_MAX == 0xFFFFFFFFUL) && (ULONG_MAX > 0xFFFFFFFFUL)
    typedef signed int s32b;
    typedef unsigned int u32b;
  #else
    typedef signed long s32b;
    typedef unsigned long u32b;
  #endif

#endif /* HAVE_STDINT_H */


/** Debugging macros ***/

#define DSTRINGIFY(x) #x
#define DSTRING(x)    DSTRINGIFY(x)
#define DHERE         __FILE__ ":" DSTRING(__LINE__) ": "


/*** Basic math macros ***/

#undef MIN
#undef MAX
#undef ABS
#undef SGN
#undef CMP

#define MIN(a,b)	(((a) > (b)) ? (b)  : (a))
#define MAX(a,b)	(((a) < (b)) ? (b)  : (a))
#define ABS(a)		(((a) < 0)   ? (-(a)) : (a))
#define SGN(a)		(((a) < 0)   ? (-1) : ((a) != 0))
#define CMP(a,b) ((a) < (b) ? -1 : ((b) < (a) ? 1 : 0))


/*** Useful fairly generic macros ***/

/*
 * Given an array, determine how many elements are in it.
 */
#define N_ELEMENTS(a) (sizeof(a) / sizeof((a)[0]))

/*
 * Return "s" (or not) depending on whether n is singular.
 */
#define PLURAL(n)		((n) == 1 ? "" : "s")


/*** Some hackish character manipulation ***/

/*
 * Note that all "index" values must be "lowercase letters", while
 * all "digits" must be "digits".  Control characters can be made
 * from any legal characters.  XXX XXX XXX
 */
#define A2I(X)	((X) - 'a')
#define I2A(X)	((X) + 'a')
#define D2I(X)	((X) - '0')
#define I2D(X)	((X) + '0')
#define KTRL(X)	((X) & 0x1F)
#define ESCAPE	'\033'

#endif /* INCLUDED_H_BASIC_H */
