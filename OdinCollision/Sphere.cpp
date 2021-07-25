#include "OdinCollision.h"
namespace OdinCollision {
	BoundingSphere::BoundingSphere(std::vector<ODVector>& points)
	{
		int n = points.size();
	
		ODVector maxi = {OdinMath::Math<rl>::REAL_MIN, OdinMath::Math<rl>::REAL_MIN, OdinMath::Math<rl>::REAL_MIN};
		ODVector mini = {OdinMath::Math<rl>::REAL_MAX, OdinMath::Math<rl>::REAL_MAX, OdinMath::Math<rl>::REAL_MAX };

		for (int i = 0; i < n; i++) {
			maxi[0] = OdinMath::Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = OdinMath::Math<rl>::odMin(mini[0], points[i][0]);

			maxi[1] = OdinMath::Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = OdinMath::Math<rl>::odMin(mini[1], points[i][1]);

			maxi[2] = OdinMath::Math<rl>::odMax(maxi[2], points[i][2]);
			mini[2] = OdinMath::Math<rl>::odMin(mini[2], points[i][2]);

		}

		center[0] = (mini[0] + maxi[0]) / (rl)2.0;
		center[1] = (mini[1] + maxi[1]) / (rl)2.0;
		center[2] = (mini[2] + maxi[2]) / (rl)2.0;

		radius = OdinMath::Math<rl>::REAL_MIN;

		for (int i = 0; i < n; i++) {

			radius = OdinMath::Math<rl>::odMax(center.distance(points[i]), radius);
		}


	}
}

