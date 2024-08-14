#include <stdio.h>
#include "args.h"
#include "argparse.h"

static const char *const usages[] = {
    "love-builder [options] [[--] args]",
    "love-builder [options]",
    NULL,
};

args args_get(int argc, const char **argv) {

	args args;
	
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_BOOLEAN('w', "win", &args.build_win, "Build an exe for Windows.", NULL, 0, 0),
		OPT_BOOLEAN('l', "linux", &args.build_linux, "Build an AppImage for Linux.", NULL, 0, 0),
		OPT_BOOLEAN('m', "mac", &args.build_mac, "Build a dmg for Mac.", NULL, 0, 0),
		OPT_END(),
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usages, 0);
	argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
	argc = argparse_parse(&argparse, argc, argv);

	return args;
}
