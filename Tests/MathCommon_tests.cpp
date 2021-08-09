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

		TEST_METHOD(testEigen4) {
			Matrix4 A(1.f, -1, 0, 0,
				-1, 1, -1, 0,
				0, -1, 2, 0,
				0, 0, 0, 3);



			QREigen4 qre(A);
			Vector4 E = qre.getEigenValues();
			Assert::AreEqual(std::round(E[1]), 1.f);

			Matrix4 B(2.f, -1, -1, 0, -1, 3, -1, -1, -1, -1, 3, -1, 0, -1, -1, 2);

			QREigen4 qre2(B);
			qre.getEigenValues();

		}


	};
}
