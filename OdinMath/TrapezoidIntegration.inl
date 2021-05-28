#pragma once
#include "TrapezoidIntegration.h"

template<typename real>
inline void TrapezoidIntegral<real>::evaluate(real a, real b, int n, typename SingleIntegral<real>::Function& function, real& I)
{
	assert(n != 0);
	real dt = (b - a) / (real)n;
	real fr, frt;

	function.evaluate(a, fr);
	function.evaluate(b, frt);

	I = (real)0.5 * (fr + frt);
	for (int i = 1; i < n; i++) {
		function.evaluate(a + dt * i, fr);
		I += fr;


	}


	I *= dt;



}