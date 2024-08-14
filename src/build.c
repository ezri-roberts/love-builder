#include "project.h"
#include <dirent.h>
#include <limits.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void project_build_love(project *proj) {

	struct zip_t *zip = zip_open("game.love", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	_zip_dir(proj, zip, proj->args.game_path);
	zip_close(zip);
}

int _zip_dir(project *proj, struct zip_t *zip, const char *path) {

	struct dirent *de;

	DIR *dr = opendir(path);
	FILE *fp;

	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
	{ 
		printf("Could not open current directory" ); 
		return 1; 
	} 

	while ((de = readdir(dr)) != NULL) {
		// Skip hidden files.
		if (de->d_name[0] == '.') continue;

		char fullpath[PATH_MAX];
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, de->d_name);

		char *relative_path = _strip_path(fullpath);

		if (de->d_type == DT_DIR) {

			_zip_dir(proj, zip, fullpath);
		} else if (de->d_type == DT_REG) {

			char *data = _read_file(fullpath);

			zip_entry_open(zip, relative_path);
			zip_entry_write(zip, data, strlen(data));
			zip_entry_close(zip);

			free(data);
		}
	}

	closedir(dr);

	return 0;
}

char* _strip_path(const char *path) {

	// Find the first occurrence of the path separator '/'
	const char *separator = strchr(path, '/');

	// If the separator is found, return the substring after it
	if (separator != NULL) {
		return (char*)(separator + 1);  // Skip the separator itself
	} else {
		// If no separator is found, return the original string
		return (char*)path;
	}
}

char* _read_file(const char *path) {

	FILE *file = fopen(path, "rb"); // Open the file in binary mode
	char *buffer = NULL;
	size_t length;

	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = (char *)malloc(length + 1);
		if (buffer) {
			if (!fread(buffer, 1, length, file)) {
				printf("Error reading file: %s\n", path);
			}
			buffer[length] = '\0';
		}

		fclose(file);
	}

	return buffer;
}
