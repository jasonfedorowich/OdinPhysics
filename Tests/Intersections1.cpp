#pragma once
#include "pch.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(TestAABBIntersections)
	{
	public:
		TEST_METHOD(testAABBD) {
			AABB<3> aabb1({ {50.f, 1.f, -500.f}, {1.f, 3.f, 2.f} });
			ODVector v{ 25.f, 2.f, 1.f };
			Assert::IsTrue(intersection(aabb1, v));

			


		}
	};
}
