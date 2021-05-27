#pragma once
#include "OdinMath.h"
#include "ODE.h"

namespace OdinMath {

	template<typename real>
	class RK4 : public ODE<real> {

	public:
		virtual void solveEquation(real t0, real t1, real y0, real dt, typename ODE<real>::Derivative& derivative, std::vector<real>& yOut, std::vector<real>& tOut);
		virtual void solveEquations(real t0, real dt, std::vector<real>& yIn, typename ODE<real>::Derivative& derivative, std::vector<real>& yOut, real& tOut);
		
	};
	/*typedef RK4<float> RK4f;
	typedef RK4<double> RK4d;*/
	//todo
	template<typename real>
	class RK2 : public ODE<real> {


	};
	
#include "RungeKutta.inl"
	
}