/* File: z-virt.h */

/*
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */

#ifndef INCLUDED_Z_VIRT_H
#define INCLUDED_Z_VIRT_H

#include "h-basic.h"

/*
 * Memory management routines.
 *
 * Set ralloc_aux to modify the memory allocation routine.
 * Set rnfree_aux to modify the memory de-allocation routine.
 *
 * These routines work best as a *replacement* for malloc/free.
 *
 * The string_make() and string_free() routines handle dynamic strings.
 * A dynamic string is a string allocated at run-time, which should not
 * be modified once it has been created.
 *
 * Note the macros below which simplify the details of allocation,
 * deallocation, setting, clearing, casting, size extraction, etc.
 *
 * The macros MAKE/C_MAKE have a "procedural" metaphor,
 * and they actually modify their arguments.
 *
 * Note that, for some reason, some allocation macros may disallow
 * "stars" in type names, but you can use typedefs to circumvent
 * this.  For example, instead of "type **p; MAKE(p,type*);" you
 * can use "typedef type *type_ptr; type_ptr *p; MAKE(p,type_ptr)".
 *
 * Note that it is assumed that "memset()" will function correctly,
 * in particular, that it returns its first argument.
 */



/**** Available macros ****/


/* Set every byte in an array of type T[N], at location P, to V, and return P */
#define C_BSET(P,V,N,T) \
	(T*)(memset((char*)(P),(V), (N) * sizeof(T)))

/* Set every byte in a thing of type T, at location P, to V, and return P */
#define BSET(P,V,T) \
	(T*)(memset((char*)(P),(V), sizeof(T)))


/* Wipe an array of type T[N], at location P, and return P */
#define C_WIPE(P, N, T) \
	(T*)(memset((char*)(P), 0, (N) * sizeof(T)))

/* Wipe a thing of type T, at location P, and return P */
#define WIPE(P, T) \
	(T*)(memset((char*)(P), 0, sizeof(T)))


/* Load an array of type T[N], at location P1, from another, at location P2 */
#define C_COPY(P1, P2, N, T) \
	(T*)(memcpy((char*)(P1),(char*)(P2), (N) * sizeof(T)))

/* Load a thing of type T, at location P1, from another, at location P2 */
#define COPY(P1, P2, T) \
	(T*)(memcpy((char*)(P1),(char*)(P2), sizeof(T)))


/* Free one thing at P, return NULL */
#define FREE(P) \
	(rnfree(P), P = NULL)


/* Allocate, and return, an array of type T[N] */
#define C_RNEW(N, T) \
	((T*)(ralloc((N) * sizeof(T))))

/* Allocate, and return, a thing of type T */
#define RNEW(T) \
	((T*)(ralloc(sizeof(T))))


/* Allocate, wipe, and return an array of type T[N] */
#define C_ZNEW(N, T) \
	(T*)(C_WIPE(C_RNEW(N, T), N, T))

/* Allocate, wipe, and return a thing of type T */
#define ZNEW(T) \
	(T*)(WIPE(RNEW(T), T))


/* Allocate a wiped array of type T[N], assign to pointer P */
#define C_MAKE(P,N,T) \
	((P)=C_ZNEW(N,T))

/* Allocate a wiped thing of type T, assign to pointer P */
#define MAKE(P,T) \
	((P)=ZNEW(T))


/**** Available variables ****/

/* Replacement hook for "rnfree()" */
extern void *(*rnfree_aux)(void *);

/* Replacement hook for "ralloc()" */
extern void *(*ralloc_aux)(size_t);


/**** Available functions ****/

/* De-allocate a given amount of memory */
extern void *rnfree(void *p);

/* Allocate (and return) 'len', or exit */
extern void *ralloc(size_t len);

/* Create a "dynamic string" */
extern char *string_make(const char *str);

/* Free a string allocated with "string_make()" */
extern void string_free(char *str);




#endif /* INCLUDED_Z_VIRT_H */



