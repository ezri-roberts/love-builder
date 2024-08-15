#include <stdio.h>
#include "args.h"
#include "argparse.h"

static const char *const usages[] = {
    "love-builder [options] [[--] args]",
    "love-builder [options]",
    NULL,
};

args args_get(int argc, const char **argv) {

	args args = {
		.project_path = NULL,
		.project_title = NULL,
		.love_version = NULL,
		.build_win = NULL,
		.build_linux = NULL,
		.build_mac = NULL,
	};
	
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Build options"),
		OPT_BOOLEAN('w', "win", &args.build_win, "Build a Windows executable.", NULL, 0, 0),
		OPT_BOOLEAN('a', "linux", &args.build_linux, "Build a Linux AppImage.", NULL, 0, 0),
		OPT_BOOLEAN('m', "mac", &args.build_mac, "Build a macOS application.", NULL, 0, 0),
		OPT_STRING('l', "love", &args.love_version, "The Love version to use.", NULL, 0, 0),
		OPT_STRING('p', "path", &args.project_path, "Project path.", NULL, 0, 0),
		OPT_STRING('t', "title", &args.project_title, "Project title.", NULL, 0, 0),
		OPT_END(),
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usages, 0);
	argparse_describe(&argparse, "\nA tool for building Love projects for different desktop platforms.", "\nSupports Windows, macOS, and Linux.");
	argc = argparse_parse(&argparse, argc, argv);

	return args;
}
