#define _CRT_SECURE_NO_WARNINGS

#include "File Handling.h"
#include <stdio.h>


bool FileRead(char arr[], char key[], char fileName[]) {
	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Could not open file.\n");
		return false;
	}
	int i = 0;
	while (true) {
		arr[i] = fgetc(fp);
		i++;
		if (feof(fp)) {
			break;
		}
	}
	fclose(fp);
	return true;
}

bool FileWrite(char arr[], char key[], char fileName[]) {
	FILE* fp;
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Could not open file.\n");
		return false;
	}
	fprintf(fp, key);
	fprintf(fp, "\n");
	fprintf(fp, arr);
	fclose(fp);
	return true;
}