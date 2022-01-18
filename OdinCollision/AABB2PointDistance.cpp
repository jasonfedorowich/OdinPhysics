#include "AABB2PointDistance.h"

namespace OdinCollision {



	//rl distanceSqr(AABB<3>& a, ODVector& p, ODVector& cp)
	//{
	//	rl dist = (rl)0.0;
	//	for (int i = 0; i < 3; i++) {
	//		rl v = p[i];
	//		if (v < a.mini[i]) {
	//			
	//			dist += (a.mini[i] - v) * (a.mini[i] - v);
	//			v = a.mini[i];
	//		}
	//		if (v > a.maxi[i]) {

	//			
	//			dist += (v - a.maxi[i]) * (v - a.maxi[i]);
	//			v = a.maxi[i];

	//		}
	//		cp[i] = v;


	//	}

	//	return dist;

	//}

	//void nearestPoint(AABB<3>& b, ODVector& p, ODVector& cp)
	//{

	//	for (int i = 0; i < 3; i++) {
	//		rl v = p[i];
	//		v = OdinMath::Math<rl>::odMax(v, b.mini[i]);
	//		v = OdinMath::Math<rl>::odMin(v, b.maxi[i]);

	//		cp[i] = v;

	//	}
	//}

}