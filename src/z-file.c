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
 * Drop permissions
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
 * Grab permissions
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

/*
 * The concept of the "file" routines below (and elsewhere) is that all
 * file handling should be done using as few routines as possible, since
 * every machine is slightly different, but these routines always have the
 * same semantics.
 *
 * In fact, perhaps we should use the "path_parse()" routine below to convert
 * from "canonical" filenames (optional leading tilde's, internal wildcards,
 * slash as the path seperator, etc) to "system" filenames (no special symbols,
 * system-specific path seperator, etc).  This would allow the program itself
 * to assume that all filenames are "Unix" filenames, and explicitly "extract"
 * such filenames if needed (by "path_parse()", or perhaps "path_canon()").
 *
 * Note that "my_fopen()" and "my_open()" and "my_make()" and "my_kill()"
 * and "my_move()" and "my_copy()" should all take "canonical" filenames.
 *
 * Note that "canonical" filenames use a leading "slash" to indicate an absolute
 * path, and a leading "tilde" to indicate a special directory, and default to a
 * relative path, but MSDOS uses a leading "drivename plus colon" to indicate the
 * use of a "special drive", and then the rest of the path is parsed "normally",
 * and MACINTOSH uses a leading colon to indicate a relative path, and an embedded
 * colon to indicate a "drive plus absolute path", and finally defaults to a file
 * in the current working directory, which may or may not be defined.
 *
 * We should probably parse a leading "~~/" as referring to "ANGBAND_DIR". (?)
 */


#ifdef SET_UID

/*
 * Extract a "parsed" path from an initial filename
 * Normally, we simply copy the filename into the buffer
 * But leading tilde symbols must be handled in a special way
 * Replace "~user/" by the home directory of the user named "user"
 * Replace "~/" by the home directory of the current user
 */
errr path_parse(char *buf, int max, const char * file)
{
	const char * u, *s;
	struct passwd	*pw;
	char user[128];


	/* Assume no result */
	buf[0] = '\0';

	/* No file? */
	if (!file) return (-1);

	/* File needs no parsing */
	if (file[0] != '~')
	{
		strcpy(buf, file);
		return (0);
	}

	/* Point at the user */
	u = file+1;

	/* Look for non-user portion of the file */
	s = strstr(u, PATH_SEP);

	/* Hack -- no long user names */
	if (s && (s >= u + sizeof(user))) return (1);

	/* Extract a user name */
	if (s)
	{
		int i;
		for (i = 0; u < s; ++i) user[i] = *u++;
		user[i] = '\0';
		u = user;
	}

	/* Look up the "current" user */
	if (u[0] == '\0') u = getlogin();

	/* Look up a user (or "current" user) */
	if (u) pw = getpwnam(u);
	else pw = getpwuid(getuid());

	/* Nothing found? */
	if (!pw) return (1);

	/* Make use of the info */
	strcpy(buf, pw->pw_dir);

	/* Append the rest of the filename, if any */
	if (s) strcat(buf, s);

	/* Success */
	return (0);
}


#else /* SET_UID */


/*
 * Extract a "parsed" path from an initial filename
 *
 * This requires no special processing on simple machines,
 * except for verifying the size of the filename.
 */
errr path_parse(char *buf, int max, const char * file)
{
	/* Accept the filename */
	strnfmt(buf, max, "%s", file);

	/* Success */
	return (0);
}


#endif /* SET_UID */


/*
 * Create a new path by appending a file (or directory) to a path
 *
 * This requires no special processing on simple machines, except
 * for verifying the size of the filename, but note the ability to
 * bypass the given "path" with certain special file-names.
 *
 * Note that the "file" may actually be a "sub-path", including
 * a path and a file.
 *
 * Note that this function yields a path which must be "parsed"
 * using the "parse" function above.
 */
errr path_build(char *buf, int max, const char * path, const char * file)
{
	/* Special file */
	if (file[0] == '~')
	{
		/* Use the file itself */
		strnfmt(buf, max, "%s", file);
	}

	/* Absolute file, on "normal" systems */
	else if (prefix(file, PATH_SEP) && !streq(PATH_SEP, ""))
	{
		/* Use the file itself */
		strnfmt(buf, max, "%s", file);
	}

	/* No path given */
	else if (!path[0])
	{
		/* Use the file itself */
		strnfmt(buf, max, "%s", file);
	}

	/* Path and File */
	else
	{
		/* Build the new path */
		strnfmt(buf, max, "%s%s%s", path, PATH_SEP, file);
	}

	/* Success */
	return (0);
}


/*** File-handling API ***/

/* Private structure to hold file pointers and useful info. */
struct ang_file
{
	FILE *fh;
	char *fname;
	file_mode mode;
};



/** Utility functions **/

