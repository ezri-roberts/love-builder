#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <sys/types.h>

char* fs_read(const char *path);
char* fs_read_bin(const char *path, size_t *size);
int fs_write(const char *path, const char *data);
int fs_cat(const char *first, const char *second, const char *path);

#endif
