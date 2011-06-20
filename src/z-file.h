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

/**
 * Drop or grab privileges.
 *
 * This is used on multiuser systems, where the game wants to gain access to
 * system-wide files like the scores, raw files, or savefiles.  Reading from
 * these locations is permitted by anyone, but writing to them requires a call
 * to safe_setuid_grab() before opening the file for writing.
 *
 * safe_setuid_drop() should be called immediately after the file has been
 * opened, to prevent security risks, and restores the game's rights so that it
 * cannot write to the system-wide files.
 */
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

/** File handle creation **/

/**
 * Open file `buf`, returning a file handler representing that file.
 */
ang_file *file_open(const char *fname, file_mode mode, file_type ftype);

/**
 * Attempt to close the file handle `f`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_close(ang_file *f);


/** File locking **/

/**
 * Lock or unlock the file represented by `f` for writing.
 * If the file is not open for writing, this call will fail.
 *
 * If `f` is closed, the file is automatically unlocked.
 */
void file_lock(ang_file *f);
void file_unlock(ang_file *f);


/** Line-based IO **/

/**
 * Get a line of text from the file represented by `f`, placing it into `buf`
 * to a maximum length of `n`.
 *
 * This expands tabs, replaces non-printables with '?', and deals with differing
 * line endings.
 *
 * Returns TRUE when data is returned; FALSE otherwise.
 */
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

/**
 * Seek to position `pos` in the file represented by `f`.
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
bool file_seek(ang_file *f, u32b pos);

/**
 * Reads n bytes from file 'f' into buffer 'buf'.
 * \returns Number of bytes read; -1 on error
 */
int file_read(ang_file *f, char *buf, size_t n);

/**
 * Write the first `n` bytes following the pointer `buf` to the file represented
 * by `f`.  Do not mix with calls to file_writec().
 *
 * Returns TRUE if successful, FALSE otherwise.
 */
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
extern errr path_build(char *buf, int max, const char * path, const char * file);
extern FILE *my_fopen(const char * file, const char * mode);
extern errr my_fclose(FILE *fff);
extern errr my_fgets(FILE *fff, char *buf, size_t n);
extern errr my_fputs(FILE *fff, const char * buf, size_t n);
extern int fd_make(const char * file, int mode);
extern int fd_open(const char * file, int flags);
extern errr fd_lock(int fd, int what);
extern errr fd_seek(int fd, long n);
extern errr fd_read(int fd, char *buf, size_t n);
extern errr fd_write(int fd, const char * buf, size_t n);
extern errr fd_close(int fd);



#endif /* INCLUDED_Z_FILE_H */
