#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinCollision;

namespace CollisionTests
{
	TEST_CLASS(OBB3Tests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			OBB3 obb3({ 2, 2, 2 }, { 2, 3, 4 }, { 4, 3, 5 });
			Assert::AreEqual(obb3.center[0], 2.f);


		}
		TEST_METHOD(testPointsContruct) {
			std::vector<ODVector3> points = { { 5, 5, 5 }, { 5, 5, -5 }, { 5, -5, -5 }, { -5, -5, -5 }, { 5, -5, 5 }, { -5, 5, -5 }, { -5, -5, 5 }, { -5, 5, 5 } };
			OBB3 obb3(points);
			Assert::AreEqual(obb3.center[0], 0.f);

		}
		TEST_METHOD(testInter) {
			std::vector<ODVector3> points = { { 5, 5, 5 }, { 5, 5, -5 }, { 5, -5, -5 }, { -5, -5, -5 }, { 5, -5, 5 }, { -5, 5, -5 }, { -5, -5, 5 }, { -5, 5, 5 } };
			OBB3 obb1(points);
			
			OBB3 obb2({ 10, 10, 10 }, { 0, 0, 0 }, {0, 0, 0, 1});
			Assert::IsTrue(obb1.intersects(obb2));

		}
	};
}
