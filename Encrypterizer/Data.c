#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Data.h"
#include "Randomizer.h"

#define FILE_PATH_ARG		1
#define FUNCTION_MODE_ARG	2
#define KEY_MODE_ARG		3
#define PASSWORD_ARG		4
#define NUM_OF_POTENTIAL_ARGS	3


bool InitFileData(FILE_DATA* fd, int argc, char* argv[]) {

	// Initialize all attributes
	fd->fileName = NULL;
	fd->fileText = NULL;
	fd->key = NULL;
	fd->numberOfChunks = 0;
	fd->sizeOfChunks = 0;
	fd->function_mode = EMPTY;
	fd->key_mode = EMPTY;
	fd->copy_mode = EMPTY;

	if (argc > 6 || argc < 3) {
		fprintf(stderr, "Error: Incorrect number of args\n");
		return false;
	}

	/*****************
	 * Set File Name *
	 *****************/
	 //Get the file path length
	int FileNameLength = strlen(argv[FILE_PATH_ARG]) + 1;
	//Allocate memory for the file path string
	fd->fileName = (char*)malloc(sizeof(char) * FileNameLength);
	if (fd->fileName == NULL) {
		fprintf(stderr, "Error: Failed to malloc\n");
		return false;
	}
	//Copy argument to the allocated memory
	strncpy(fd->fileName, argv[FILE_PATH_ARG], FileNameLength);

	ParseArguments(fd, argc, argv);

	/*******************
	 * Handle KEY_MODE *
	 *******************/

	 //Handle Input mode
	if (fd->key_mode == INPUT) {
		//Checks if the position for password is filled.
		if (argv[argc - 1][0] == '-') {
			fd->key = NULL;
			fprintf(stderr, "Error: Failed to provide password\n");
			return false;
		}
		//Position is filled so we can get the password from arguments
		int passlength = strlen(argv[argc - 1]) + 1;
		fd->key = (char*)malloc(sizeof(char) * passlength);
		if (fd->key == NULL) {
			return false;
		}

		strncpy(fd->key, argv[argc - 1], passlength);
		fd->sizeOfChunks = passlength;
	}
	else if (fd->key_mode == GENERATE) {
		// TODO:
		//Fix pass generator
		int passlength = 11;
		fd->key = (char*)malloc(sizeof(char) * passlength);
		if (fd->key == NULL) {
			return false;
		}
		generateRandomKey(fd->key, passlength - 1);
		fd->sizeOfChunks = passlength;
		fd->key[passlength - 1] = '\0';

		printf("Your generated decryption key: %s\n", fd->key);
	}

	/*********************
	 * Set num of chunks *
	 *********************/
	 //Open the file to read its size
	FILE* fp = fopen(fd->fileName, "r");
	if (fp == NULL) {
		printf("ERROR: Failed while opening file\n");
		return false;
	}

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
	fd->fileText = (char**)malloc(sizeof(char*) * fd->numberOfChunks);
	if (fd->fileText == NULL)
		return false;
	//Allocate each chunk to the pointers
	for (int i = 0; i < fd->numberOfChunks; i++) {
		fd->fileText[i] = (char*)malloc(sizeof(char) * (fd->sizeOfChunks + 1));
		if (fd->fileText[i] == NULL)
			return false;
	}

	return true;
}

bool ParseArguments(FILE_DATA* fd, int argc, char* argv[]) {
	// Parse the flags from the arguments
	for (int i = 0; i < argc; i++) {
		//Checks that '-' is infront of argument so its a valid flag
		if (argv[i][0] != '-') {
			continue;
		}

		//Argument is a flag, save the char and execute the correct switch case for that flag.
		char arg = argv[i][1];

		switch (arg) {
		case('C'):
			fd->copy_mode = COPY;
			break;
		case('S'):
			fd->copy_mode = SHRED;
			break;
		case('P'):
			fd->key_mode = INPUT;
			break;
		case('R'):
			fd->key_mode = GENERATE;
			break;
		case ('E'):
			fd->function_mode = ENCRYPT;
			break;
		case('D'):
			fd->function_mode = DECRYPT;
			break;
		default:
			continue;
		}
	}

	if (fd->function_mode == EMPTY) {
		fprintf(stderr, "Error: Failed to parse arguments\n");
		return false;
	}

	if (fd->key_mode == EMPTY)
		fd->key_mode = GENERATE;

	if (fd->copy_mode == EMPTY)
		fd->copy_mode = COPY;

	return true;
}


//Checks to see if any of the allocated memory is currently allocated, if so deallocate it.
bool DestroyFileData(FILE_DATA* fd) {
	if (fd->fileName != NULL) {
		free(fd->fileName);
		fd->fileName = NULL;

	}

	if (fd->fileText != NULL) {
		for (int i = 0; i < fd->numberOfChunks; i++) {
			if (fd->fileText[i] != NULL) {
				free(fd->fileText[i]);
				fd->fileText[i] = NULL;
			}
		}
		free(fd->fileText);
		fd->fileText = NULL;
	}

	if (fd->key != NULL) {
		free(fd->key);
		fd->key = NULL;
	}

	return true;
}