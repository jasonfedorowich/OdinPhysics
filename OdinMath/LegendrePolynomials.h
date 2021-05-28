#pragma once
#include "OdinMath.h"
#include <vector>
namespace OdinMath {

	template<typename real>
	struct LegendrePolynomial {



		std::vector<real> coefficients(int degree);
		std::vector<real> roots(int degree);


	};


	template<typename real>
	inline std::vector<real> LegendrePolynomial<real>::coefficients(int degree)
	{
		return std::vector<real>();
	}

	template<typename real>
	inline std::vector<real> LegendrePolynomial<real>::roots(int degree)
	{
		return std::vector<real>();
	}

}
