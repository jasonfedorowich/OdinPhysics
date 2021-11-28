#pragma once
#include "RungeKutta.h"

template<typename real>
inline void RK4<real>::solveEquation(real t0, real t1, real y0, real dt,  typename ODE<real>::Derivative& derivative, std::vector<real>& yOut, std::vector<real>& tOut)
{
	auto rk4 = [&](real tt, real yy, real dt) {
		real k1;
		derivative.differentiateEq(tt, yy, k1);
		k1 *= dt;
		real k2;
		derivative.differentiateEq(tt + (real)0.5 * dt, yy + (real)0.5 * k1, k2);
		k2 *= dt;
		real k3;
		derivative.differentiateEq(tt + (real)0.5 * dt, yy + (real)0.5 * k2, k3);
		k3 *= dt;
		real k4;
		derivative.differentiateEq(tt + dt, yy + k3, k4);
		k4 *= dt;
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
	real halfDt = dt * (real)(0.5);
	unsigned n = yIn.size();
	std::vector<real> k1(n);
	derivative.differentiateEqs(t0, yIn, k1);

	std::vector<real> yIn2(n);
	for (int i = 0; i < n; i++) {
		k1[i] *= dt;
		yIn2[i] = yIn[i] + (real)0.5 * k1[i];
	}

	std::vector<real> k2(n);
	derivative.differentiateEqs(t0 + halfDt, yIn2, k2);

	std::vector<real> yIn3(n);
	for (int i = 0; i < n; i++) {
		k2[i] *= dt;
		yIn3[i] = yIn[i] + (real)0.5 * k2[i];
	}

	std::vector<real> k3(n);
	derivative.differentiateEqs(t0 + halfDt, yIn3, k3);

	std::vector<real> yIn4(n);
	for (int i = 0; i < n; i++) {
		k3[i] *= dt;
		yIn4[i] = yIn[i] + k3[i];
	}

	std::vector<real> k4(n);
	derivative.differentiateEqs(t0 + dt, yIn4, k4);

	for (int i = 0; i < n; i++) {
		k4[i] *= dt;
		
	}
	tOut = t0 + dt;
	if (yOut.size() > n)
		yOut = std::vector<real>(n);

	for (int i = 0; i < n; i++) {
		yOut[i] = yIn[i] + (k1[i] + (real)2.0 * k2[i] + (real)2.0 * k3[i] + k4[i]) / (real)6.0;

	}


}