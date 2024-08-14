#include <stdio.h>
#include "args.h"
#include "project.h"

int main(int argc, const char **argv) {

	project proj = project_new(args_get(argc, argv));
}
