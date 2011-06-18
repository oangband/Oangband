/* CVS: Last edit by $Author: bahman $ on $Date: 2006/01/19 22:38:47 $ */
/* File: h-type.h */

#ifndef INCLUDED_H_TYPE_H
#define INCLUDED_H_TYPE_H

/*
 * Basic "types".
 *
 * Note the attempt to make all basic types have 4 letters.
 * This improves readibility and standardizes the code.
 *
 * Likewise, all complex types are at least 4 letters.
 * Thus, almost every three letter word is a legal variable.
 * But beware of certain reserved words ('for' and 'if' and 'do').
 *
 * Note that the type used in structures for bit flags should be uint.
 * As long as these bit flags are sequential, they will be space smart.
 *
 * Note that on some machines, apparently "signed char" is illegal.
 *
 * It must be true that char/byte takes exactly 1 byte
 * It must be true that sind/uind takes exactly 2 bytes
 * It must be true that sbig/ubig takes exactly 4 bytes
 *
 * On Sparc's, a sint takes 4 bytes (2 is legal)
 * On Sparc's, a uint takes 4 bytes (2 is legal)
 * On Sparc's, a long takes 4 bytes (8 is legal)
 * On Sparc's, a huge takes 4 bytes (8 is legal)
 * On Sparc's, a vptr takes 4 bytes (8 is legal)
 *
 * Note that some files have already been included by "h-include.h"
 * These include <stdio.h> and <sys/types>, which define some types
 * In particular, uint is defined so we do not have to define it
 *
 * Also, see <limits.h> for min/max values for sind, uind, long, huge
 * (SHRT_MIN, SHRT_MAX, USHRT_MAX, LONG_MIN, LONG_MAX, ULONG_MAX)
 * These limits should be verified and coded into "h-constant.h".
 */



/*** Special 4 letter names for some standard types ***/


/* A standard pointer (to "void" because ANSI C says so) */
typedef void *vptr;

/* A simple pointer (to unmodifiable strings) */
typedef const char *cptr;


/* Error codes for function return values */
/* Success = 0, Failure = -N, Problem = +N */
typedef int errr;


/*
 * Hack -- prevent problems with non-MACINTOSH
 */
#undef uint
#define uint uint_hack

/*
 * Hack -- prevent problems with MSDOS and WINDOWS
 */
#undef huge
#define huge huge_hack

/*
 * Hack -- prevent problems with C++
 */
#undef bool
#define bool bool_hack


/* Note that unsigned values can cause math problems */
/* An unsigned byte of memory */
typedef unsigned char byte;

/* Note that a bool is smaller than a full "int" */
/* Simple True/False type */
typedef char bool;


/* A signed, standard integer (at least 2 bytes) */
typedef int sint;

/* An unsigned, "standard" integer (often pre-defined) */
typedef unsigned int uint;


/* The largest possible unsigned integer */
typedef unsigned long huge;


/* Signed/Unsigned 16 bit value */
typedef signed short s16b;
typedef unsigned short u16b;

/* Signed/Unsigned 32 bit value */
#ifdef L64	/* 64 bit longs */
typedef signed int s32b;
typedef unsigned int u32b;
#else
typedef signed long s32b;
typedef unsigned long u32b;
#endif




/*** Pointers to all the basic types defined above ***/

typedef char *char_ptr;
typedef byte *byte_ptr;

#endif /* INCLUDED_H_TYPE_H */

