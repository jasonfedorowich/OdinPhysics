#pragma once
#include "OdinMath.h"
namespace OdinMath {
	template<typename real>
	class SingleIntegral {

	public:
		struct Function {
			void* uData;
			Function(void* uData) : uData(uData) {}
			Function() : Function(nullptr) {};
			
			virtual void evaluate(real t, real& xOut) = 0;


		};
	public:
		virtual void evaluate(real a, real b, int n, Function& function, real& I) = 0;

	};

}