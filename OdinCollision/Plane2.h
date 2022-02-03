#pragma once
#include "OdinCollision.h"
namespace OdinCollision {


	struct Plane2 {

		ODVector2 normal, point;

		Plane2() {}
		Plane2(ODVector2& normal, ODVector2& point) { this->normal = normal; }
		Plane2(ODVector2&& normal, ODVector2&& point) { this->normal = normal; }
		

		Plane2(const Plane2& plane) { *this = plane; }
		~Plane2() {}


		Plane2& operator=(const Plane2& p);

		bool intersects(Plane2& other);
		bool contains(Plane2& other);
		bool disjoint(Plane2& other);


		void getABD(rl& a, rl& b, rl& d);


		rl getDot() { return normal.dot(point); }



	};

}