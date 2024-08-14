#include "project.h"
#include "manager.h"

project project_new(args args) {

	project proj;
	proj.args = args;

	if (proj.args.build_win) {
		manager_get(WIN_11_5);
	}

	if (proj.args.build_linux) {
		manager_get(LINUX_11_5);
	}

	project_build_love(&proj);

	return proj;
}


