#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(AABB3Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector3 c{ 0.f, 0.f, 0.f };
			ODVector3 e{ 10.f, 10.f, 10.f };
			AABB3 aabb(e, c);
			Assert::AreEqual(aabb.maximum()[0], 10.f);


		}
		TEST_METHOD(testOverlap) {
			AABB3 aabb1( {50.f, 50.f, 50.f}, {0.f, 0.1f, 0.f});

			AABB3 aabb2( {1.f, 2.f, 3.3f}, {25.f, 0.f, 25.f} );
			Assert::IsTrue(aabb1.intersects(aabb2));

		}
	};
}
