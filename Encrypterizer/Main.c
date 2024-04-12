#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Data.h"
#include "File Handling.h"
#include "Encrypter.h"

void PrintHelp() {
	fprintf(stdout, "\nUsage: [FilePath] [Function_Mode] [Key_Mode] [Copy_Mode] [Password]\n\n"
		"[FilePath]\n"
		"                Absolute or relative path Ex: ('Test.txt', 'C:\\Users\\nathan\\Documents\\test.txt') \n\n"

		"[Function_Mode]\n"
		"   -E           Perform Encryption on a file\n"
		"   -D           Perform Decryption on a file\n\n"

		"[Key_Mode]\n"
		"   -P           Input a password to be used as the last param\n"
		"   -R           Generates a random password to encrypt the data with\n\n"

		"[Copy_Mode]\n"
		"   -C           Copy the files contents to a new file, keeping the old one\n"
		"   -S           Copy the files contents to a new file, deleteing the old one\n\n"

		"[Password]\n"
		"                Optional argument to be used if '-P' is enabled\n\n");
}

int main(int argc, char* argv[]) {
	FILE_DATA fd;

	if (!InitFileData(&fd, argc, argv)) {
		PrintHelp();
		DestroyFileData(&fd);
		exit(EXIT_FAILURE);
	}

	//TODO:
	/*
	if(!ParseArguments(&fd, argc, argv)) {
		PrintHelp();
		DestroyFileData(&fd);
		return 1;
	}
	*/

	if (!ReadFromFile(&fd)) {
		fprintf(stderr, "Error: failed to read file\n");
		DestroyFileData(&fd);
		exit(EXIT_FAILURE);
	}

	printf("File Size: %d\n", fd.sizeOfChunks * fd.numberOfChunks);

	/*
	printf("\n\n\nBefore encryption:\n");
	for (int i = 0; i < fd.numberOfChunks; i++) {
		printf("%s\n", fd.fileText[i]);
	}
	*/

	Encrypt(&fd);

	/*
	printf("\n\n\nAfter encryption:\n");
	for (int i = 0; i < fd.numberOfChunks; i++) {
		printf("%s", fd.fileText[i]);
	}
	*/
	printf("\n");

	if (!WriteToFile(&fd)) {
		fprintf(stderr, "Error: failed to write file\n");
		DestroyFileData(&fd);
		exit(EXIT_FAILURE);
	}

	DestroyFileData(&fd);

	return 0;
}