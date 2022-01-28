#include "OdinCollision.h"

namespace OdinCollision {
	BoundingSphere::BoundingSphere(std::vector<ODVector3>& points)
	{
		int n = points.size();
	
		ODVector3 maxi{OdinMath::Math<rl>::REAL_MIN, OdinMath::Math<rl>::REAL_MIN, OdinMath::Math<rl>::REAL_MIN};
		ODVector3 mini{OdinMath::Math<rl>::REAL_MAX, OdinMath::Math<rl>::REAL_MAX, OdinMath::Math<rl>::REAL_MAX };

		for (int i = 0; i < n; i++) {
			maxi[0] = OdinMath::Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = OdinMath::Math<rl>::odMin(mini[0], points[i][0]);

			maxi[1] = OdinMath::Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = OdinMath::Math<rl>::odMin(mini[1], points[i][1]);

			maxi[2] = OdinMath::Math<rl>::odMax(maxi[2], points[i][2]);
			mini[2] = OdinMath::Math<rl>::odMin(mini[2], points[i][2]);

		}
		center = mini + maxi;
		center *= (rl)0.5;
		mini = maxi - center;
		OdinMath::vAbs<rl>(mini);

		using namespace OdinMath;
		radius = Math<rl>::odMax(mini[0], Math<rl>::odMax(mini[1], mini[2]));

	
	}
	BoundingSphere::BoundingSphere(std::vector<ODVector3>&& points) : BoundingSphere(points)
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
	bool BoundingSphere::intersects(BoundingSphere& sphere)
	{
		rl r = radius + sphere.radius;
		ODVector3 tmp = sphere.center - center;
		return tmp.dot(tmp) <= (r * r);
	}

	bool BoundingSphere::contains(BoundingSphere& sphere)
	{
		rl d = this->center.distance(sphere.center);
		return d > (radius + sphere.radius) ? false : d <= (radius - sphere.radius);

	}

	bool BoundingSphere::disjoint(BoundingSphere& other)
	{
		return !intersects(other);
	}
	
	BoundingSphere BoundingSphere::merge(BoundingSphere& s)
	{
		BoundingSphere ms;
		ODVector3 offset = s.center - center;
		rl distSq = offset.dot(offset);
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
		ODVector3 offset = s.center - center;
		rl distSq = offset.dot(offset);
		rl radiusDiff = radius - s.radius;

		if (radiusDiff * radiusDiff >= distSq) {
			if (s.radius > radius) {
				center = s.center;
				radius = s.radius;
			}
			
		}
		else {
			
			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			rl rad = (dist + s.radius + radius) * (rl)0.5;
			if (dist > 0)
				center += offset * ((rad - radius) / dist);
			radius = rad;



		}

	}

	BoundingSphere BoundingSphere::merge(ODVector3& p)
	{
		BoundingSphere ms;
		ODVector3 offset = p - center;
		rl distSq = offset.dot(offset);
		

		if (radius * radius >= distSq) {
			ms.center = center;
			ms.radius = radius;
			
		}
		else {

			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			ms.radius = (dist + radius) * (rl)0.5;
			ms.center = center;
			if (dist > 0)
				ms.center += offset * ((ms.radius - radius) / dist);



		}

		return ms;
	}

	void BoundingSphere::makeUnion(ODVector3& p)
	{
		ODVector3 offset = p - center;
		rl distSq = offset.dot(offset);


		if (radius * radius >= distSq) {
			return;

		}
		else {

			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			rl rad = (dist + radius) * (rl)0.5;
			if (dist > 0)
				center += offset * ((rad - radius) / dist);



		}

	}

	BoundingSphere BoundingSphere::merge(ODVector3&& p)
	{
		BoundingSphere ms;
		ODVector3 offset = p - center;
		rl distSq = offset.dot(offset);


		if (radius * radius >= distSq) {
			ms.center = center;
			ms.radius = radius;

		}
		else {

			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			ms.radius = (dist + radius) * (rl)0.5;
			ms.center = center;
			if (dist > 0)
				ms.center += offset * ((ms.radius - radius) / dist);



		}

		return ms;
	}

	void BoundingSphere::makeUnion(ODVector3&& p)
	{
		ODVector3 offset = p - center;
		rl distSq = offset.dot(offset);


		if (radius * radius >= distSq) {
			return;

		}
		else {

			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			rl rad = (dist + radius) * (rl)0.5;
			if (dist > 0)
				center += offset * ((rad - radius) / dist);



		}
	}
	
}

