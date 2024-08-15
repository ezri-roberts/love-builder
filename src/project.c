#include "project.h"
#include "manager.h"
#include <stdio.h>
#include <sys/stat.h>

project project_new(args args) {

	project proj;
	proj.args = args;

	if (args.project_title) {
		proj.name = (char*)args.project_title;
	} else {
		proj.name = _path_last((char*)args.project_path);
	}

	sprintf(proj.build_dir, "%s/build", args.project_path);
	sprintf(proj.love_dir, "%s/build/love", args.project_path);

	mkdir(proj.build_dir, 0755);
	mkdir(proj.love_dir, 0755);

	project_build_love(&proj);

	if (proj.args.build_win) {
		proj.version = WIN_11_5;
		manager_get(proj.love_dir, WIN_11_5);
		project_build_win(&proj);
	}

	if (proj.args.build_linux) {
		proj.version = LINUX_11_5;
		manager_get(proj.love_dir, LINUX_11_5);
	}

	return proj;
}

char* _path_last(char *path) {

    int init_size = strlen(path);
    char delim[] = "/";

    char *ptr = strtok(path, delim);
	char *last = NULL;

    while(ptr != NULL) {
        last = ptr; 
        ptr = strtok(NULL, delim);
    }

	return last;
}