/*
 * Delete file 'fname'.
 */
bool file_delete(const char *fname)
{
	char buf[1024];

	/* Get the system-specific paths */
	path_parse(buf, sizeof(buf), fname);

	return (remove(buf) == 0);
}

/*
 * Hack -- attempt to move a file
 */
bool file_move(const char *fname, const char *newname)
{
	char buf[1024];
	char aux[1024];

	/* Get the system-specific paths */
	path_parse(buf, sizeof(buf), fname);
	path_parse(aux, sizeof(aux), newname);

	return (rename(buf, aux) == 0);
}

/** File-handle functions **/

/*
 * Open file 'fname', in mode 'mode', with filetype 'ftype'.
 * Returns file handle or NULL.
 */
ang_file *file_open(const char *fname, file_mode mode, file_type ftype)
{
	ang_file *f = ZNEW(ang_file);
	char buf[1024];

	(void)ftype;

	/* Get the system-specific path */
	path_parse(buf, sizeof(buf), fname);

	switch (mode)
	{
		case MODE_WRITE:  f->fh = fopen(buf, "wb"); break;
		case MODE_READ:   f->fh = fopen(buf, "rb"); break;
		case MODE_APPEND: f->fh = fopen(buf, "a+"); break;
		default:          f->fh = fopen(buf, "__");
       	}

	if (f->fh == NULL)
	{
		FREE(f);
		return NULL;
	}

	f->fname = string_make(buf);
	f->mode = mode;

	return f;
}


/*
 * Hack -- replacement for "fopen()"
 */
FILE *my_fopen(const char * file, const char * mode)
{
	char buf[1024];
	FILE *fff;

	/* Hack -- Try to parse the path */
	if (path_parse(buf, sizeof(buf), file)) return (NULL);

	/* Attempt to fopen the file anyway */
	fff = fopen(buf, mode);

#if defined(MAC_MPW) || defined(MACH_O_CARBON)

	/* Set file creator and type */
	if (fff && strchr(mode, 'w')) fsetfileinfo(buf, _fcreator, _ftype);

#endif

	/* Return open file or NULL */
	return (fff);
}

/*
 * Close file handle 'f'.
 */
bool file_close(ang_file *f)
{
	if (fclose(f->fh) != 0)
		return FALSE;

	FREE(f->fname);
	FREE(f);

	return TRUE;
}

/*
 * Hack -- replacement for "fclose()"
 */
errr my_fclose(FILE *fff)
{
	/* Require a file */
	if (!fff) return (-1);

	/* Close, check for error */
	if (fclose(fff) == EOF) return (1);

	/* Success */
	return (0);
}


/** Locking functions **/

/*
 * Lock a file using POSIX locks, on platforms where this is supported.
 */
void file_lock(ang_file *f)
{
#if defined(HAVE_FCNTL_H) && defined(SET_UID)
	struct flock lock;
	lock.l_type = (f->mode == MODE_READ ? F_RDLCK : F_WRLCK);
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = 0;
	fcntl(fileno(f->fh), F_SETLKW, &lock);
#endif /* HAVE_FCNTL_H && SET_UID */
}

/*
 * Unlock a file locked using file_lock().
 */
void file_unlock(ang_file *f)
{
#if defined(HAVE_FCNTL_H) && defined(SET_UID)
	struct flock lock;
	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = 0;
	fcntl(fileno(f->fh), F_SETLK, &lock);
#endif /* HAVE_FCNTL_H && SET_UID */
}


/** Byte-based IO and functions **/

/*
 * Seek to location 'pos' in file 'f'.
 */
bool file_seek(ang_file *f, u32b pos)
{
	return (fseek(f->fh, pos, SEEK_SET) == 0);
}

/*
 * Read a single, 8-bit character from file 'f'.
 */
bool file_readc(ang_file *f, byte *b)
{
	int i = fgetc(f->fh);

	if (i == EOF)
		return FALSE;

	*b = (byte)i;
	return TRUE;
}

/*
 * Write a single, 8-bit character 'b' to file 'f'.
 */
bool file_writec(ang_file *f, byte b)
{
	return file_write(f, (const char *)&b, 1);
}

/*
 * Read 'n' bytes from file 'f' into array 'buf'.
 */
int file_read(ang_file *f, char *buf, size_t n)
{
	size_t read = fread(buf, 1, n, f->fh);

	if (read == 0 && ferror(f->fh))
		return -1;
	else
		return read;
}

/*
 * Append 'n' bytes of array 'buf' to file 'f'.
 */
bool file_write(ang_file *f, const char *buf, size_t n)
{
	return fwrite(buf, 1, n, f->fh) == n;
}

/** Line-based IO **/

