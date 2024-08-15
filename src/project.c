#include "project.h"
#include "manager.h"
#include <stdio.h>
#include <sys/stat.h>

project project_new(args args) {

	project proj;
	proj.args = args;

	sprintf(proj.build_dir, "%s/build", args.game_path);
	sprintf(proj.love_dir, "%s/build/love", args.game_path);

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


