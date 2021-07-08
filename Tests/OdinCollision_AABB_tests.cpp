#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(AABBTest)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			AABB<3> aabb;
			Assert::AreEqual(aabb.maxi[0], 0.f);

			AABB<3> aabb2({ {1.f, 2.f, 3.3f}, {0.f, -1.f, 10.f}, {100.f, 0.f, -1000.f} });
			Assert::AreEqual(aabb2.maxi[0], 100.f);


		}
		TEST_METHOD(testOverlap) {
			AABB<3> aabb1({ {50.f, 1.f, -500.f}, {1.f, 3.f, 2.f} });

			AABB<3> aabb2({ {1.f, 2.f, 3.3f}, {0.f, -1.f, 10.f}, {100.f, 0.f, -1000.f} });
			Assert::IsTrue(aabb1.overlaps(aabb2));


		}
	};
}
