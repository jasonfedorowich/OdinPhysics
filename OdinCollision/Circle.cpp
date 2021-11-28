#include "OdinCollision.h"

namespace OdinCollision {



	BoundingCircle::BoundingCircle(std::vector<ODVector>& points)
	{
		assert(points.size() >= 1);
		AABB<2> aabb(points);
		center = (aabb.maxi + aabb.mini);
		center /= (rl)2.0;

		radius = center.distance(points[0]);
		for (unsigned i = 1; i < points.size(); i++) {
			radius = OdinMath::Math<rl>::odMax(radius, center.distance(points[i]));
		}
	}

	BoundingCircle::BoundingCircle(std::vector<ODVector>&& points)
	{

		assert(points.size() >= 1);
		AABB<2> aabb(points);
		center = (aabb.maxi + aabb.mini);
		center /= (rl)2.0;

		radius = center.distance(points[0]);
		for (unsigned i = 1; i < points.size(); i++) {
			radius = OdinMath::Math<rl>::odMax(radius, center.distance(points[i]));

		}

	}

	bool BoundingCircle::overlaps(BoundingCircle& other)
	{
		return other.center.distance(other.center) <= (other.radius + radius);
	}

}