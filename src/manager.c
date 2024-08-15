#include "manager.h"
#include "project.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char* names[VERSION_MAX] = {
	"love-11.5-win64.zip",
	"love-11.5-macos.zip",
	"love-11.5-x86_64.AppImage",
};

int manager_get(const char *path, VERSION version) {

	CURL *curl;
	FILE *file;
	CURLcode res;

	char url[1024];
	char dest[PATH_MAX];

	const char *base_url = "https://github.com/love2d/love/releases/download/";

	sprintf(url, "%s11.5/%s", base_url, names[version]);
	sprintf(dest, "%s/%s", path, names[version]);

	printf("%s, %s\n", url, dest);

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

	// Window and Mac versions are zip files.
	if (version != LINUX_11_5) {
		int arg = 2;
		zip_extract(dest, path, _on_extract, &arg);
		remove(dest);
	}

	return 0;
}

int _on_extract(const char *filename, void *arg) {
	static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

    return 0;
}

size_t manager_write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}
