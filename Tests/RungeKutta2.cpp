#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;
using namespace std;

struct Grav : public ODE<float>::Derivative {




	// Inherited via Derivative
	virtual void differentiateEq(float t, float y, float& dydt) override
	{
		return;
	}

	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{
		float rSq = y[0] * y[0] + y[1] * y[1];
		
		float c = -pow(rSq, -1.5);

		dydt[0] = y[2];
		dydt[1] = y[3];
		dydt[2] = c * y[0];
		dydt[3] = c * y[1];

	}

};


namespace Tests
{
	TEST_CLASS(MathTests2)
	{
	public:

		TEST_METHOD(testRK42) {

			float time = 0.0f;
			int n = 32;

			float x0 = 1.0f;
			float y0 = 0.1f;

			float dx0 = 0.0f;
			float dy0 = 0.0f;

			std::vector<float> st{ x0, y0, dx0, dy0 };
			RK4<float> rk4;
			Grav gr;

			for (int i = 0; i < n; i++) {
				stringstream _ss;
				_ss << "x: " << st[0] << "\n";
				_ss << "y: " << st[1] << "\n";
				_ss << "vx: " << st[2] << "\n";
				_ss << "vy: " << st[2] << "\n";
				Logger::WriteMessage(_ss.str().c_str());
				

				rk4.solveEquations(time, 0.001, st, gr, st, time);
			}


		}

	};
}