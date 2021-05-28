#pragma once
#include "OdinMath.h"
#include "SingleIntegral.h"
#include "LegendrePolynomials.h"

namespace OdinMath {

	template<typename real>
	class GLQ : public SingleIntegral<real> {




	public:
		virtual void evaluate(real a, real b, int n, typename SingleIntegral<real>::Function& function, real& I);

	};


	template<typename real>
	inline void GLQ<real>::evaluate(real a, real b, int n, typename SingleIntegral<real>::Function& function, real& I)
	{
		//todo support other polynomials
		assert(n == 5 || n == 6);

		real* coeff = nullptr;
		real* roots = nullptr;
		switch (n) {
		case 5:
		{

			real coefft[5] = {(real)0.2369268850,(real)0.4786286705,(real)0.5688888889,(real)0.4786286705,(real)0.2369268850};
			real rootst[5] = {(real)-0.9061798459,(real)-0.5384693101,(real)0.0,(real)+0.5384693101,(real)+0.9061798459};
			coeff = coefft;
			roots = rootst;
		}
		break;
		case 6:
		{
			real coefft[6] = {(real)0.17132449238,(real)0.36076157305,(real)0.46791393457,(real)0.17132449238,(real)0.36076157305,(real)0.46791393457};
			real rootst[6] = {(real)0.932469514203,(real)-0.932469514203,(real)0.661209386466,(real)-0.661209386466,(real)0.238619186083,(real)-0.238619186083};
			coeff = coefft;
			roots = rootst;
		}
		break;


		}


		real radius = ((real)0.5) * (b - a);
		real center = ((real)0.5) * (b + a);

		I = (real)0.0;
		real fr;
		for (int i = 0; i < n; ++i)
		{
			function.evaluate(radius * roots[i] + center, fr);
			I += coeff[i] * fr;
		}
		I *= radius;



	}

}