/*
 * Read a line of text from file 'f' into buffer 'buf' of size 'n' bytes.
 *
 * Support both \r\n and \n as line endings, but not the outdated \r that used
 * to be used on Macs.  Replace non-printables with '?', and \ts with ' '.
 */
#define TAB_COLUMNS 4

bool file_getl(ang_file *f, char *buf, size_t len)
{
	bool seen_cr = FALSE;
	byte b;
	size_t i = 0;

	bool check_encodes = FALSE;

	/* Leave a byte for the terminating 0 */
	size_t max_len = len - 1;

	while (i < max_len)
	{
		char c;

		if (!file_readc(f, &b))
		{
			buf[i] = '\0';
			return (i == 0) ? FALSE : TRUE;
		}

		c = (char) b;

		if (c == '\r')
		{
			seen_cr = TRUE;
			continue;
		}

		if (seen_cr && c != '\n')
		{
			fseek(f->fh, -1, SEEK_CUR);
			buf[i] = '\0';
			return TRUE;
		}

		if (c == '\n')
		{
			buf[i] = '\0';
			return TRUE;
		}

		/* Expand tabs */
		if (c == '\t')
		{
			/* Next tab stop */
			size_t tabstop = ((i + TAB_COLUMNS) / TAB_COLUMNS) * TAB_COLUMNS;
			if (tabstop >= len) break;

			/* Convert to spaces */
			while (i < tabstop)
				buf[i++] = ' ';

			continue;
		}

		/* Ignore non-printables */
		/* else if (my_isprint((unsigned char)c)) */
		/* { */
		/* 	buf[i++] = c; */

		/* 	/\* Notice possible encode *\/ */
		/* 	if (c == '[') check_encodes = TRUE; */

		/* 	continue; */
		/* } */
		else
		{
			buf[i++] = '?';
			continue;
		}
	}

	buf[i] = '\0';
	return TRUE;
}

/*
 * Append a line of text 'buf' to the end of file 'f', using system-dependent
 * line ending.
 */
bool file_put(ang_file *f, const char *buf)
{
	return file_write(f, buf, strlen(buf));
}

/*
 * The comp.lang.c FAQ recommends this pairing for varargs functions.
 * See <http://c-faq.com/varargs/handoff.html>
 */

/**
 * Append a formatted line of text to the end of file 'f'.
 *
 * file_putf() is the ellipsis version. Most file output will call this
 * version. It calls file_vputf() to do the real work. It returns TRUE
 * if the write was successful and FALSE otherwise.
 */
bool file_putf(ang_file *f, const char *fmt, ...)
{
	va_list vp;
	bool status;

	if (!f) return FALSE;

	va_start(vp, fmt);
	status = file_vputf(f, fmt, vp);
	va_end(vp);

	return status;
}

/**
 * Append a formatted line of text to the end of file 'f'.
 *
 * file_vputf() is the va_list version. It returns TRUE if the write was
 * successful and FALSE otherwise.
 */
bool file_vputf(ang_file *f, const char *fmt, va_list vp)
{
	char buf[1024];

	if (!f) return FALSE;

	(void)vstrnfmt(buf, sizeof(buf), fmt, vp);
	return file_put(f, buf);
} 


/*
 * Hack -- replacement for "fgets()"
 *
 * Read a string, without a newline, to a file
 *
 * Process tabs, strip internal non-printables
 */
errr my_fgets(FILE *fff, char *buf, size_t n)
{
	int i = 0;

	char *s;

	char tmp[1024];

	/* Read a line */
	if (fgets(tmp, 1024, fff))
	{
		/* Convert weirdness */
		for (s = tmp; *s; s++)
		{
			/* Handle newline */
			if (*s == '\n')
			{
				/* Terminate */
				buf[i] = '\0';

				/* Success */
				return (0);
			}

			/* Handle tabs */
			else if (*s == '\t')
			{
				/* Hack -- require room */
				if (i + 8 >= n) break;

				/* Append a space */
				buf[i++] = ' ';

				/* Append some more spaces */
				while (!(i % 8)) buf[i++] = ' ';
			}

			/* Handle printables */
			else if (isprint(*s))
			{
				/* Copy */
				buf[i++] = *s;

				/* Check length */
				if (i >= n) break;
			}
		}
	}

	/* Nothing */
	buf[0] = '\0';

	/* Failure */
	return (1);
}


/*
 * Hack -- replacement for "fputs()"
 *
 * Dump a string, plus a newline, to a file
 *
 * Perhaps this function should handle internal weirdness.
 */
errr my_fputs(FILE *fff, const char * buf, size_t n)
{
	/* Dump, ignore errors */
	(void)fprintf(fff, "%s\n", buf);

	/* Success */
	return (0);
}


/*
 * Several systems have no "O_BINARY" flag
 */
#ifndef O_BINARY
# define O_BINARY 0
#endif /* O_BINARY */


