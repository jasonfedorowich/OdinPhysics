#pragma once
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <algorithm> 

#include "OdinMath.h"

namespace OdinMath {
	template<typename real>
	struct Math {

		static real odSqrt(real x);
		static real odPow(real b,  real e);

		static const real& odMax(const real& x, const real& y);
		static real odMax(const real&& x, const real&& y);

		static const real& odMin(const real& x, const real& y);
		static real odMin(const real&& x, const real&& y);


		static real odCos(real x);
		static real odSin(real x);
		static real odTan(real x);
		static real odAcos(real x);
		static real odAsin(real x);
		static real odAtan(real x);
		static real odLog10(real x);
		static real odLoge(real x);
		static real odLog2(real x);
		static real sign(real x);



		static const real REAL_MAX;
		static const real REAL_MIN;
		static const real PI;
		static const real PI_OVER_2;
		static const real PI_OVER_4;
		static const real e;

	};

	template<> const float Math<float>::REAL_MAX = FLT_MAX;
	template<> const float Math<float>::REAL_MIN = FLT_MIN;
	template<> const float Math<float>::PI = 3.1415926535897932384f;
	template<> const float Math<float>::PI_OVER_2 = Math<float>::PI / 2;
	template<> const float Math<float>::PI_OVER_4 = Math<float>::PI / 4;
	template<> const float Math<float>::e = 2.71828182845904523536f;


	template<> const double Math<double>::REAL_MAX = DBL_MAX;
	template<> const double Math<double>::REAL_MIN = DBL_MIN;
	template<> const double Math<double>::PI = 3.1415926535897932384;
	template<> const double Math<double>::PI_OVER_2 = Math<double>::PI / 2;
	template<> const double Math<double>::PI_OVER_4 = Math<double>::PI / 4;
	template<> const double Math<double>::e = 2.71828182845904523536;


	

	template<typename real>
	inline real Math<real>::odSqrt( real x)
	{
		return sqrt(x);
	}
	template<typename real>
	inline real Math<real>::odPow( real b,  real e)
	{
		return pow(b, e);
	}

	template<typename real>
	inline const real& Math<real>::odMax(const real& x, const real& y)
	{
		return x > y ? x : y;
	}

	template<typename real>
	inline real Math<real>::odMax(const real&& x, const real&& y)
	{
		return x > y ? x : y;
	}

	template<typename real>
	inline const real& Math<real>::odMin(const real& x, const real& y)
	{
		return x < y ? x : y;
	}

	template<typename real>
	inline real Math<real>::odMin(const real&& x, const real&& y)
	{
		return x < y ? x : y;
	}

	template<typename real>
	inline real Math<real>::odCos(real x)
	{
		return cos(x);
	}

	template<typename real>
	inline real Math<real>::odSin(real x)
	{
		return sin(x);
	}

	template<typename real>
	inline real Math<real>::odTan(real x)
	{
		return tan(x);
	}

	template<typename real>
	inline real Math<real>::odAcos(real x)
	{
		return acos(x);
	}

	template<typename real>
	inline real Math<real>::odAsin(real x)
	{
		return asin(x);
	}

	template<typename real>
	inline real Math<real>::odAtan(real x)
	{
		return atan(x);
	}

	template<typename real>
	inline real Math<real>::odLog10(real x)
	{
		return log10(x);
	}

	template<typename real>
	inline real Math<real>::odLoge(real x)
	{
		return log(x);
	}

	template<typename real>
	inline real Math<real>::odLog2(real x)
	{
		return log2(x);
	}

	template<typename real>
	inline real Math<real>::sign(real x)
	{
		return (real)(x < (real)0.0 ? -1.0 : 1.0);
	}

	typedef Math<float> Mathf;
	typedef Math<double> Mathd;
}
