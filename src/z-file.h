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

extern errr path_parse(char *buf, int max, const char * file);
extern errr path_temp(char *buf, int max);
extern errr path_build(char *buf, int max, const char * path, const char * file);
extern FILE *my_fopen(const char * file, const char * mode);
extern FILE *my_fopen_temp(char *buf, size_t max);
extern errr my_fclose(FILE *fff);
extern errr my_fgets(FILE *fff, char *buf, size_t n);
extern errr my_fputs(FILE *fff, const char * buf, size_t n);
extern errr fd_kill(const char * file);
extern errr fd_move(const char * file, const char * what);
extern errr fd_copy(const char * file, const char * what);
extern int fd_make(const char * file, int mode);
extern int fd_open(const char * file, int flags);
extern errr fd_lock(int fd, int what);
extern errr fd_seek(int fd, long n);
extern errr fd_read(int fd, char *buf, size_t n);
extern errr fd_write(int fd, const char * buf, size_t n);
extern errr fd_close(int fd);


void safe_setuid_drop(void);
void safe_setuid_grab(void);

#endif /* INCLUDED_Z_FILE_H */
