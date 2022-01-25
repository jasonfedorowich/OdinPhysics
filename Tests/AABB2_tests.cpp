#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(AABB2Tests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector2 c{ 0.f, 0.f };
			ODVector2 e{ 10.f, 10.f};
			AABB2 aabb(e, c);
			Assert::AreEqual(aabb.maximum()[0], 10.f);


		}
		TEST_METHOD(testOverlap) {
			AABB2 aabb1({ 50.f, 50.f }, { 0.f, 0.1f });

			AABB2 aabb2({ 1.f, 2.f }, { 25.f, 0.f});
			Assert::IsTrue(aabb1.intersects(aabb2));

		}
	};
}
