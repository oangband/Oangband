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
void * (*rnfree_aux)(void *) = NULL;

/*
 * Free some memory (allocated by ralloc), return NULL
 */
void *rnfree(void *p)
{
	if (!p) return (NULL);

	/* Use the "aux" function */
	if (rnfree_aux) return ((*rnfree_aux)(p));

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
 * Duplicates an existing string `str`, allocating as much memory as necessary.
 */
char *string_make(const char *str)
{
	char *res;
	size_t siz;

	/* Error-checking */
	if (!str) return NULL;

	/* Allocate space for the string (including terminator) */
	siz = strlen(str) + 1;
	res = (char*)(ralloc(siz));

	/* Copy the string (with terminator) */
	my_strcpy(res, str, siz);

	return res;
}


/*
 * Un-allocate a string allocated above.
 * Depends on no changes being made to the string.
 */
void string_free(char *str)
{
	/* Kill the buffer of chars we must have allocated above */
	rnfree((void *)(str));
}


