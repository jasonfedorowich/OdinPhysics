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
			std::vector<ODVector> v{ {1.f, 2.f, 3.3f}, { 0.f, -1.f, 10.f }, { 100.f, 0.f, -1000.f } };
			//BoundingSphere bs({ {1.f, 2.f, 3.3f}, {0.f, -1.f, 10.f}, {100.f, 0.f, -1000.f} });
			BoundingSphere bs1(v);
			ODVector vec = { 1.f, 2.f, 3.3f };
			BoundingSphere bs2(vec, 100.f);
			BoundingSphere bs;
			
		}
		//todo add more tests
	};
}
