#include "Sphere2PointIntersection.h"
namespace OdinCollision {
	bool intersection(BoundingSphere& s, ODVector& p)
	{
		ODVector d = s.center - p;

		return d.dot(d) > s.radius * s.radius;
	}
}