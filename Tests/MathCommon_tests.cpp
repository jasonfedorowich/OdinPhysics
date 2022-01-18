#include "pch.h"
#include "CppUnitTest.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(MathCommon)
	{
	public:

		TEST_METHOD(testMax) {
			float x = 100.f;
			float y = 0.1f;

			Assert::AreEqual(Math<float>::odMax(x, y), 100.f);

		}

		TEST_METHOD(testRandom) {

			int x = 200;
			while (x) {
				float rand = Math<float>::odRandom(50.0, 1000.f);
				stringstream _ss;
				_ss << rand;
				_ss << "\n";
				Logger::WriteMessage(_ss.str().c_str());
				Assert::IsTrue(rand <= 1000.f);
				Assert::IsTrue(rand >= 50.0);
				x--;


			}


		}

		
		

		TEST_METHOD(testQRDecomp) {

			Matrix4 A(2.f, 4, -2, -2,
				1, 2, 4, -3,
				-3, -3, 8, -2,
				-1, 1, 6, -3);

			QRDecomp4 qr(A);
			Matrix4 inv;
			qr.inverse(inv);

			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.333));

			Matrix4 B(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			QRDecomp4 qr2(B);
			qr2.inverse(inv);
			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.722));

			


		}

		TEST_METHOD(testQRDecomp3) {

			Matrix3 A(2.f, 4, -2,
				4, 2, 4,
				-2, 4, 8);

			QRDecomp3 qr(A);
			Matrix3 inv;
			qr.inverse(inv);

			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.0f));





		}
		TEST_METHOD(testQRDecompGS) {
			Matrix4 A(2.f, 4, -2, -2,
				1, 2, 4, -3,
				-3, -3, 8, -2,
				-1, 1, 6, -3);
			QRDecomp4 qr(A, QRMode::GS);
			Matrix4 P = qr.Q * qr.R;

			Matrix4 inv;
			qr.inverse(inv);
			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.333));
			Matrix3 B(60.f, 91, 26, 60, 3, 75, 45, 90, 31);
			Matrix3 Q;
			Matrix3 R;
			gs<Matrix3, Vector3, float>(B, Q, R, 3);
			Assert::AreEqual(std::roundf(inv(0, 0)), std::roundf(0.333));

			Vector3 v{ 26.f, 75.f ,31.f };
			Vector3 q{ 0.62469f, 0.62469, 0.46852 };
			float d = v.dot(q);


		}

	



	};
}
