#define _CRT_SECURE_NO_WARNINGS

#include "File Handling.h"
#include <stdio.h>


bool WriteToFile(FILE_DATA* fd) {
    FILE* fp;

    if (fd->function_mode == ENCRYPT) {
        fp = fopen("Output.bin", "wb");
    }
    else {
        fp = fopen("Output.txt", "w");
    }

    if (fp == NULL) {
        printf("Error creating file\n");
        return false;
    }
    for (int i = 0; i < fd->numberOfChunks; i++) {
        fwrite(fd->fileText[i], sizeof(char), fd->sizeOfChunks, fp);
    }
    fclose(fp);
    return true;
}

bool ReadFromFile(FILE_DATA* fd) {
    FILE* fp;
    
    if (fd->function_mode == DECRYPT) {
        fp = fopen(fd->fileName, "rb");
    }
    else {
        fp = fopen(fd->fileName, "r");
    }

    if (fp == NULL) {
        printf("ERROR: Failed while opening file\n");
        return false;
    }

    for (int i = 0; i < fd->numberOfChunks; i++) {
        int Bytes_Read = fread(fd->fileText[i], sizeof(char), fd->sizeOfChunks, fp);
        fd->fileText[i][fd->sizeOfChunks] = '\0';
        if (Bytes_Read < fd->sizeOfChunks) {
            for (int j = Bytes_Read; j < fd->sizeOfChunks; j++) {
                fd->fileText[i][j] = '\0';
            }
        }
    }
    fclose(fp);

    if (fd->copy_mode == SHRED) {
        if (!remove(fd->fileName))
            printf("ERROR: Failed to delete original file");
    }
    return true;
}