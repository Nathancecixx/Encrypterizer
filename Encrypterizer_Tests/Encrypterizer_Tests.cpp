#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../Encrypterizer/Data.h"
#include "../Encrypterizer/Encrypter.h"
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

		TEST_METHOD(TestMethod1)
		{
		}
	};
}
