/* File: z-virt.c */

/*
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */

/* Purpose: Memory management routines -BEN- */

#include "z-virt.h"

#include "z-util.h"


/*
 * Optional auxiliary "rnfree" function
 */
void * (*rnfree_aux)(void *, size_t) = NULL;

/*
 * Free some memory (allocated by ralloc), return NULL
 */
void *rnfree(void *p, size_t len)
{
	/* Easy to free zero bytes */
	if (len == 0) return (NULL);

	/* Use the "aux" function */
	if (rnfree_aux) return ((*rnfree_aux)(p, len));

	/* Use "free" */
	free ((char*)(p));

	/* Done */
	return (NULL);
}


/*
 * Optional auxiliary "ralloc" function
 */
void * (*ralloc_aux)(size_t) = NULL;


/*
 * Allocate some memory
 *
 * Doesn't return on out of memory.
 */
void *ralloc(size_t len)
{
	void *mem;

	/* Allow allocation of "zero bytes" */
	if (len == 0) return ((void *)(NULL));

	/* Use the aux function if set */
	if (ralloc_aux) mem = (*ralloc_aux)(len);

	/* Use malloc() to allocate some memory */
	else mem = ((void *)(malloc((size_t)(len))));

	if (!mem)
		quit("Out of Memory!");

	/* Return the memory, if any */
	return (mem);
}




/*
 * Allocate a constant string, containing the same thing as 'str'
 */
char *string_make(char *str)
{
	size_t len = 0;
	cptr t = str;
	char *s, *res;

	/* Simple sillyness */
	if (!str) return (str);

	/* Get the number of chars in the string, including terminator */
	while (str[len++]) /* loop */;

	/* Allocate space for the string */
	s = res = (char*)(ralloc(len));

	/* Copy the string (with terminator) */
	while ((*s++ = *t++) != 0) /* loop */;

	/* Return the allocated, initialized, string */
	return (res);
}


/*
 * Un-allocate a string allocated above.
 * Depends on no changes being made to the string.
 */
errr string_free(char *str)
{
	size_t len = 0;

	/* Succeed on non-strings */
	if (!str) return (0);

	/* Count the number of chars in 'str' plus the terminator */
	while (str[len++]) /* loop */;

	/* Kill the buffer of chars we must have allocated above */
	rnfree((void *)(str), len);

	/* Success */
	return (0);
}


