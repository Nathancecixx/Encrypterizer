#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Data.h"

#define FILE_PATH_ARG		1
#define FUNCTION_MODE_ARG	2
#define KEY_MODE_ARG		3
#define PASSWORD_ARG		4
#define NUM_OF_POTENTIAL_ARGS	2


bool InitFileData(FILE_DATA* fd, int argc, char* argv[]) {

	if (argc > 5 || argc < 3) {
		return false;
	}

	// Initialize all attributes
	fd->fileName = NULL;
	fd->fileText = NULL;
	fd->key = NULL;
	fd->numberOfChunks = 0;
	fd->sizeOfChunks = 0;


	/*****************
	 * Set File Name *
	 *****************/
	//Get the file path length
	int FileNameLength = strlen(argv[FILE_PATH_ARG]) + 1; 
	//Allocate memory for the file path string
	fd->fileName = (char*)malloc(sizeof(char) * FileNameLength);
	if (fd->fileName == NULL) {
		return false;
	}
	//Copy argument to the allocated memory (+1 to account for '\n')
	strncpy(fd->fileName, argv[FILE_PATH_ARG], FileNameLength);

	/********************************
	 * Parse Command Line Arguments *
	 ********************************/
	// Parse the flags from the arguments
	for (int i = 0; i < NUM_OF_POTENTIAL_ARGS; i++) {
		//Checks that '-' is infront of argument so its a valid flag
		if (argv[i + 2][0] != '-') {
			return false;
		}

		//Argument is a flag, save the char and execute the correct switch case for that flag.
		char arg = argv[i + 2][1];
		
		switch (arg) {
		case('C'):
			fd->function_mode = COPY;
			break;
		case('S'):
			fd->function_mode = SHRED;
			break;
		case('P'):
			fd->key_mode = INPUT;
			break;
		case('R'):
			fd->key_mode = GENERATE;
			break;
		}
	}


	/*******************
	 * Handle KEY_MODE *
	 *******************/

	//Handle Input mode
	if (fd->key_mode == INPUT) {
		//Checks if the position for password is filled.
		if (argv[PASSWORD_ARG] == NULL) {
			fd->key = NULL;
			return false;
		}
		//Position is filled so we can get the password from arguments
		int passlength = strlen(argv[PASSWORD_ARG]) + 1;
		fd->key = (char*)malloc(sizeof(char) * passlength);
		if (fd->key == NULL) {
			return false;
		}

		strncpy(fd->key, argv[PASSWORD_ARG], passlength);
		fd->sizeOfChunks = passlength;
	}
	else if (fd->key_mode == GENERATE) {
		// TODO:
		//Insert random pass generator
		return false;
	}

	/*********************
	 * Set num of chunks *
	 *********************/
	//Open the file to read its size
	FILE* fp = fopen(fd->fileName, "r");
	if (fp == NULL)
		return false;

	//Get the size of file
	fseek(fp, 0L, SEEK_END);
	int totalChars = ftell(fp);
	fclose(fp);

	//Calculate num of chunks
	fd->numberOfChunks = totalChars / fd->sizeOfChunks;
	//Check if theres a remainder and if so add an extra chunk to accomidate
	if (totalChars % fd->sizeOfChunks != 0) {
		fd->numberOfChunks++;
	}


	/*********************
	 * Allocate fileText *
	 *********************/
	
	//Allocate chunk pointers
	fd->fileText = (char**)malloc( sizeof(char*) * fd->numberOfChunks );
	if (fd->fileText == NULL)
		return false;
	//Allocate each chunk to the pointers
	for (int i = 0; i < fd->numberOfChunks; i++) {
		fd->fileText[i] = (char*) malloc ( sizeof(char) * (fd->sizeOfChunks + 1) );
		if (fd->fileText[i] == NULL)
			return false;
	}

	return true;
}

//Checks to see if any of the allocated memory is currently allocated, if so deallocate it.
bool DestroyFileData(FILE_DATA* fd) {
	if (fd->fileName != NULL) {
		free(fd->fileName);

	}

	if (fd->fileText != NULL) {
		for (int i = 0; i < fd->numberOfChunks; i++) {
			if (fd->fileText[i] != NULL) {
				free(fd->fileText[i]);
			}
		}
		free(fd->fileText);
		fd->fileText = NULL;
	}

	if (fd->key != NULL)
		free(fd->key);

	return true;
}