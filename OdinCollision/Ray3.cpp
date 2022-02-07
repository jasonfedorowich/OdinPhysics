#include "OdinCollision.h"
namespace OdinCollision {
	Ray3::Ray3(std::vector<ODVector3>& points)
	{
		using namespace OdinMath;

		ODVector3 start = points[0];
		ODVector3 end = points[0];

		for (unsigned i = 0; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);
			end[2] = Math<rl>::odMax(end[2], points[i][2]);
			start[2] = Math<rl>::odMin(start[2], points[i][2]);


		}
		this->p = start;
		this->d = end - start;
	}
	Ray3::Ray3(std::vector<ODVector3>&& points)
	{
		using namespace OdinMath;

		ODVector3 start = points[0];
		ODVector3 end = points[0];

		for (unsigned i = 0; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);
			end[2] = Math<rl>::odMax(end[2], points[i][2]);
			start[2] = Math<rl>::odMin(start[2], points[i][2]);


		}
		this->p = start;
		this->d = end - start;
	}
	Ray3& Ray3::operator=(const Ray3& r)
	{
		if (this != &r) {
			this->p = r.p;
			this->d = r.d;
		}
		return *this;

	}
	bool Ray3::intersects(Ray3& other)
	{
		rl t, s;
		ODVector3 p1, p2;
		rl dist = closestPoints(other, s, t, p1, p2);
		if (dist == 0.f || dist < OdinMath::Math<rl>::eps) {
			return true;
		}
	}
	bool Ray3::contains(Ray3& other)
	{
		return intersects(other);
	}
	bool Ray3::disjoint(Ray3& other)
	{
		return !intersects(other);
	}
	Ray3 Ray3::merge(Ray3& other)
	{
		Ray3 ray;
		ODVector3 e1 = p + d;
		ODVector3 e2 = other.p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, other.p, mini);
		OdinMath::min<rl>(mini, e1, mini);
		OdinMath::min<rl>(mini, e2, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, e2, maxi);
		OdinMath::max<rl>(maxi, p, maxi);
		OdinMath::max<rl>(maxi, other.p, maxi);



		ray.p = mini;
		ray.d = maxi - mini;

		
		return ray;
	}
	void Ray3::makeUnion(Ray3& other)
	{
		ODVector3 e1 = p + d;
		ODVector3 e2 = other.p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, other.p, mini);
		OdinMath::min<rl>(mini, e1, mini);
		OdinMath::min<rl>(mini, e2, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, e2, maxi);
		OdinMath::max<rl>(maxi, p, maxi);
		OdinMath::max<rl>(maxi, other.p, maxi);

		this->p = mini;
		this->d = maxi - mini;

	}
	Ray3 Ray3::merge(ODVector3& pt)
	{
		ODVector3 e1 = p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, e1, mini);
		OdinMath::min<rl>(mini, pt, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, p, maxi);
		OdinMath::max<rl>(maxi, pt, maxi);

		Ray3 ray;
		ray.p = mini;
		ray.d = maxi - mini;
		return ray;

	}
	void Ray3::makeUnion(ODVector3& pt)
	{
		ODVector3 e1 = p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, e1, mini);
		OdinMath::min<rl>(mini, pt, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, p, maxi);
		OdinMath::max<rl>(maxi, pt, maxi);

		this->p = mini;
		this->d = maxi - mini;

	}
	Ray3 Ray3::merge(ODVector3&& pt)
	{
		ODVector3 e1 = p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, e1, mini);
		OdinMath::min<rl>(mini, pt, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, p, maxi);
		OdinMath::max<rl>(maxi, pt, maxi);

		Ray3 ray;
		ray.p = mini;
		ray.d = maxi - mini;
		return ray;
	}
	void Ray3::makeUnion(ODVector3&& pt)
	{
		ODVector3 e1 = p + d;
		ODVector3 mini;
		OdinMath::min<rl>(p, e1, mini);
		OdinMath::min<rl>(mini, pt, mini);

		ODVector3 maxi;
		OdinMath::max<rl>(e1, p, maxi);
		OdinMath::max<rl>(maxi, pt, maxi);

		this->p = mini;
		this->d = maxi - mini;

	}
	rl Ray3::closestPoints(Ray3& other, rl& s, rl& t, ODVector3& p1, ODVector3& p2)
	{
		using namespace OdinMath;
		ODVector3 r = p - other.p;
		rl a = d.dot(d);
		rl b = d.dot(other.d);
		rl c = d.dot(r);
		rl e = other.d.dot(other.d);
		rl f = other.d.dot(r);
		rl d = a * e - b * b;

		//planes are parallel
		if (d == 0 || Math<rl>::odAbs(d) <= OdinMath::Math<rl>::eps) {
			p1 = p;
			s = (rl)0.f;
			if (a == 0 || Math<rl>::odAbs(a) <= OdinMath::Math<rl>::eps) {
				throw std::invalid_argument("Ray3 is invalid: it represents a point");
			}
			t = c / a;
			p2 = other.p + t * other.d;
			return p1.distance(p2);
		}


		s = (b * f - c * e) / d;
		t = (a * f - b * c) / d;
		
		p1 = p + this->d * s;
		p2 = other.p + other.d * t;

		return p1.distance(p2);
	}
}