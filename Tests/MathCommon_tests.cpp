#include "pch.h"
#include "CppUnitTest.h"

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
	};
}
