#include "OdinCollision.h"

namespace OdinCollision {




	Plane2& Plane2::operator=(const Plane2& p)
	{
		if (this != &p) {

			this->normal = p.normal;
			this->point = p.point;
		}
		return *this;
	}

	bool Plane2::intersects(Plane2& other)
	{
		using namespace OdinMath;
		ODVector3 cr = normal.cross(other.normal);
		vAbs(cr);
		ODVector3 ep{ Math<rl>::eps, Math<rl>::eps, Math<rl>::eps };
		ODVector3 isSmaller = cr > ep;
		isSmaller = isSmaller & cr;
		return ODVector3::zeros() != isSmaller;
	}

	bool Plane2::contains(Plane2& other)
	{
		return intersects(other);
		
	}

	bool Plane2::disjoint(Plane2& other)
	{
		return !intersects(other);
	}

	void Plane2::getABD(rl& a, rl& b, rl& d)
	{
		d = getDot();
		a = normal[0];
		b = normal[1];
	}

	

}