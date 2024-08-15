#include "project.h"
#include "filesystem.h"
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

static char* names[VERSION_MAX] = {
	"love-11.5-win64/love.exe",
	"love-11.5-macos/",
	"love-11.5-x86_64.AppImage",
};

void project_build_love(project *proj) {

	char game_path[PATH_MAX];
	sprintf(game_path, "%s/%s.love", proj->build_dir, proj->name);

	struct zip_t *zip = zip_open(game_path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	_zip_dir(proj, zip, proj->args.project_path);
	zip_close(zip);
}

void project_build_win(project *proj) {

	char version_path[PATH_MAX];
	char love_path[PATH_MAX];
	char exe_path[PATH_MAX];
	
	sprintf(version_path, "%s/%s", proj->love_dir, names[proj->version]); 
	sprintf(love_path, "%s/%s.love", proj->build_dir, proj->name); 
	sprintf(exe_path, "%s/%s.exe", proj->love_dir, proj->name); 

	fs_cat(version_path, love_path, exe_path);
	remove(version_path);
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

			if (strcmp(de->d_name, "build") != 0) {
				_zip_dir(proj, zip, fullpath);
			}
		} else if (de->d_type == DT_REG) {

			char *data = fs_read(fullpath);

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
