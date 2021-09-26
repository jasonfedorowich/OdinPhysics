#include "AABB2PointIntersection.h"

namespace OdinCollision {
	bool intersection(AABB<3>& a, ODVector& p)
	{
		for (int i = 0; i < 3; i++) {
			if (a.maxi[i] < p[i] || a.mini[i] > p[i])
				return false;

		}
		return true;
	}
}