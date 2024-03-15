#define _CRT_SECURE_NO_WARNINGS

#include "File Handling.h"
#include <stdio.h>


bool FileRead(DATA data) {
	FILE* fp;
	fp = fopen(data.fileName, "r");
	if (fp == NULL) {
		printf("Could not open file.\n");
		return false;
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			data.message[i][j] = fgetc(fp);
			if (feof(fp)) {
				break;
			}
		}
	}
	fclose(fp);
	return true;
}

bool FileWrite(DATA data) {
	FILE* fp;
	fp = fopen(data.fileName, "w");
	if (fp == NULL) {
		printf("Could not open file.\n");
		return false;
	}
	fprintf(fp, data.key);
	fprintf(fp, "\n");
	fprintf(fp, data.message);
	fclose(fp);
	return true;
}