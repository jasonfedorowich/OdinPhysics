#pragma once
#include <vector>
namespace OdinMath {

	template<typename real>
	class ODE {
	public:
		struct Derivative {

			void* userData;
			Derivative() : Derivative(nullptr) {}
			Derivative(void* userData) { this->userData = userData; }


			virtual void differentiateEq(real t, real y, real& dydt) = 0;
			virtual void differentiateEqs(real t, std::vector<real>& y, std::vector<real>& dydt) = 0;

		};
	public:
		/*Solve differential equation in the form dy/dt */
		virtual void solveEquation(real t0, real t1, real y0, real dt, Derivative& derivative, std::vector<real>& yOut, std::vector<real>& tOut) = 0;
		/*Solve the coupled differential equations */
		virtual void solveEquations(real t0, real dt, std::vector<real>& yIn, Derivative& derivative, std::vector<real>& yOut, real& tOut) = 0;



	};
}