#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Plane2Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			Plane2 plane({ 2, 3 }, { 0, 0 });
			Assert::AreEqual(plane.normal[0], 2.f);


		}
		TEST_METHOD(testInter) {
			Plane2 plane1({ 2, 2 }, { 2, 3});
			Plane2 plane2({ 2, 2 }, { 2, 3 });
			Assert::IsFalse(plane1.intersects(plane2));

		}
	};
}
