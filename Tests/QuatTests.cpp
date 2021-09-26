#pragma once
#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{
	TEST_CLASS(QuatTestDX)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			DXQuat quat(0.8924f, 0.23912f, 0.36964f, -0.099046f);
			Assert::AreEqual(quat[0], 0.8924f);

		}
		TEST_METHOD(testConvertToMatrix) {
			DXQuat quat(0.8924f, 0.23912f, 0.36964f, -0.099046f);
			DXMatrix4 mat;
			quat.toRotation(mat);
			Assert::AreEqual(std::round(mat(0, 0)), std::round(0.7071f));
			DXQuat quat2(0.7071, 0.7071, 0.f, 0.f);
			quat2.toRotation(mat);

		}
	};
}
