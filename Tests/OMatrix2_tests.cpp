#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;


namespace Tests
{
	TEST_CLASS(OMatrix2Tests)
	{
	public:

		TEST_METHOD(testMult) {

			OMatrix2<float> M(11.f, 9, 24, 1);
			OMatrix2<float> B(1.f, 3, 2, 4);
			OMatrix2<float> Q = M * B;
			Assert::AreEqual(Q(0, 0), 29.f);
			Assert::AreEqual(Q(1, 0), 26.f);



		}

		TEST_METHOD(testAdding) {
			OMatrix2<float> M(11.f, 9, 24, 1);
			OMatrix2<float> B(1.f, 2, 3, 4);
			OMatrix2<float> Q = M + B;
			Assert::AreEqual(Q(0, 0), 12.f);
			Assert::AreEqual(Q(0, 1), 11.f);


		}

		TEST_METHOD(testInvert) {
			OMatrix2<float> M(11.f, 9, 24, 1);
			M.invert();
			Assert::AreEqual(round(M(0, 0)), round(-0.0048780f));

		

		}

	};
}
