#ifndef ARGS_H
#define ARGS_H

typedef struct {
	const char *project_path;
	const char *project_title;
	const char *love_version;
	int build_win;
	int build_linux;
	int build_mac;
} args;

args args_get(int argc, const char **argv);

#endif
