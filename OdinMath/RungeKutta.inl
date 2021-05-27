#pragma once
#include "RungeKutta.h"

template<typename real>
inline void RK4<real>::solveEquation(real t0, real t1, real y0, real dt,  typename ODE<real>::Derivative& derivative, std::vector<real>& yOut, std::vector<real>& tOut)
{
	auto rk4 = [&](real tt, real yy, real dt) {
		real first;
		derivative.differentiateEq(tt, yy, first);
		real k1 = dt * first;
		real second;
		derivative.differentiateEq(tt + (real)0.5 * dt, yy + (real)0.5 * k1, second);
		real k2 = dt * second;
		real third;
		derivative.differentiateEq(tt + (real)0.5 * dt, yy + (real)0.5 * k2, third);
		real k3 = dt * third;
		real fourth;
		derivative.differentiateEq(tt + dt, yy + k3, fourth);
		real k4 = dt * fourth;
		return (k1 + (real)2.0 * k2 + (real)2.0 * k3 + k4) / (real)6.0;

	};


	int n = 1 + (t1 - t0) / dt;
	yOut.push_back(y0);
	real t;
	real y;

	for (int i = 0; i < n; i++) {
		y = yOut.back();
		t = t0 + dt * i;
		y += rk4(t, y, dt);
		yOut.push_back(y);
		tOut.push_back(t);


	}

	tOut.push_back(t);


}
template<typename real>
inline void RK4<real>::solveEquations(real t0, real dt, std::vector<real>& yIn, typename ODE<real>::Derivative& derivative, std::vector<real>& yOut, real& tOut)
{
	//todo
}