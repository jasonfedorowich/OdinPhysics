#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(Seg2Test)
	{
	public:

		TEST_METHOD(testConstructor)
		{
			ODVector2 s{ 0.f, 0.f };
			ODVector2 e{ 10.f, 10.f };
			Seg2 seg(s, e);
			Assert::AreEqual(seg.direction()[0], 10.f);


		}
		TEST_METHOD(testInter) {
			Seg2 a({ 0, 0 }, { 1,  1 });
			Seg2 b({ 0, 1 }, { 1, -1 });
			Assert::IsTrue(a.intersects(b));

		}
	};
}
