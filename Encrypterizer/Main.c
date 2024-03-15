#include "File Handling.h"
#include <stdio.h>
#include <string.h>

int main() {
	FileWrite("test message", "Test key", "test.txt");

	FILE* fp = fopen("test.txt", "r");
	fseek(fp, 0L, SEEK_END);
	printf("%d", ftell(fp));
	fclose(fp);
}