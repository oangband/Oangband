#ifndef INCLUDED_Z_FILE_H
#define INCLUDED_Z_FILE_H

#include "h-basic.h"

/*** Permissions code ***/

/**
 * Player's user ID and group ID, respectively.
 *
 * Only relevant to POSIX systems that use main.c, and set there.
 */
extern int player_uid;
extern int player_egid;

void safe_setuid_grab(void);
void safe_setuid_drop(void);


/*** File access code ***/

/** Data types **/

/**
 * An opaque file handle for Angband file handling.
 */
typedef struct ang_file ang_file;

/**
 * Specifies what kind of access is required to a file.  See file_open().
 */
typedef enum
{
	MODE_WRITE,
	MODE_READ,
	MODE_APPEND
} file_mode;

/**
 * Specifies what kind of thing a file is, when writing.  See file_open().
 */
typedef enum
{
	FTYPE_TEXT = 1,
	FTYPE_SAVE,
	FTYPE_RAW,
	FTYPE_HTML
} file_type;

/** Utility functions **/

/**
 * Tries to delete `fname`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_delete(const char *fname);

/**
 * Moves the file `fname` to `newname`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_move(const char *fname, const char *newname);

ang_file *file_open(const char *fname, file_mode mode, file_type ftype);

/**
 * Attempt to close the file handle `f`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_close(ang_file *f);

/** Line-based IO **/

bool file_getl(ang_file *f, char *buf, size_t n);

/**
 * Write the string pointed to by `buf` to the file represented by `f`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_put(ang_file *f, const char *buf);

/**
 * Format (using strnfmt) the given args, and then call file_put().
 */
bool file_putf(ang_file *f, const char *fmt, ...);
bool file_vputf(ang_file *f, const char *fmt, va_list vp);

/** Byte-based IO */

bool file_write(ang_file *f, const char *buf, size_t n);

/**
 * Read a byte from the file represented by `f` and place it at the location
 * specified by 'b'.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_readc(ang_file *f, byte *b);

/**
 * Write the byte `b` to the file represented by `f`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_writec(ang_file *f, byte b);

extern errr path_parse(char *buf, int max, const char * file);
extern errr path_temp(char *buf, int max);
extern errr path_build(char *buf, int max, const char * path, const char * file);
extern FILE *my_fopen(const char * file, const char * mode);
extern FILE *my_fopen_temp(char *buf, size_t max);
extern errr my_fclose(FILE *fff);
extern errr my_fgets(FILE *fff, char *buf, size_t n);
extern errr my_fputs(FILE *fff, const char * buf, size_t n);
extern errr fd_copy(const char * file, const char * what);
extern int fd_make(const char * file, int mode);
extern int fd_open(const char * file, int flags);
extern errr fd_lock(int fd, int what);
extern errr fd_seek(int fd, long n);
extern errr fd_read(int fd, char *buf, size_t n);
extern errr fd_write(int fd, const char * buf, size_t n);
extern errr fd_close(int fd);



#endif /* INCLUDED_Z_FILE_H */
