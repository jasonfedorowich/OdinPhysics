#include "OdinMath.h"

namespace OdinMath {
	BSplineCurve4::BSplineCurve4(std::vector<ODVector4>& controlPoints, int d, bool open, std::vector<rl>&& knotVector) : controlPoints(controlPoints), d(d), n(controlPoints.size())
	{
		basis = new BSplineBasis<rl>(d, n, open, knotVector);

	}
	 void BSplineCurve4::get(rl u, Vector4& pos)
	{
		basis->computeBasis(u);

		Vector4 result{ (rl)0.0, (rl)0.0, (rl)0.0, (rl)0.0 };
		for (int i = 0; i < n; i++) {
			result += (basis->get(i) * controlPoints[i]);

		}

		
	}
}