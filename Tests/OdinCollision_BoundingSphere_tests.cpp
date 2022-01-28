#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(SphereTests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			
			BoundingSphere bs({ {1.f, 2.f, 3.3f}, {0.f, -1.f, 10.f}, {100.f, 0.f, -1000.f} });
			Assert::AreEqual(round(bs.center[0]), 50.f);
			ODVector3 vec = { 1.f, 2.f, 3.3f };
			BoundingSphere bs2(vec, 100.f);

			Assert::AreEqual(bs2.center[0], 1.f);
			
		}
		TEST_METHOD(TestIntersection)
		{

			BoundingSphere bs({100.f, 100.f, 2.f}, 10.f);
			ODVector3 vec = { 1.f, 101.f, 3.3f };
			BoundingSphere bs2(vec, 100.f);

			Assert::IsTrue(bs.intersects(bs2));

		}

		//todo add more tests
	};
}
