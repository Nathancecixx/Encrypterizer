#include <stdio.h>
#include "Randomizer.h"

int main(int argc, char* argv) {
	//testing for randomizer
	unsigned char key[16];
	generateRandomKey(key, sizeof(key));

	printf("Generated security key: ");
	for (size_t i = 0; i < sizeof(key); i++) {
		printf("%c", key[i]);
	}
	printf("\n");
	return 0;
}