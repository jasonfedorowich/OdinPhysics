#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;
using namespace std;

struct Angles : public ODE<float>::Derivative {

	float alpha, gamma, beta, epi;
	Angles(float alpha, float beta, float gamma, float epi) { this->alpha = alpha; this->beta = beta; this->gamma = gamma; this->epi = epi; }

	// Inherited via Derivative
	virtual void differentiateEq(float t, float y, float& dydt) override
	{
		return;
	}

	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{
		dydt[0] = -sqrt((1 - y[0] * y[0]) * (beta - 2 * alpha * y[0]) - powf((gamma - epi * y[0]), 2));
		dydt[1] = gamma - epi * y[0] / (1 - y[0] * y[0]);
		dydt[2] = y[0] * (gamma - epi * y[0]) / (1.f - y[0] * y[0]);

	}


};

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


struct QFunc : public ODE<float>::Derivative {




	// Inherited via Derivative
	virtual void differentiateEq(float t, float y, float& dydt) override
	{
		return;
	}

	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{

		dydt[0] = y[1];
		float qSq = y[0] * y[0];
		float qPSq = y[1] * y[1];
		float numer = -3.f * 1.f * qSq - 2.f * y[0] * (2.f + 9.f * qSq) * qPSq;
		float denom = 1.f + qSq * (4.f + 9.0f * qSq);
		

		dydt[1] = numer / denom;
		
	}

};


struct BallHill : public ODE<float>::Derivative {
	// Inherited via Derivative
	virtual void differentiateEq(float t, float y, float& dydt) override
	{
	}
	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{
		dydt[0] = y[1];
		float numer = -2.f * y[0] * (2.f * y[1] * y[1] - 1);
		float denom = 1 + 4.f * y[0] * y[0];

		
		dydt[1] = numer / denom;

	}
};


struct TwoMass : public ODE<float>::Derivative {
	// Inherited via Derivative
	float gamma, beta;

	TwoMass(float beta, float gamma) { this->beta = beta; this->gamma = gamma; }
	virtual void differentiateEq(float t, float y, float& dydt) override
	{

	}

	virtual void differentiateEqs(float t, std::vector<float>& y, std::vector<float>& dydt) override
	{
		float rSq = y[0] * y[0];
		dydt[0] = y[1];
		dydt[1] = (beta * beta) / (rSq * y[0]) - gamma / rSq;
		dydt[2] = beta / rSq;

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

		TEST_METHOD(testRK43) {

			float time = 0.0f;
			int n = 100;


			std::vector<float> st{ 1.f, 0.f };
			RK4<float> rk4;
			QFunc gr;

			for (int i = 0; i < n; i++) {
				stringstream _ss;
				_ss << "q: " << st[0] << "\n";
				_ss << "q': " << st[1] << "\n";
				_ss << "time: " << time << "\n";
				
				Logger::WriteMessage(_ss.str().c_str());


				rk4.solveEquations(time, 0.1, st, gr, st, time);
			}


		}

		TEST_METHOD(testRK44) {

			float time = 0.0f;
			int n = 100;


			std::vector<float> st{ 0.0f, 1.f };
			RK4<float> rk4;
			BallHill gr;

			for (int i = 0; i < n; i++) {
				stringstream _ss;
				_ss << "q: " << st[0] << "\n";
				_ss << "q': " << st[1] << "\n";
				_ss << "time: " << time << "\n";

				Logger::WriteMessage(_ss.str().c_str());


				rk4.solveEquations(time, 0.1, st, gr, st, time);
			}


		}

	};
}