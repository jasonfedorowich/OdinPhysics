#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

struct DD : public ODE<float>::Derivative{




	// Inherited via Derivative
	virtual void differentiateEq(float t, float y, float& dydt) override
	{
		dydt = t * sqrt(y);
	}

	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{
	}

};

struct ERF : public SingleIntegral<float>::Function {




	// Inherited via Function
	virtual void evaluate(float t, float& xOut) override
	{
		xOut = t * exp(-1 * t);
	}

};

namespace Tests
{
	TEST_CLASS(MathTests)
	{
	public:

		TEST_METHOD(testSolveEquationRK4)
			{
				RK4<float> rk4;
				DD dd;
				std::vector<float> tOut;
				std::vector<float> yOut;
				rk4.solveEquation(0.f, 10.f, 1.0f, 0.1f, dd, yOut, tOut);

				Assert::AreEqual(round(yOut[20]), 4.f);
				Assert::AreEqual(round(tOut[20]), 2.f);


			}

		TEST_METHOD(testIntegrationTrap) {
			TrapezoidIntegral<float> ti;
			ERF ff;
			float result;
			ti.evaluate(0, 5, 65, ff, result);
			Assert::AreEqual(round(0.9593f), round(result));
		}
		TEST_METHOD(testIntegrationGLQ) {
			GLQ<float> ti;
			ERF ff;
			float result;
			ti.evaluate(0, 5, 5, ff, result);
			Assert::AreEqual(round(0.9593f), round(result));
		}


		
	};

	TEST_CLASS(Vector4Tests) {


public:
	TEST_METHOD(testConstructor) {

		DXVector4 dx1;
		Assert::AreEqual(dx1[0], 0.0f);
		DXVector4 dx2(1.0f, 1.0f, 2.0f);
		Assert::AreEqual(dx2[0], 1.0f);
	}

	TEST_METHOD(testOperators) {

		DXVector4 dx1(1.0f, 1.0f, 2.0f);
		DXVector4 dx2(2.0f, 2.0f, 4.0f);

		DXVector4 dx3 = dx1 + dx2;
		Assert::AreEqual(dx3[0], 3.0f);
		DXVector4 dx4(2.0f, 2.0f, 4.0f);

		Assert::AreEqual(dx4 == dx2, true);

		dx2[0] = 1000.f;
		Assert::AreEqual(dx2[0], 1000.f);
	}
	TEST_METHOD(testDot) {
		DXVector4 v1(1.0f, 1.0f, 1.0f);
		DXVector4 v2(2.0f, 2.0f, 1.0f);
		Assert::AreEqual(v1.dot(v2), 5.0f);

	}
	TEST_METHOD(testCross) {

		DXVector4 v1(2.0f, 1.0, 3.0);
		DXVector4 v2(2.0f, 0.0, 0.0);

		Vector4 v3 = v1.cross(v2);

		Assert::AreEqual(v3.getX(), 0.0f);
		Assert::AreEqual(v3.getY(), 6.0f);
	}
	TEST_METHOD(testNormal) {
		Vector4 v1(-1, 3, 4);
		Vector4 norm = v1.normal();

		double exp = -1.0 / sqrt(26.0);

		Assert::AreEqual((int)norm.getX(), (int)exp);
	}

	TEST_METHOD(testLength) {



		Vector4 v1(1.0f, 2.0, 1.0);
		float l = v1.length();
		float exp = sqrt(6);
		Assert::AreEqual((int)l, (int)exp);
	}


	};
}