/*
 * Hack -- attempt to open a file descriptor (create file)
 *
 * This function should fail if the file already exists
 *
 * Note that we assume that the file should be "binary"
 */
int fd_make(const char * file, int mode)
{
	char buf[1024];
	int fd;

	/* Hack -- Try to parse the path */
	if (path_parse(buf, sizeof(buf), file)) return (-1);

#if defined(MACINTOSH)

	/* Create the file, fail if exists, write-only, binary */
	fd = open(buf, O_CREAT | O_EXCL | O_WRONLY | O_BINARY);

#else

	/* Create the file, fail if exists, write-only, binary */
	fd = open(buf, O_CREAT | O_EXCL | O_WRONLY | O_BINARY, mode);

#endif

#if defined(MAC_MPW) || defined(MACH_O_CARBON)

	/* Set file creator and type */
	if (fd >= 0) fsetfileinfo(buf, _fcreator, _ftype);

#endif

	/* Return descriptor */
	return (fd);
}


/*
 * Hack -- attempt to open a file descriptor (existing file)
 *
 * Note that we assume that the file should be "binary"
 */
int fd_open(const char * file, int flags)
{
	char buf[1024];

	/* Hack -- Try to parse the path */
	if (path_parse(buf, sizeof(buf), file)) return (-1);

#if defined(MACINTOSH) || defined(WINDOWS)

	/* Attempt to open the file */
	return (open(buf, flags | O_BINARY));

#else

	/* Attempt to open the file */
	return (open(buf, flags | O_BINARY, 0));

#endif

}

/*
 * Hack -- attempt to lock a file descriptor
 *
 * Legal lock types -- F_UNLCK, F_RDLCK, F_WRLCK
 */
errr fd_lock(int fd, int what)
{
	/* Verify the fd */
	if (fd < 0) return (-1);

#ifdef SET_UID

	struct flock lock;

	lock.l_type = what;
	lock.l_start = 0; /* Lock the entire file */
	lock.l_whence = SEEK_SET; /* Lock the entire file */
	lock.l_len = 0; /* Lock the entire file */

	/* Wait for access and set lock status */
	/*
	 * Change F_SETLKW to F_SETLK if it's perferable to return
	 * without locking and reporting an error instead of waiting.
	 */
	return(fcntl(fd, F_SETLKW, &lock));


#else /* SET_UID */

	/* Unused parameter */
	(void)what;

#endif /* SET_UID */

	/* Success */
	return (0);
}

/** Byte-based IO and functions **/

/*
 * Hack -- attempt to seek on a file descriptor
 */
errr fd_seek(int fd, long n)
{
	long p;

	/* Verify fd */
	if (fd < 0) return (-1);

	/* Seek to the given position */
	p = lseek(fd, n, SEEK_SET);

	/* Failure */
	if (p < 0) return (1);

	/* Failure */
	if (p != n) return (1);

	/* Success */
	return (0);
}


#ifndef SET_UID
#define FILE_BUF_SIZE 16384
#endif

/*
 * Hack -- attempt to read data from a file descriptor
 */
errr fd_read(int fd, char *buf, size_t n)
{
	/* Verify the fd */
	if (fd < 0) return (-1);

#ifndef SET_UID

	/* Read pieces */
	while (n >= FILE_BUF_SIZE)
	{
		/* Read a piece */
		if (read(fd, buf, FILE_BUF_SIZE) != FILE_BUF_SIZE) return (1);

		/* Shorten the task */
		buf += FILE_BUF_SIZE;

		/* Shorten the task */
		n -= FILE_BUF_SIZE;
	}

#endif

	/* Read the final piece */
	if (read(fd, buf, n) != (long)n) return (1);

	/* Success */
	return (0);
}


/*
 * Hack -- Attempt to write data to a file descriptor
 */
errr fd_write(int fd, const char * buf, size_t n)
{
	/* Verify the fd */
	if (fd < 0) return (-1);

#ifndef SET_UID

	/* Write pieces */
	while (n >= FILE_BUF_SIZE)
	{
		/* Write a piece */
		if (write(fd, (void *)buf, FILE_BUF_SIZE) != FILE_BUF_SIZE) return (1);

		/* Shorten the task */
		buf += FILE_BUF_SIZE;

		/* Shorten the task */
		n -= FILE_BUF_SIZE;
	}

#endif

	/* Write the final piece */
	if (write(fd, (void *)buf, n) != (long)n) return (1);

	/* Success */
	return (0);
}


/*
 * Hack -- attempt to close a file descriptor
 */
errr fd_close(int fd)
{
	/* Verify the fd */
	if (fd < 0) return (-1);

	/* Close, return 0 on sucess, -1 on failure */
	return (close(fd));
}




