#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;


namespace Tests
{
	TEST_CLASS(OMatrix3Tests)
	{
	public:

		TEST_METHOD(testMult) {

			OMatrix3<float> M(11.f, 9, 24, 1, 5, 2, 3, 17, 18);
			OMatrix3<float> B(1.f, 2, 3, 4, 5, 6, 7, 8, 9);
			OMatrix3<float> Q = M * B;
			Assert::AreEqual(Q(0, 0), 215.f);
			Assert::AreEqual(Q(1, 0), 35.f);
			


		}

		TEST_METHOD(testAdding) {
			OMatrix3<float> M(11.f, 9, 24, 1, 5, 2, 3, 17, 18);
			OMatrix3<float> B(1.f, 2, 3, 4, 5, 6, 7, 8, 9);
			OMatrix3<float> Q = M + B;
			Assert::AreEqual(Q(0, 0), 12.f);
			Assert::AreEqual(Q(0, 1), 11.f);


		}

		TEST_METHOD(testInvert) {
			OMatrix3<float> M(11.f, 9, 24, 1, 5, 2, 3, 17, 18);
			M.invert();
			Assert::AreEqual(round(M(0, 0)), round(0.100719f));

			OMatrix3<double> Q(11.0, 9.0, 24.0, 1.0, 5.0, 2.0, 3.0, 17, 18);

			Q.invert();
			Assert::AreEqual(round(Q(0, 0)), round(0.100719));

		}

	};
}
