#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Plane3Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			Plane3 plane({ 2, 3, 3 }, { 0, 0, 0 });
			Assert::AreEqual(plane.normal[0], 2.f);


		}
		TEST_METHOD(testInter) {
			Plane3 plane1({2, 2, 1 }, { 2, 3, 3 });
			Plane3 plane2({ 2, 2, 1 }, { 2, 3, 4 });
			Assert::IsFalse(plane1.intersects(plane2));

		}
	};
}
