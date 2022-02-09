#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Ray2Tests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector2 s{ 0.f, 0.f };
			ODVector2 e{ 10.f, 10.f };
			Ray2 ray(s, e);
			Assert::AreEqual(ray.d[0], 10.f);


		}
		TEST_METHOD(testInter) {
			Ray2 a({ 0, 0 }, { 1,  1 });
			Ray2 b({ 0, 1 }, { 1, -1 });
			Assert::IsTrue(a.intersects(b));

		}
	};
}
