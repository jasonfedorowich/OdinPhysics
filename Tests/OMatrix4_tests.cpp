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
			Logger::WriteMessage("here");
			OMatrix4<float> A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);

			OMatrix4<float> R = A * B;
			Logger::WriteMessage("here");
			Assert::AreEqual(R(0, 0), 3.f);

		}

		TEST_METHOD(testScale) {
			OMatrix4<float> B(2.f, -1, -1, 0,
				-1, 3, -1, -1,
				-1, -1, 3, -1,
				0, -1, -1, 2);
			B *= 3.0f;

			Assert::AreEqual(B(0, 0), 6.0f);

			OMatrix4<double> C(2.0, -1, -1, 0,
				-1, 3, -1, -1,
				-1, -1, 3, -1,
				0, -1, -1, 2);
			C *= 3.0;

			Assert::AreEqual(C(0, 0), 6.0);


		}

		TEST_METHOD(transformation) {
			OVector4<float> v = { 1.0f, 2.0f, 3.0f, 4.0f };
			OMatrix4<float> B(2.f, -1, -1, 0,
				-1, 3, -1, -1,
				-1, -1, 3, -1,
				0, -1, -1, 2);
			v = B* v;

			Assert::AreEqual(v[0], -3.f);

		}

		TEST_METHOD(addMatrix) {
			OMatrix4<float> A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);

			OMatrix4<float> B(2.f, -1, -1, 0,
				-1, 3, -1, -1,
				-1, -1, 3, -1,
				0, -1, -1, 2);
			A = A + B;

			Assert::AreEqual(A(0, 0), 3.f);

		}

		TEST_METHOD(invertMatrixFloat) {
			OMatrix4<float> A(

				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);
			A.invert();

			Assert::AreEqual(std::round(A(0, 0)), std::round(0.721831f));


		}
		TEST_METHOD(testSetCol) {
			OMatrix4<float> A(

				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);
			A.setCol(0, { 0.f, 0.f, 0.f, 0.f });

			Assert::AreEqual(A(0, 0), 0.f);


		}

		TEST_METHOD(testSetRow) {
			OMatrix4<float> A(

				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);
			A.setRow(0, { 0.f, 0.f, 0.f, 0.f });

			Assert::AreEqual(A(0, 0), 0.f);


		}
		
		TEST_METHOD(testDetermin) {
			OMatrix4<float> A(

				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);
			float d = A.determinant();

			Assert::AreEqual(d, 284.0f);


		}
		TEST_METHOD(testIdent) {
			OMatrix4<float> I = OMatrix4<float>::identity();

			Assert::AreEqual(I(0,0), 1.f);


		}

		TEST_METHOD(testLeftVectorMatMult) {
			OMatrix4<float> A(
				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			OVector4<float> v(1.f, 2.f, 3.f, 4.f);
			v *= A;
			Assert::AreEqual(v[0], 30.f);


		}
		TEST_METHOD(testMatVectMult) {
			OMatrix4<float> A(
				11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			OVector4<float> v(1.f, 2.f, 3.f, 4.f);
			A *= v;
			Assert::AreEqual(v[0], 109.f);


		}

		TEST_METHOD(testOuterProduct4) {
			OVector4<float> p(1.f, 2.f, 3.f, 4.f);
			OVector4<float> q(5.f, 4.f, 3.f, 1.f);
			OMatrix4<float> M;

			outerProduct(M, p, q);
			Assert::AreEqual(M(0, 0), 5.f);
			Assert::AreEqual(M(1, 1), 8.f);


		}



	};
}