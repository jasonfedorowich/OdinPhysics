#pragma once
namespace OdinMath {

	template<typename real>
	struct BSplineBasis {

		std::vector<real> knotVector;

		BSplineBasis() {};
		BSplineBasis(int d, std::vector<real>&& knotVector = {});




	};

}