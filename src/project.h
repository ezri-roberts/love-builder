#ifndef PROJECT_H
#define PROJECT_H

#include "args.h"
#include "../lib/zip/src/zip.h"

typedef struct {
	args args;
	char *root_dir;
} project;

project project_new(args args);
void project_build_love(project *proj);

char* _strip_path(const char *path);
char* _read_file(const char *path);
int _zip_dir(project *proj, struct zip_t *zip, const char *path);

#endif
