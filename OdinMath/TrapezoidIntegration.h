#pragma once
#include "OdinMath.h"
#include "SingleIntegral.h"

namespace OdinMath {
	template<typename real>
	class TrapezoidIntegral : public SingleIntegral<real> {

	public:
		virtual void evaluate(real a, real b, int n, typename SingleIntegral<real>::Function& function, real& I);


	};


#include "TrapezoidIntegration.inl"
	

}


