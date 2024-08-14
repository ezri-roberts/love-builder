#include "manager.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <string.h>

int manager_get(const char *path, VERSION version) {

	CURL *curl;
	FILE *file;
	CURLcode res;

	char url[1024];
	char dest[256];
	strcpy(url, "https://github.com/love2d/love/releases/download/");
	strcpy(dest, path);

	switch (version) {
		case WIN_11_5:
			strcat(dest, "/love-11.5-win64.zip");
			strcat(url, "11.5/love-11.5-win64.zip");
			break;
		case LINUX_11_5:
			strcat(dest, "/love-11.5-x86_64.AppImage");
			strcat(url, "11.5/love-11.5-x86_64.AppImage");
			break;
		case OSX_11_5:
			strcat(dest, "/love-11.5-macos.zip");
			strcat(url, "11.5/love-11.5-macos.zip");
			break;
	}

	curl = curl_easy_init();

	if (!curl) {
		printf("Failed to init curl.\n");
		return 1;
	}

	file = fopen(dest, "wb");

	if (!file) {
		printf("Failed to open %s\n", dest);
		return 1;
	}

	// Set curl opts.
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, manager_write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	res = curl_easy_perform(curl);

	fclose(file);

	if (res != CURLE_OK) {
		printf("Download failed: %s\n", curl_easy_strerror(res));
		return 1;
	}

	curl_easy_cleanup(curl);

	return 0;
}

size_t manager_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}
