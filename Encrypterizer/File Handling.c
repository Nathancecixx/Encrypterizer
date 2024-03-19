#define _CRT_SECURE_NO_WARNINGS

#include "File Handling.h"
#include <stdio.h>

bool FileRead(FILE_DATA* data) {
	FILE* fp;
	fp = fopen(data->fileName, "r");
	if (fp == NULL) {
		printf("Could not open file.\n");
		return false;
	}
	for (int i = 0; i < data->numberOfChunks; i++) {
		for (int j = 0; j < data->sizeOfChunks; j++) {
			int c = fgetc(fp);
			if (feof(fp)) {
				data->fileText[i][j] = '\0';
				break;
			}
			data->fileText[i][j] = (char) c;
		}
		data->fileText[i][data->sizeOfChunks] = '\0';
	}

	fclose(fp);
	return true;
}



bool FileWrite(FILE_DATA* fd) {
	FILE* fp;
	fp = fopen("output.txt", "w");
	if (fp == NULL) {
		return false;
	}
	fprintf(fp, fd->fileText);
	fclose(fp);
	return true;
}
