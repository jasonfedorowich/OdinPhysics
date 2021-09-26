#pragma once
#include "pch.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(TestDistances)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			


		}
		TEST_METHOD(testAABBD) {
			AABB<3> aabb1({ {50.f, 1.f, -500.f}, {1.f, 3.f, 2.f} });
			ODVector v{ 25, 2, 3 };
			ODVector cp;
			float di = OdinCollision::distanceSqr(aabb1, v, cp);

			Assert::AreEqual(cp[0], 25.f);


		}
	};
}
