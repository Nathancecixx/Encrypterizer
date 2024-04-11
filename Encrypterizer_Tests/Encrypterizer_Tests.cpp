#include "pch.h"
#include "CppUnitTest.h"

#include "C:\Users\natha\OneDrive\Documents\GitHub\Section3-Group7\Encrypterizer\Data.h"
#include "C:\Users\natha\OneDrive\Documents\GitHub\Section3-Group7\Encrypterizer\Encrypter.h"

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

		TEST_METHOD(REQ_ENC_001)
		{

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
