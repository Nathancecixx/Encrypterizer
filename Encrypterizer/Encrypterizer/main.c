#define _CRT_SECURE_NO_WARNINGS
//Liam Cabarle - Randomizer Module
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Randomizer.h"
#include "RandomizerUnitTests.h"

int main(void) {
	unsigned char key[16];
	generateRandomKey(key, sizeof(key));
	//does it print a random key
	printf("Generated security key: ");
	for (size_t i = 0; i < sizeof(key); i++) {
		printf("%c", key[i]);
	}
	printf("\n");

	testUppercaseLetters();
	testLowercaseLetters();
	testDigits();
	//testSrand();
	testRandModulo3();
	testArrayFill();

	return 0;
}