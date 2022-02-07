#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Ray3Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector3 s{ 0.f, 0.f, 0.f };
			ODVector3 e{ 10.f, 10.f, 10.f };
			Ray3 ray(s, e);
			Assert::AreEqual(ray.d[0], 10.f);


		}
		TEST_METHOD(testInter) {
			Ray3 a({ 0, 0, 0 }, { 1,  1, 0 });
			Ray3 b({ 0, 1, 0 }, { 1, -1, 0 });
			Assert::IsTrue(a.intersects(b));

		}
	};
}
