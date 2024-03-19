#include "Encrypter.h"

bool Encrypt(FILE_DATA* fd) {
    for (int i = 0; i < fd->numberOfChunks; i++) {
        for (int j = 0; j < fd->sizeOfChunks; j++) {
            if (fd->fileText[i][j] == '\0') {
                break;
            }
            fd->fileText[i][j] ^= fd->key[j];
        }
    }
}

bool Decrypt(FILE_DATA* fd) {
        for (int i = 0; i < fd->numberOfChunks; i++) {
            for (int j = 0; j < fd->sizeOfChunks; j++) {
                if (fd->fileText[i][j] == '\0') {
                    break;
                }
                fd->fileText[i][j] ^= fd->key[j];
            }
        }

}