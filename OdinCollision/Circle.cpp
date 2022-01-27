#include "OdinCollision.h"

namespace OdinCollision {



	//BoundingCircle::BoundingCircle(std::vector<ODVector>& points)
	//{
	//	assert(points.size() >= 1);
	//	AABB<2> aabb(points);
	//	center = (aabb.maxi + aabb.mini);
	//	center /= (rl)2.0;

	//	radius = center.distance(points[0]);
	//	for (unsigned i = 1; i < points.size(); i++) {
	//		radius = OdinMath::Math<rl>::odMax(radius, center.distance(points[i]));
	//	}
	//}

	//BoundingCircle::BoundingCircle(std::vector<ODVector>&& points)
	//{

	//	assert(points.size() >= 1);
	//	AABB<2> aabb(points);
	//	center = (aabb.maxi + aabb.mini);
	//	center /= (rl)2.0;

	//	radius = center.distance(points[0]);
	//	for (unsigned i = 1; i < points.size(); i++) {
	//		radius = OdinMath::Math<rl>::odMax(radius, center.distance(points[i]));

	//	}

	//}

	//bool BoundingCircle::overlaps(BoundingCircle& other)
	//{
	//	return other.center.distance(other.center) <= (other.radius + radius);
	//}

	BoundingCircle::BoundingCircle(std::vector<ODVector2>& points)
	{
		using namespace OdinMath;
		AABB2 temp(points);
		center = temp.center;
		radius = Math<rl>::odMax(temp.extents[0], temp.extents[1]);
	}

	BoundingCircle::BoundingCircle(std::vector<ODVector2>&& points)
	{
		using namespace OdinMath;
		AABB2 temp(points);
		center = temp.center;
		radius = Math<rl>::odMax(temp.extents[0], temp.extents[1]);
	}

	BoundingCircle& BoundingCircle::operator=(const BoundingCircle& circle)
	{
		if (this != &circle) {
			center = circle.center;
			radius = circle.radius;
		}
		return *this;
	}

	bool BoundingCircle::intersects(BoundingCircle& other)
	{
		ODVector2 tmp = other.center - this->center;
		rl r = other.radius + radius;
		return tmp.dot(tmp) <= (r * r);
	}

	bool BoundingCircle::contains(BoundingCircle& other)
	{
		rl d = this->center.distance(other.center);
		return d > (radius + other.radius) ? false : d <= (radius - other.radius);
		
	}

	bool BoundingCircle::disjoint(BoundingCircle& other)
	{
		return !intersects(other);
		
	}

	BoundingCircle BoundingCircle::merge(BoundingCircle& s)
	{
		BoundingCircle ms;
		ODVector2 offset = s.center - center;
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
			if (dist > 0)
				ms.center += offset * ((ms.radius - radius) / dist);



		}

		return ms;


	}

	void BoundingCircle::makeUnion(BoundingCircle& s)
	{
		ODVector2 offset = s.center - center;
		rl distSq = offset.dot(offset);
		rl radiusDiff = radius - s.radius;

		if (radiusDiff * radiusDiff >= distSq) {
			if (s.radius > radius) {
				this->center = s.center;
				this->radius = s.radius;
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

	BoundingCircle BoundingCircle::merge(ODVector2& p)
	{
		ODVector2 offset = p - center;
		rl distSq = offset.dot(offset);
		
		if (radius * radius >= distSq) {
			return *this;

		}
		else {
			BoundingCircle bc;
			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			bc.radius = (dist + radius) * (rl)0.5;
			bc.center = center;
			if (dist > 0)
				bc.center += offset * ((bc.radius - radius) / dist);

			return bc;

		}
	}

	void BoundingCircle::makeUnion(ODVector2& p)
	{
		ODVector2 offset = p - center;
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

	BoundingCircle BoundingCircle::merge(ODVector2&& p)
	{
		ODVector2 offset = p - center;
		rl distSq = offset.dot(offset);

		if (radius * radius >= distSq) {
			return *this;

		}
		else {
			BoundingCircle bc;
			rl dist = OdinMath::Math<rl>::odSqrt(distSq);
			bc.radius = (dist + radius) * (rl)0.5;
			bc.center = center;
			if (dist > 0)
				bc.center += offset * ((bc.radius - radius) / dist);

			return bc;

		}
	}

	void BoundingCircle::makeUnion(ODVector2&& p)
	{
		ODVector2 offset = p - center;
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