#include "File Handling.h"
#include "Encrypt.h"

void Encrypt(PDATA dataPackage) {
    dataPackage->isEncrypted = true;

    for (int i = 0; i < NUMBEROFCHUNK; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            dataPackage->text[i][j] = dataPackage->text[i][j] ^ dataPackage->password[j];
        }
    }
}

void Decrypt(PDATA dataPackage) {
    dataPackage->isEncrypted = false;
    for (int i = 0; i < NUMBEROFCHUNK; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            dataPackage->text[i][j] = dataPackage->text[i][j] ^ dataPackage->password[j];
        }
    }
}