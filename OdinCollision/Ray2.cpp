#include "OdinCollision.h"
namespace OdinCollision {

	Ray2::Ray2(std::vector<ODVector2>& points)
	{
		ODVector2 maxi = points[0];
		ODVector2 mini = points[0];

		for (int i = 1; i < points.size(); i++) {
			OdinMath::max(points[i], maxi, maxi);
			OdinMath::min(points[i], mini, mini);

		}

		this->p = mini;
		this->d = maxi - mini;
	}
	Ray2::Ray2(std::vector<ODVector2>&& points)
	{
		ODVector2 maxi = points[0];
		ODVector2 mini = points[0];

		for (int i = 1; i < points.size(); i++) {
			OdinMath::max(points[i], maxi, maxi);
			OdinMath::min(points[i], mini, mini);

		}

		this->p = mini;
		this->d = maxi - mini;
	}
	Ray2& Ray2::operator=(const Ray2& s)
	{
		if (this != &s) {
			this->d = s.d;
			this->p = s.p;
		}
		return *this;
	}
	bool Ray2::intersects(Ray2& other)
	{
		rl s, t;
		ODVector2 pt;
		return intersectionPoint(other, s, t, pt);
	}
	bool Ray2::contains(Ray2& other)
	{
		return intersects(other);
	}
	bool Ray2::disjoint(Ray2& other)
	{
		return !intersects(other);
	}
	Ray2 Ray2::merge(Ray2& other)
	{
		ODVector2 mini = other.p;
		ODVector2 e1 = p + d;
		ODVector2 e2 = other.p + other.d;
		ODVector2 tmp;

		OdinMath::min<rl>(mini, p, mini);
		OdinMath::min<rl>(e1, e2, tmp);
		OdinMath::min<rl>(mini, tmp, mini);

		OdinMath::max<rl>(p, other.p, tmp);
		OdinMath::max<rl>(e1, e2, e1);
		OdinMath::max<rl>(e1, tmp, e1);

		Ray2 ray;
		ray.p = mini;
		ray.p = e1 - mini;
		return ray;
	}
	void Ray2::makeUnion(Ray2& other)
	{
		ODVector2 mini = other.p;
		ODVector2 e1 = p + d;
		ODVector2 e2 = other.p + other.d;
		ODVector2 tmp;

		OdinMath::min<rl>(mini, p, mini);
		OdinMath::min<rl>(e1, e2, tmp);
		OdinMath::min<rl>(mini, tmp, mini);

		OdinMath::max<rl>(p, other.p, tmp);
		OdinMath::max<rl>(e1, e2, e1);
		OdinMath::max<rl>(e1, tmp, e1);

		this->p = mini;
		this->d = e1 - mini;

	}
	Ray2 Ray2::merge(ODVector2& pt)
	{
		ODVector2 mini;
		ODVector2 e1 = p + d;
		ODVector2 tmp;

		OdinMath::min<rl>(p, pt, mini);
		OdinMath::min<rl>(e1, mini, mini);
		

		OdinMath::max<rl>(e1, pt, tmp);
		OdinMath::max<rl>(p, tmp, tmp);

		Ray2 ray;
		ray.p = mini;
		ray.p = tmp - mini;
		return ray;
	}
	void Ray2::makeUnion(ODVector2& pt)
	{
		ODVector2 mini;
		ODVector2 e1 = p + d;
		ODVector2 tmp;

		OdinMath::min<rl>(p, pt, mini);
		OdinMath::min<rl>(e1, mini, mini);


		OdinMath::max<rl>(e1, pt, tmp);
		OdinMath::max<rl>(p, tmp, tmp);

		this->p = mini;
		this->d = tmp - mini;

	}
	Ray2 Ray2::merge(ODVector2&& pt)
	{
		ODVector2 mini;
		ODVector2 e1 = p + d;
		ODVector2 tmp;

		OdinMath::min<rl>(p, pt, mini);
		OdinMath::min<rl>(e1, mini, mini);


		OdinMath::max<rl>(e1, pt, tmp);
		OdinMath::max<rl>(p, tmp, tmp);

		Ray2 ray;
		ray.p = mini;
		ray.p = tmp - mini;
		return ray;
	}
	void Ray2::makeUnion(ODVector2&& pt)
	{
		ODVector2 mini;
		ODVector2 e1 = p + d;
		ODVector2 tmp;

		OdinMath::min<rl>(p, pt, mini);
		OdinMath::min<rl>(e1, mini, mini);


		OdinMath::max<rl>(e1, pt, tmp);
		OdinMath::max<rl>(p, tmp, tmp);

		this->p = mini;
		this->d = tmp - mini;
	}
	bool Ray2::intersectionPoint(Ray2& other, rl& s, rl& t, ODVector2& pt)
	{
		using namespace OdinMath;
		ODVector2 inv = { other.d[1], other.d[0] };


		ODVector2 prod = d % inv;
		rl denom = prod[0] - prod[1];
		if (Math<rl>::odAbs(denom) <= Math<rl>::eps || denom == (rl)0.f) {
			return false;
		}
		ODVector2 diff = p - other.p;
		inv = { diff[1], diff[0] };
		prod = other.d % inv;

		rl numa = prod[0] - prod[1];
		s = numa / denom;

		prod = d % inv;
		rl numb = prod[0] - prod[1];
		t = numb / denom;

		pt = p + (d * s);
		return true;
	}
}