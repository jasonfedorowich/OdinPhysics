#pragma once
#include "OdinMath.h"
#include "BSplineBasis.h"
namespace OdinMath {

	void computeControl(std::vector<ODVector>& pts);
	void computeKnots(std::vector<ODVector>& knts);

	struct BSplineCurve4 {
		std::vector<ODVector> controlPoints;
		std::vector<ODVector> knotVector;
		int degree;
		BSplineCurve4(std::vector<ODVector>& controlPoints, int order, std::vector<rl>&& knotVector = {});

		
	};

}