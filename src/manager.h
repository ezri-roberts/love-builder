#ifndef MANAGER_H
#define MANAGER_H

#include <curl/curl.h>
#include <string.h>


typedef enum {
	WIN_11_5,
	LINUX_11_5,
	OSX_11_5,
} VERSION;

int manager_get(const char *path, VERSION version);
size_t manager_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif
