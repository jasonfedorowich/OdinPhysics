#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(BoundingCircleTests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector2 c{ 0.f, 0.f };
			ODVector2 e{ 10.f, 10.f };
			BoundingCircle bc(10.f, c);
			Assert::AreEqual(bc.center[0], 0.f);


		}
		TEST_METHOD(testOverlap) {
			ODVector2 c{ 0.f, 0.f };
			ODVector2 e{ 10.f, 10.f };
			BoundingCircle bc1(10.f, c);
			BoundingCircle bc2(20.f, {10.f, 10.f});

			Assert::IsTrue(bc1.intersects(bc2));

		}
	};
}
