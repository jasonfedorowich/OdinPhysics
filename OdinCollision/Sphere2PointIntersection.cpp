#include "Sphere2PointIntersection.h"
namespace OdinCollision {
	bool intersection(BoundingSphere& s, ODVector& p)
	{
		return s.center.dot(p) > s.radius * s.radius;
	}
}