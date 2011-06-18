/* File z-util.h */

/*
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */

#ifndef INCLUDED_Z_UTIL_H
#define INCLUDED_Z_UTIL_H

#include "h-basic.h"


/*
 * Extremely basic stuff, like global temp and constant variables.
 * Also, some very useful low level functions, such as "streq()".
 * All variables and functions in this file are "addressable".
 */


/**** Available variables ****/

/**
 * The name of the program.
 */
extern char *argv0;


/* Aux functions */
extern void (*plog_aux)(const char *);
extern void (*quit_aux)(const char *);


/**** Available Functions ****/

/**
 * Case insensitive comparison between two strings
 */
extern int my_stricmp(const char *s1, const char *s2);

/**
 * Case insensitive comparison between two strings, up to n characters long.
 */
extern int my_strnicmp(const char * a, const char * b, int n);

/**
 * Case-insensitive strstr
 */
extern char *my_stristr(const char *string, const char *pattern);

/* Copy a string */
extern size_t my_strcpy(char *buf, const char *src, size_t bufsize);

/* Concatenate two strings */
extern size_t my_strcat(char *buf, const char *src, size_t bufsize);

/* Test equality, prefix, suffix */
extern bool streq(const char * s, const char * t);
extern bool prefix(const char * s, const char * t);
extern bool suffix(const char * s, const char * t);


/* Print an error message */
extern void plog(const char * str);

/* Exit, with optional message */
extern void quit(const char * str);


/* Sorting functions */
/* TODO: make ang_sort() take comp and swap hooks rather than use globals */
/* void ang_sort(void *u, void *v, int n); */
extern void sort(void *array, size_t nmemb, size_t smemb,
		 int (*comp)(const void *a, const void *b));

/* Mathematical functions */
int mean(int *nums, int size);
int variance(int *nums, int size);

#endif /* INCLUDED_Z_UTIL_H */
