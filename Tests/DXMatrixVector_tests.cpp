#include "pch.h"
#include "CppUnitTest.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(DXMatrix4Tests)
	{
	public:

		
		TEST_METHOD(testTranspose) {
			Matrix4 A(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			Matrix4 t = A.getTranspose();
			Assert::AreEqual(t(1, 0), 9.f);
			



		}


	};
}
