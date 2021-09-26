#pragma once
#include "OdinMath.h"
#include "BSplineBasis.h"
namespace OdinMath {

	void computeControl(std::vector<Vector4>& pts);

	struct BSplineCurve4 {
		std::vector<Vector4> controlPoints;
		std::vector<Vector4> knotVector;
		int d;
		int n;
		BSplineBasis<rl>* basis;
		BSplineCurve4(std::vector<Vector4>& controlPoints, int d, bool open, std::vector<rl>&& knotVector = {});
		
		void get(rl u, Vector4& pos);
		~BSplineCurve4() { delete basis; }
		
	};

}