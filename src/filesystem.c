#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* fs_read(const char *path) {

	FILE *file = fopen(path, "rb"); // Open the file in binary mode
	char *buffer = NULL;
	size_t length;

	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = (char *)malloc(length + 1);
		if (buffer) {

			if (!fread(buffer, 1, length, file)) {
				printf("Error reading file: %s\n", path);
			}

			buffer[length] = '\0';
		}

		fclose(file);
	}

	return buffer;
}

char* fs_read_bin(const char *path, size_t *size) {

	FILE *file = fopen(path, "rb"); // Open the file in binary mode
	char *buffer = NULL;
	size_t length;

	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = (char *)malloc(length);
		if (buffer) {

			if (!fread(buffer, 1, length, file)) {
				printf("Error reading file: %s\n", path);
			}
		}

		fclose(file);
	}

	return buffer;
}
int fs_cat(const char *first, const char *second, const char *path) {

	FILE *file1 = fopen(first, "rb"); // Open the file in binary mode
	if (file1 == NULL) {
        printf("Error opening file");
		return NULL;
    }

	FILE *file2 = fopen(second, "rb"); // Open the file in binary mode
	if (file2 == NULL) {
        printf("Error opening file");
        fclose(file1);
		return NULL;
    }

	FILE *dest = fopen(path, "wb");
    if (dest == NULL) {
        printf("Error opening output file");
        fclose(file1);
        fclose(file2);
		return NULL;
    }

	size_t length1;
	size_t length2;

	fseek(file1, 0, SEEK_END);
	length1 = ftell(file1);
	fseek(file1, 0, SEEK_SET);

	fseek(file2, 0, SEEK_END);
	length2 = ftell(file2);
	fseek(file2, 0, SEEK_SET);

	char *buffer = malloc(sizeof(char) * (length1 + length2));
	size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file1)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file2)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

	fclose(file1);
	fclose(file2);
	fclose(dest);

	free(buffer);
}

int fs_write(const char *path, const char *data) {

	FILE *file = fopen(path, "wb");

	if (file == NULL) {
		printf("Error opening file: %s\n", path);
		return 1;
	}

	fprintf(file, "%s", data);

    if (fclose(file) != 0) {
        printf("Error closing file");
    }

	return 0;
}
