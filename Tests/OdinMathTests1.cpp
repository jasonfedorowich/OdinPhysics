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

namespace Tests
{
	TEST_CLASS(RK4Tests)
	{
	public:

		TEST_METHOD(testSolveEquation)
			{
				RK4<float> rk4;
				DD dd;
				std::vector<float> tOut;
				std::vector<float> yOut;
				rk4.solveEquation(0.f, 10.f, 1.0f, 0.1f, dd, yOut, tOut);

				Assert::AreEqual(round(yOut[20]), 4.f);
				Assert::AreEqual(round(tOut[20]), 2.f);


			}

		TEST_METHOD(testIntegration) {


		}
	};
}
