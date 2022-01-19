#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(OVector2Tests)
	{
	public:

		TEST_METHOD(TestConstructorV2)
		{
			OVector2<float> v{ 1.0f, 2.0f };
			Assert::AreEqual(v[0], 1.0f);
			OVector2<float> vvv;
			Assert::AreEqual(vvv[0], 0.0f);
		}

		TEST_METHOD(TestAdding) {
			OVector2<float> v1{ 1.0f, 2.0f};
			OVector2<float> v2{ 3.0f, 4.0f};
			OVector2<float> v3 = v1 + v2;

			OVector2<float> v4 = v1 - v2;


			Assert::AreEqual(v3[0], 4.0f);


		}

		TEST_METHOD(testDot) {
			OVector2<float> v1{ 1.0f, 2.0f };
			OVector2<float> v2{ 3.0f, 4.0f };

			float res = v1.dot(v2);

			Assert::AreEqual(res, 11.f);


		}


		TEST_METHOD(testCross3) {

			OVector2<float> v1{ 0.0f, 1.0f };
			OVector2<float> v2{ 2.0f, 9.0f};

			OVector3<float> v3 = v1.cross(v2);
			Assert::AreEqual(v3[0], 0.f);
		}





	};
}