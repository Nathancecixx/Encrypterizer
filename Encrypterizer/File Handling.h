#pragma once
#include <stdbool.h>
#define CHUNKSIZE 16
#define NUMBEROFCHUNK 20

typedef struct Data {
    char text[NUMBEROFCHUNK][CHUNKSIZE];
    char password[CHUNKSIZE];
    char fileName[10];
    bool isEncrypted;
}DATA, * PDATA;

bool WriteToFile(PDATA dataPackage, char fileName[]);
bool ReadFromFile(PDATA dataPackage, char fileName[]);
