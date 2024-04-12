#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../Encrypterizer/Data.h"
#include "../Encrypterizer/Encrypter.h"
#include "../Encrypterizer/Randomizer.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EncrypterizerTests
{
	TEST_CLASS(FileHandlingModule)
	{
	public: 

		TEST_METHOD(TestMethod1)
		{
		}
	};

	TEST_CLASS(EncrypterModule)
	{
	public:

		TEST_METHOD(REQ_ENC_001_ReceiveFileData)
		{
			FILE_DATA fd;
			int argc = 5;
			char* argv[] = { "./Encrypterizer", "Test.txt", "-E", "-P", "Password" };
			InitFileData(&fd, argc, argv);

			// Test that the Encrypter module accepts FILE_DATA without errors
			Assert::IsTrue(Encrypt(&fd));
			Assert::IsTrue(Decrypt(&fd));

			// Clean up
			DestroyFileData(&fd);

		}

		TEST_METHOD(REQ_ENC_002_ExecuteEncryptDecrypt)
		{
			FILE_DATA fd;
			int argc = 5;
			char* argv[] = { "./Encrypterizer", "Test.txt", "-E", "-P", "Password" };
			InitFileData(&fd, argc, argv);

			char** OG = new(char*);

			Encrypt(&fd);
			Decrypt(&fd);

			// Compare the original and decrypted files to confirm they are identical
			// ...

			// Clean up
			DestroyFileData(&fd);
		}

		TEST_METHOD(REQ_ENC_003_CleanExitOnError)
		{
			FILE_DATA* fd = nullptr;

			// Pass a NULL pointer or an incorrectly typed pointer to the Encrypter functions
			Assert::IsFalse(Encrypt(fd));
			Assert::IsFalse(Decrypt(fd));
		}

	};
	TEST_CLASS(RandomizerModule)
	{
	public:

		TEST_METHOD(REQ_SYS_041_Uppercase)
		{
			unsigned char key[16];
			generateRandomKey(key, sizeof(key));
			//letter count
			int hasUppercase = 0;
			//goes through array and counts how many uppercase letters there are
			for (size_t i = 0; i < sizeof(key); i++) {
				if (isupper(key[i])) {
					hasUppercase++;
				}
			}
			//no uppercase letters = error
			if (!hasUppercase) {
				printf("Error: Key does not have an uppercase letter\n");
			}
			else {
				printf("The key has %d uppercase letters\n", hasUppercase);
			}
		}
		TEST_METHOD(REQ_SYS_041_Lowercase)
		{
			unsigned char key[16];
			generateRandomKey(key, sizeof(key));
			//letter counter
			int hasLowercase = 0;
			//goes through array and counts the lowercase letters
			for (size_t i = 0; i < sizeof(key); i++) {
				if (islower(key[i])) {
					hasLowercase++;
				}
			}
			//no lowercase letters = error
			if (!hasLowercase) {
				printf("Error: Key does not have a lowercase letter\n");
			}
			else {
				printf("Test passed! The key has %d lowercase letters\n", hasLowercase);
			}
		}
		TEST_METHOD(REQ_SYS_041_Digit)
		{
			unsigned char key[16];
			generateRandomKey(key, sizeof(key));
			//digit counter
			int hasDigit = 0;
			//iterates through the array and counts the digits
			for (size_t i = 0; i < sizeof(key); i++) {
				if (isdigit(key[i])) {
					hasDigit++;
				}
			}
			//no digits = error
			if (!hasDigit) {
				printf("Error: Key does not have digits\n");
			}
			else {
				printf("Test passed! The key has %d digits\n", hasDigit);
			}
		}
		TEST_METHOD(REQ_SYS_042_ModifyArray)
		{
			//empty array
			unsigned char key[16] = { 0 };

			generateRandomKey(key, sizeof(key));
			//goes through the array
			for (size_t i = 0; i < sizeof(key); i++) {
				//if array is empty = error
				if (key[i] == 0) {
					printf("Array was not filled\n");
				}
				else { //array is filled and it prints the array
					printf("Test passed. Array was filled\n");
				}
			}
		}
		TEST_METHOD(REQ_SYS_043_Rand)
		{
			int counts[3] = { 0 };
			//makes choices 100 times to check if random numbers are chosen
			for (int i = 0; i < 100; i++) {
				int choice = rand() % 3;
				counts[choice]++;
			}
			//if 0 is chosen
			if (counts[0] <= 0) {
				printf("Error: rand() %% 3 never returns 0\n");
			}
			else {
				printf("Test passed. 0 was randomly chosen\n");
			}
			//if 1 is chosen
			if (counts[1] <= 0) {
				printf("Error: rand() %% 3 never returns 1\n");
			}
			else {
				printf("Test passed. 1 was randomly chosen\n");
			}
			//if 2 is chosen
			if (counts[2] <= 0) {
				printf("Error: rand() %% 3 never returns 2\n");
			}
			else {
				printf("Test passed. 2 was randomly chosen\n");
			}
		}
		TEST_METHOD(REQ_SYS_044_SRandTime)
		{
			unsigned char key1[16];
			unsigned char key2[16];
			srand(time(NULL));
			generateRandomKey(key1, sizeof(key1) - 1);
			key1[sizeof(key1) - 1] = '\0';
			printf("This is key 1: %s\n", key1);
			srand(time(NULL));
			generateRandomKey(key2, sizeof(key2) - 1);
			key2[sizeof(key2) - 1] = '\0';
			printf("This is key 2: %s\n", key2);

			if (memcmp(key1, key2, sizeof(key1)) == 0) {
				printf("Error: Keys generated are the same\n");
			}
			else {
				printf("Test passed! Keys are different\n");
			}
		}
	};
	};
}
