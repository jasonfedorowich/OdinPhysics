#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	struct Plane3 {
		ODVector3 normal, point;

		Plane3() {}
		Plane3(ODVector3& normal, ODVector3& point) { this->normal = normal; }
		Plane3(ODVector3&& normal, ODVector3&& point) { this->normal = normal; }
		Plane3(ODVector3& p1, ODVector3& p2, ODVector3& p3);
		Plane3(ODVector3&& p1, ODVector3&& p2, ODVector3&& p3);

		Plane3(const Plane3& plane) { *this = plane; }
		~Plane3() {}


		Plane3& operator=(const Plane3& p);

		bool intersects(Plane3& other);
		bool contains(Plane3& other);
		bool disjoint(Plane3& other);


		Plane3 merge(Plane3& other);
		void makeUnion(Plane3& other);

		Plane3 merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		Plane3 merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);


		void getABCD(rl& a, rl& b, rl& c, rl& d);


		rl getDot() { return normal.dot(point); }
		static void pointsToPlane(Plane3& plane, ODVector3& p1, ODVector3& p2, ODVector3& p3);

	};


}