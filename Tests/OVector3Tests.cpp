#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(OVector3Tests)
	{
	public:

		TEST_METHOD(TestConstructorV3)
		{
			OVector3<float> v{ 1.0f, 2.0f, 3.f };
			Assert::AreEqual(v[0], 1.0f);
			OVector3<float> vvv;
			Assert::AreEqual(vvv[0], 0.0f);
		}

		TEST_METHOD(TestAdding) {
			OVector3<float> v1{ 1.0f, 2.0f, 3.f };
			OVector3<float> v2{ 3.0f, 4.0f, 6.f };
			OVector3<float> v3 = v1 + v2;

			OVector3<float> v4 = v1 - v2;


			Assert::AreEqual(v3[0], 4.0f);


		}

		TEST_METHOD(testDot) {
			OVector3<float> v1{ 1.0f, 2.0f, 3.f };
			OVector3<float> v2{ 3.0f, 4.0f, 6.f  };

			float res = v1.dot(v2);

			Assert::AreEqual(res, 29.f);


		}


		TEST_METHOD(testCross3) {

			OVector3<float> v1{ 0.0f, 1.0f, 2.f };
			OVector3<float> v2{ 2.0f, 9.0f, 6.f };

			OVector3<float> v3 = v1.cross(v2);
			Assert::AreEqual(v3[0], -12.f);
		}





	};
}