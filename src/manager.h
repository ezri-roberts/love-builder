#ifndef MANAGER_H
#define MANAGER_H

#include <curl/curl.h>
#include <string.h>


typedef enum {
	WIN_11_5 = 0,
	OSX_11_5 = 1,
	LINUX_11_5 = 2,
	VERSION_MAX = 3,
} VERSION;

int manager_get(const char *path, VERSION version);
size_t manager_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
int _on_extract(const char *filename, void *arg);

#endif
