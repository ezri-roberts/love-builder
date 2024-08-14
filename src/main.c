#include <stdio.h>
#include "manager.h"

int main(int argc, char** argv) {

	if(manager_get(LINUX_11_5) == 0) {
		printf("Download successfull.\n");
	} else {
		printf("Download failed!\n");
	}
    return 0;
}
