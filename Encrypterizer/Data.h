#pragma once

#include "stdbool.h"

typedef enum { EMPTY, ENCRYPT, DECRYPT, COPY, SHRED, INPUT, GENERATE} ARGUMENT;

typedef struct File_Data {
	char* fileName;
	char** fileText;
	char* key;
	int numberOfChunks;
	int sizeOfChunks;
	ARGUMENT function_mode;
	ARGUMENT key_mode;
	ARGUMENT copy_mode;
}FILE_DATA;

bool InitFileData(FILE_DATA* fd, int argc, char* argv[]);

bool ParseArguments(FILE_DATA* fd, int argc, char* argv[]);

bool DestroyFileData(FILE_DATA* fd);