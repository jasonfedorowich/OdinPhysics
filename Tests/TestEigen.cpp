#include "pch.h"
#include "CppUnitTest.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(EigenTests)
	{
	public:

		

		TEST_METHOD(testEigen4WithQRHess) {
			Matrix4 A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);



			QREigen4 qre(A, EigenMode::QR_HESS);
			Vector4 E = qre.getEigenValues();
			Assert::AreEqual(std::round(E[1]), 1.f);

			Matrix4 B(2.f, -1, -1, 0, -1, 3, -1, -1, -1, -1, 3, -1, 0, -1, -1, 2);

			QREigen4 qre3(B, EigenMode::QR_HESS_SHIFT);
			Vector4 E3 = qre3.getEigenValues();

			Matrix4 C(2.f, 4, -2, -2,
				4, 2, 4, -3,
				-2, 4, 8, 6,
				-2, -3, 6, -3);
			QREigen4 qre4(C, EigenMode::QR_HESS);
			Vector4 E4 = qre4.getEigenValues();

			



		}

		TEST_METHOD(testEigen4WithQR) {
			Matrix4 A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);



			QREigen4 qre(A, EigenMode::QR);
			Vector4 E = qre.getEigenValues();
			Assert::AreEqual(std::round(E[1]), 1.f);

		}


		TEST_METHOD(testEigen4WithGivens) {

			Matrix4 A(1.f, -1, 0, 0,
				     -1, 1, -1, 0,
				      0, -1, 2, 0,
				      0, 0, 0, 3);



			QREigen4 qre(A, EigenMode::HESS_GIVENS);
			Vector4 E = qre.getEigenValues();
			Assert::AreEqual(std::round(E[1]), 1.f);

			Matrix4 C(2.f, 4, -2, -2,
				4, 2, 4, -3,
				-2, 4, 8, 6,
				-2, -3, 6, -3);
			
			QREigen4 qre3(C, EigenMode::HESS_GIVENS, true, true, 100000);
			Vector4 E4 = qre3.getEigenValues();

			//QREigen4 qre4(C);

			//Vector4 E5 = qre4.getEigenValues();

			Matrix4 B(2.f, -1, -1, 0, -1, 3, -1, -1, -1, -1, 3, -1, 0, -1, -1, 2);
			QREigen4 qre5(B, EigenMode::HESS_GIVENS);
			Vector4 E7 = qre5.getEigenValues();

		}
	

		



	};
}
