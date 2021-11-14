#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(MatrixTests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			Matrix < 4, float> m4;
			m4(1, 1) = 1.f;

			Assert::AreEqual(m4(1, 1), 1.f);

			Matrix<4, float> m4c = m4;
			Assert::AreEqual(m4c(1, 1), 1.f);
			Matrix<2, int> m5({ {1, 2},
				{2, 2} });

		}

		TEST_METHOD(Multiplication) {
			Matrix<4, float> m4({{ 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 }
		});
			Matrix<4, float> m5({ { 2, 0, 0, 0 }, { 0, 2, 0, 0 }, { 0, 0, 2, 0 }, { 0, 0, 0, 2 }
				});
		
			Matrix<4, float> m3;
			m4.test();
			m4.test123(m4);

		//	m4.strassenMult(m5);
			Matrix<4, float> mm = strassenMulti(m4, m5);
			/*strassenMult<float, 4>(m4, m5);*/

			Matrix<4, float> A({ {11.f, 9, 24, 2},
				{1, 5, 2, 6},
				{3, 17, 18, 1},
				{2, 5, 7, 1} });


			Matrix<4, float>  B({ {2.f, 4, -2, -2},
				{1, 2, 4, -3},
				{-3, -3, 8, -2},
				{-1, 1, 6, -3} });

			Matrix<4, float> C = strassenMulti(A, B);

			Assert::AreEqual(C(0, 0), -43.0f);


		}

		TEST_METHOD(inverseTest) {

			Matrix<3, float> m4({ 
						{ 5, 7, 9 },
						 { 4, 3, 8 },
						 { 7, 5, 6 }
				});

	
			Matrix<3, float> inverse;
			gaussJordan(m4, inverse);
			
			Assert::AreEqual(inverse(0, 0), -0.209523812f);
		}

		TEST_METHOD(determinantTest) {
			Matrix<4, float> m4({
						{ 1, 1, 1, -1 },
						 { 1, 1, -1, 1 },
						 { 1, -1, 1, 1 },
							{-1, 1, 1, 1}
				});

			float det = determinant<float>(m4);
			Assert::AreEqual(det, -16.f);

		}

		TEST_METHOD(test3x3Inverse) {

			Matrix<3, float> m4({
						{ 1, 2, 3 },
						 { 0, 1, 4 },
						 { 5, 6, 0 }		
				});
			Matrix<3, float> inv;
			float det;
			adjugateInverse(m4, inv, det);
			Assert::AreEqual(inv(0, 0), -24.f);


		}

		TEST_METHOD(test4x4Inverse) {

			Matrix<4, float> m4({
						{ 1, 1, 1, -1 },
						 { 1, 1, -1, 1 },
						 { 1, -1, 1, 1 },
							{-1, 1, 1, 1}
				});
			Matrix<4, float> inv;
			float det;
			adjugateInverse(m4, inv, det);

			Assert::AreEqual(inv(0, 0), 0.25f);
			

		}
		TEST_METHOD(testTranspose) {
			Matrix<4, int> m4({
						{ 7, 12, 1, 14 },
						 { 2, 13, 8, 11 },
						 { 16, 3, 10, 5 },
							{9, 6, 14, 4}
				});

			m4.transpose();

			Assert::AreEqual(m4(1, 0), 12);

		}

		TEST_METHOD(testGetTranspose) {
			Matrix<4, int> m4({
						{ 7, 12, 1, 14 },
						 { 2, 13, 8, 11 },
						 { 16, 3, 10, 5 },
							{9, 6, 14, 4}
				});

			Matrix<4, int> transpo = m4.getTranspose();

			Assert::AreEqual(transpo(1, 0), 12);

		}

		TEST_METHOD(testLooping) {

			Matrix<4, int> m4({
						{ 7, 12, 1, 14 },
						 { 2, 13, 8, 11 },
						 { 16, 3, 10, 5 },
							{9, 6, 14, 4}
				});

			auto it = m4.begin();
			it = Vector<4, int>({ 1, 2, 3, 4 });

			for (Vector<4, int>& v : m4) {
				Vector<4, int> vv = v;

			}
		}

		


	};
}