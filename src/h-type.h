/* CVS: Last edit by $Author: bahman $ on $Date: 2006/01/19 22:38:47 $ */
/* File: h-type.h */

#ifndef INCLUDED_H_TYPE_H
#define INCLUDED_H_TYPE_H


/* Remove: cptr, uint */


/* A simple pointer (to unmodifiable strings) */
typedef const char *cptr;


/*
 * Hack -- prevent problems with non-MACINTOSH
 */
#undef uint
#define uint uint_hack

/* An unsigned, "standard" integer (often pre-defined) */
typedef unsigned int uint;



/*** Define the basic game types ***/

/*
 * errr is an error code
 *
 * A "byte" is an unsigned byte of memory.
 * s16b/u16b are exactly 2 bytes (when possible)
 * s32b/u32b are exactly 4 bytes (when possible)
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

  #define TRUE	1
  #define FALSE	0

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

#define MAX_UCHAR       UINT8_MAX
#define MAX_SHORT       INT16_MAX

#else /* HAVE_STDINT_H */

  /* Try hacks instead (not guaranteed to work) */
  typedef unsigned char byte;
  typedef signed short s16b;
  typedef unsigned short u16b;

#define MAX_UCHAR       UCHAR_MAX
#define MAX_SHORT       32767

  /* Detect >32-bit longs */
  #if (UINT_MAX == 0xFFFFFFFFUL) && (ULONG_MAX > 0xFFFFFFFFUL)
    typedef signed int s32b;
    typedef unsigned int u32b;
  #else
    typedef signed long s32b;
    typedef unsigned long u32b;
  #endif

#endif /* HAVE_STDINT_H */

#endif /* INCLUDED_H_TYPE_H */

