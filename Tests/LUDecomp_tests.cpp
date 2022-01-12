
#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(LUDecompTests)
	{
	public:

		TEST_METHOD(testLU4) {
			Matrix4 A(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			LU4 lu(A);

			Assert::AreEqual(std::round(10 * lu.L(1, 0) + 0.5) / 10, std::round(10 * 0.272727f + 0.5) / 10);



		}

		TEST_METHOD(testLUInv4) {
			Matrix4 A(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			LU4 lu(A);
			Matrix4 I;
			Matrix4 inv;

			lu.solve(inv, I);


			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.72));



		}
		TEST_METHOD(solveLUSystem4) {
			Matrix4 A(2.f, 4, -2, -2,
				1, 2, 4, -3,
				-3, -3, 8, -2,
				-1, 1, 6, -3);


			LU4 lu(A);
			Vector4 b = { -4, 5, 7, 7 };
			Vector4 x;

			lu.solve(x, b);
			Assert::AreEqual(std::roundf(x[0]), 1.f);




		}
		TEST_METHOD(testLU3) {
			Matrix3 A(11.f, 9, 24,
				1, 5, 2,
				3, 17, 18);

			LU3 lu(A);
			Assert::AreEqual(lu.U(0, 0), 11.f);

		}

		TEST_METHOD(testLU3Inv) {
			Matrix3 A(11.f, 9, 24,
				1, 5, 2,
				3, 17, 18);

			LU3 lu(A);
			Matrix3 m;
			lu.inverse(m);
			Assert::AreEqual(round(m(0, 0)), round(0.1007f));

		}
	};
}
