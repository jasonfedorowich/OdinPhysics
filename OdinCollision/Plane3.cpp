#include "OdinCollision.h"

namespace OdinCollision {



	Plane3::Plane3(ODVector3& p1, ODVector3& p2, ODVector3& p3)
	{
		pointsToPlane(*this, p1, p2, p3);
	}

	Plane3::Plane3(ODVector3&& p1, ODVector3&& p2, ODVector3&& p3)
	{
		pointsToPlane(*this, p1, p2, p3);
	}

	Plane3& Plane3::operator=(const Plane3& p)
	{
		if (this != &p) {
			this->normal = p.normal;
			this->point = p.point;

		}
		return *this;
	}

	bool Plane3::intersects(Plane3& other)
	{
		using namespace OdinMath;
		ODVector3 cr = normal.cross(other.normal);
		vAbs(cr);
		ODVector3 ep{ Math<rl>::eps, Math<rl>::eps, Math<rl>::eps };
		ODVector3 isSmaller = cr > ep;
		isSmaller = isSmaller & cr;
		return ODVector3::zeros() != isSmaller;
	}

	bool Plane3::contains(Plane3& other)
	{
		return intersects(other);
	}

	bool Plane3::disjoint(Plane3& other)
	{
		return !intersects(other);
	}

	Plane3 Plane3::merge(Plane3& other)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d/a, 0.f, 0.f};
			return Plane3(point, other.point, p);
		}
		else if (b > 0) {
			ODVector3 p{0.f, -d/b, 0.f };
			return Plane3(point, other.point, p);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d/c };
			return Plane3(point, other.point, p);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	void Plane3::makeUnion(Plane3& other)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d / a, 0.f, 0.f };
			pointsToPlane(*this, this->point, p, other.point);
		}
		else if (b > 0) {
			ODVector3 p{ 0.f, -d / b, 0.f };
			pointsToPlane(*this, this->point, p, other.point);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d / c };
			pointsToPlane(*this, this->point, p, other.point);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	Plane3 Plane3::merge(ODVector3& pt)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d / a, 0.f, 0.f };
			return Plane3(point, pt, p);
		}
		else if (b > 0) {
			ODVector3 p{ 0.f, -d / b, 0.f };
			return Plane3(point, pt, p);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d / c };
			return Plane3(point, pt, p);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	void Plane3::makeUnion(ODVector3& pt)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d / a, 0.f, 0.f };
			pointsToPlane(*this, this->point, pt, p);
		}
		else if (b > 0) {
			ODVector3 p{ 0.f, -d / b, 0.f };
			pointsToPlane(*this, this->point, pt, p);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d / c };
			pointsToPlane(*this, this->point, pt, p);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	Plane3 Plane3::merge(ODVector3&& pt)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d / a, 0.f, 0.f };
			return Plane3(point, pt, p);
		}
		else if (b > 0) {
			ODVector3 p{ 0.f, -d / b, 0.f };
			return Plane3(point, pt, p);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d / c };
			return Plane3(point, pt, p);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	void Plane3::makeUnion(ODVector3&& pt)
	{
		//plane equation is Ax + By + Cz = D
		rl a, b, c, d;
		getABCD(a, b, c, d);
		if (a > 0) {
			ODVector3 p{ -d / a, 0.f, 0.f };
			pointsToPlane(*this, this->point, pt, p);
		}
		else if (b > 0) {
			ODVector3 p{ 0.f, -d / b, 0.f };
			pointsToPlane(*this, this->point, pt, p);

		}
		else if (c > 0) {
			ODVector3 p{ 0.f, 0.f, -d / c };
			pointsToPlane(*this, this->point, pt, p);

		}
		else
			throw std::invalid_argument("Plane is not relevant");
	}

	void Plane3::getABCD(rl& a, rl& b, rl& c, rl& d)
	{
		d = normal.dot(point);
		a = normal[0];
		b = normal[1];
		c = normal[2];
	}

	void Plane3::pointsToPlane(Plane3& plane, ODVector3& p1, ODVector3& p2, ODVector3& p3)
	{
		ODVector3 p1p2 = p2 - p1;
		ODVector3 p1p3 = p3 - p1;
		plane.normal = p1p2.cross(p1p3);
		plane.point = p1;
	}

}