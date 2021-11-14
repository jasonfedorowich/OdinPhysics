#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(OVector4Tests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			OVector4<float> v{ 1.0f, 2.0f, 3.f, 5.f };
			Assert::AreEqual(v[0], 1.0f);
		}

		TEST_METHOD(Adding) {
			OVector4<float> v1{ 1.0f, 2.0f, 3.f, 5.f };
			OVector4<float> v2{ 3.0f, 4.0f, 6.f, 10.f };
			OVector4<float> v3 = v1 + v2;

			OVector4<float> v4 = v1 - v2;


			Assert::AreEqual(v3[0], 4.0f);


		}

		TEST_METHOD(testDot) {
			OVector4<float> v1{ 1.0f, 2.0f, 3.f, 5.f };
			OVector4<float> v2{ 3.0f, 4.0f, 6.f, 10.f };

			float res = v1.dot(v2);
			float res2 = v1.dot3(v2);

			Assert::AreEqual(res, 79.f);
			Assert::AreEqual(res2, 29.f);


		}





	};
}