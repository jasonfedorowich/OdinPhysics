#include "OdinCollision.h"

namespace OdinCollision {
	BoundingSphere::BoundingSphere(std::vector<OdinMath::Vector4>& points)
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
	BoundingSphere::BoundingSphere(std::vector<ODVector>&& points) : BoundingSphere(points)
	{

	}
	BoundingSphere::BoundingSphere(const BoundingSphere& s)
	{
		*this = s;
	}
	BoundingSphere& BoundingSphere::operator=(const BoundingSphere& s)
	{
		if (this != &s) {
			this->center = center;
			this->radius = radius;
		}return *this;
	}
	bool BoundingSphere::overlaps(BoundingSphere& sphere)
	{
		return sphere.center.distance(sphere.center) <= (radius + sphere.radius);
	}
	BoundingSphere BoundingSphere::merge(BoundingSphere& s)
	{
		BoundingSphere ms;
		rl distSq = s.center.dot(s.center);
		rl radiusDiff = radius - s.radius;

		if (radiusDiff * radiusDiff >= distSq) {
			if (s.radius > radius) {
				ms.center = s.center;
				ms.radius = s.radius;
			}
			else {
				ms.center = center;
				ms.radius = radius;
			}
		}
		else {
			ODVector offset = s.center - center;
			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			ms.radius = (dist + s.radius + radius) * (rl)0.5;
			ms.center = center;
			if(dist > 0)
				ms.center += offset * ((ms.radius - radius) / dist);



		}

		return ms;
	}
	void BoundingSphere::makeUnion(BoundingSphere& s)
	{

		rl distSq = s.center.dot(s.center);
		rl radiusDiff = radius - s.radius;

		if (radiusDiff * radiusDiff >= distSq) {
			if (s.radius > radius) {
				center = s.center;
				radius = s.radius;
			}
			
		}
		else {
			ODVector offset = s.center - center;
			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			rl rad = (dist + s.radius + radius) * (rl)0.5;
			if (dist > 0)
				center += offset * ((rad - radius) / dist);
			radius = rad;



		}

	}
	rl BoundingSphere::seperation(BoundingSphere& s)
	{
		return s.center.distance(center) - (s.radius + radius);
	}
}

