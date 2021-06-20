#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace Tests
{
	TEST_CLASS(MatrixTests)
	{
	public:

		TEST_METHOD(Test1)
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

			m4.strassenMult(m5);

			/*strassenMult<float, 4>(m4, m5);*/

		}


	};
}