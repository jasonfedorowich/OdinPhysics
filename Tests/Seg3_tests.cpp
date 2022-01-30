#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Seg3Test)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			ODVector3 s{ 0.f, 0.f, 0.f };
			ODVector3 e{ 10.f, 10.f, 10.f };
			Seg3 seg(s, e);
			Assert::AreEqual(seg.direction()[0], 10.f);


		}
		TEST_METHOD(testInter) {
			Seg3 a({ 0, 0, 0 }, { 2,  2, 0 });
			Seg3 b({ 0, 1, 0 }, { 4, -4, 0 });
			Assert::IsTrue(a.intersects(b));

		}
	};
}
