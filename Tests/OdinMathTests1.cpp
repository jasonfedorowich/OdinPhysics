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
}
