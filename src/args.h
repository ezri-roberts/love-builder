#ifndef ARGS_H
#define ARGS_H

typedef struct {
	const char *game_path;
	const char *build_version;
	int build_win;
	int build_linux;
	int build_mac;
} args;

args args_get(int argc, const char **argv);

#endif
