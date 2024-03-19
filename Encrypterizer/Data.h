#pragma once

#include "stdbool.h"

typedef enum { COPY, SHRED } FUNCTION_MODE;
typedef enum { INPUT, GENERATE } KEY_MODE;

typedef struct File_Data {
	char* fileName;
	int numberOfChunks;
	int sizeOfChunks;
	char** fileText;
	FUNCTION_MODE function_mode;
	KEY_MODE key_mode;
	char* key;
}FILE_DATA;

bool InitFileData(FILE_DATA* fd, int argc, char* argv[]);

bool DestroyFileData(FILE_DATA* fd);