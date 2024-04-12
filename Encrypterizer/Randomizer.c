#define _CRT_SECURE_NO_WARNINGS
//Liam Cabarle - Randomizer Module
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Randomizer.h"

void generateRandomKey(char key[], size_t size) {
	//Seed the random number generator with the current time
	srand(time(NULL));

	// Generate random bytes
	for (size_t i = 0; i < size; i++) {
		int choice = rand() % 3;
		// Randomly choose between a letters or a digits
		if (choice == 0) {
			key[i] = 'A' + rand() % 26; //Uppercase letter
		}
		else if (choice == 1) {
			key[i] = 'a' + rand() % 26; //Lowercase letter
		}
		else {
			key[i] = '0' + rand() % 10; //digits 0 to 9
		}
	}
}