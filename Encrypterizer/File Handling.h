#pragma once
#include <stdbool.h>
typedef struct Data {
	bool password; //0 for self-created password, 1 for random generated password
	char message[100][100];
	char fileName[10];
	char key[16];
	int fileSize;
	bool fileEmpty;
	bool encrypted; //1 if the message is encrypted, 0 if the message is decrypted
}DATA;
bool FileRead(DATA data);
bool FileWrite(DATA data);

int FileSize(DATA data);
bool FileEmpty(DATA data);