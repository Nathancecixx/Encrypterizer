#include "Encrypter.h"
#include <stdlib.h>
bool Encrypt(FILE_DATA* fd) {
    if (fd == NULL)
        return false;

    for (int i = 0; i < fd->numberOfChunks; i++) {
        for (int j = 0; j < fd->sizeOfChunks; j++) {
            fd->fileText[i][j] ^= fd->key[j];
        }
    }

    return true;
}

bool Decrypt(FILE_DATA* fd) {
    if (fd == NULL)
        return false;
    for (int i = 0; i < fd->numberOfChunks; i++) {
        for (int j = 0; j < fd->sizeOfChunks; j++) {
            fd->fileText[i][j] ^= fd->key[j];
        }
    }
    return true;
}