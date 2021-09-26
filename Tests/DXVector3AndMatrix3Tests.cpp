#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(DXVector3Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			DXVector3 v(1.f, 2.f, 3.f);
			Assert::AreEqual(v[0], 1.f);

		}
		TEST_METHOD(test1) {
			
			DXVector3 v(1.f, 2.f, 3.f);
			DXVector3 v2(1.f, 2.f, 3.f);
			Assert::AreEqual(v.dot(v2), 14.f);

		}
	};


	TEST_CLASS(DXMatrix3Test) {
public:
	TEST_METHOD(testConstructor) {

		DXMatrix3 mat(1.f, 2.f, 3.f, 4.f, 4.f, 5.f, 6.f, 8.f, 9.f);
		Assert::AreEqual(mat(0, 0), 1.f);
	}

	TEST_METHOD(test1) {
		DXMatrix3 mat(1.f, 2.f, 3.f, 4.f, 4.f, 5.f, 6.f, 8.f, 9.f);
		DXMatrix3 mat2;
		mat *= mat2;
		Assert::AreEqual(mat(0, 1), 2.f);

	}



	};
}
