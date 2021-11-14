#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(MatrixTestsOMatrix4)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			OMatrix4<float> A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);

			Assert::AreEqual(A(0, 0), 1.f);
		}

		TEST_METHOD(Multiplication) {
			OMatrix4<float> B(2.f, -1, -1, 0, 
				-1, 3, -1, -1, 
				-1, -1, 3, -1,
				0, -1, -1, 2);

			OMatrix4<float> A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);

			OMatrix4<float> R = A * B;
			Assert::AreEqual(R(0, 0), 3.f);

		}

		



	};
}