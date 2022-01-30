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
		TEST_METHOD(testNormal4) {
			OVector4<float> uu = { 1.f, 2.0, 3.0, 4.0 };
			uu.normalize();
			Assert::AreEqual(std::round(uu[0]), std::round(0.18257f));

		}
		TEST_METHOD(testNormal3) {
			OVector4<float> uu = { 1.f, 2.0, 3.0, 4.0 };
			uu.normalize3();
			uu.normal();
			Assert::AreEqual(std::round(uu[0]), std::round(0.26726f));
		

		}

		TEST_METHOD(testScalarMult) {
			OVector4<float> uuuu = { 1.f, 2.0, 3.0, 4.0 };
			uuuu = uuuu * 10.f;
			Assert::AreEqual(uuuu[0], 10.f);


		}




	};
}