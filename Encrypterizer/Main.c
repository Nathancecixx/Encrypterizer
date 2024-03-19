#include <stdio.h>
#include <string.h>

#include "Data.h"
#include "File Handling.h"
#include "Encrypter.h"

void PrintHelp() {
	fprintf(stderr, "\nUsage: [FilePath] [Function_Mode] [Key_Mode] [Password]\n\n"
		"[FilePath]\n"
		"                Absolute or relative path Ex: ('Test.txt', 'C:\\Users\\nathan\\Documents\\test.txt') \n\n"

		"[Function_Mode]\n"
		"   -C           Copy the files contents to a new file, keeping the old one\n"
		"   -S           Copy the files contents to a new file, deleteing the old one\n\n"

		"[Key_Mode]\n"
		"   -P           Input a password to be used as the last param\n"
		"   -R           Generates a random password to encrypt the data with\n\n"

		"[Password]\n"
		"                Optional argument to be used if '-P' is enabled\n\n");
}

int main(int argc, char* argv[]) {
	FILE_DATA fd;

	if (!InitFileData(&fd, argc, argv)) {
		fprintf(stderr, "Error: failed to gather file data\n");
		PrintHelp();
		DestroyFileData(&fd);
		return 1;
	}

	if (!FileRead(&fd)) {
		fprintf(stderr, "Error: failed to read file\n");
		DestroyFileData(&fd);
		return 1;
	}

	printf("\nBefore encryption:\n");
	for (int i = 0; i < fd.numberOfChunks; i++) {
		printf("%s", fd.fileText[i]);
	}
	
	Encrypt(&fd);

	printf("\nAfter encryption:\n");
	for (int i = 0; i < fd.numberOfChunks; i++) {
		printf("%s", fd.fileText[i]);
	}

	Decrypt(&fd);

	printf("\nAfter decryption:\n");
	for (int i = 0; i < fd.numberOfChunks; i++) {
		printf("%s", fd.fileText[i]);
	}

	if (!FileWrite(&fd)) {
		fprintf(stderr, "Error: failed to write file\n");
		DestroyFileData(&fd);
		return 1;
	}

	DestroyFileData(&fd);

	return 0;
}