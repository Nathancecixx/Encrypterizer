#define _CRT_SECURE_NO_WARNINGS

#include "File Handling.h"
#include <stdio.h>


bool WriteToFile(PDATA dataPackage, char fileName[]) {
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return false;
    }
    fprintf(fp, "%d", dataPackage->isEncrypted);
    fprintf(fp, "\n");
    fprintf(fp, "%s", dataPackage->password);
    fprintf(fp, "\n");
    fprintf(fp, "%s", dataPackage->text);
    fclose(fp);
    return true;
}

bool ReadFromFile(PDATA dataPackage, char fileName[]) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    int num;
    fscanf(fp, "%d", &num);
    if (num == 0) {
        dataPackage->isEncrypted = false;
    }
    else if (num == 1) {
        dataPackage->isEncrypted = true;
    }
    fscanf(fp, "\n");
    fgets(dataPackage->password, CHUNKSIZE, fp);
    dataPackage->password[strcspn(dataPackage->password, "\n")] = '\0';
    fgets(dataPackage->text, CHUNKSIZE * NUMBEROFCHUNK, fp);
    fclose(fp);
    return true;
}