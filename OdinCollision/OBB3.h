#pragma once
#include "OdinCollision.h"

namespace OdinCollision {

	struct OBB3 {
		ODQuat orientation;
		ODVector3 extents;
		ODVector3 center;

		OBB3() {};
		OBB3(ODVector3& extents, ODVector3& center, ODQuat& orientation) { this->extents = extents; this->center = center; this->orientation = orientation; }
		OBB3(ODVector3&& extents, ODVector3&& center, ODQuat&& orientation) { this->extents = extents; this->center = center; this->orientation = orientation; }
		OBB3(ODVector3& extents, ODVector3& center, ODMatrix3& orientation) { this->extents = extents; this->center = center; this->orientation = ODQuat(orientation); }
		OBB3(ODVector3&& extents, ODVector3&& center, ODMatrix3&& orientation) : OBB3(extents, center, orientation) {}
		OBB3(std::vector<ODVector3>& points);
		OBB3(std::vector<ODVector3>&& points);
		OBB3(const OBB3& aabb) { *this = aabb; }

		OBB3& operator=(const OBB3& aabb);

		bool intersects(OBB3& other);
		bool contains(OBB3& other);
		bool disjoint(OBB3& other);

		bool contains(ODVector3& pt);
		bool contains(ODVector3&& pt);
		bool contains(ODVector3& pt, ODMatrix3& rot);
		bool contains(ODVector3&& pt, ODMatrix3& rot);
	


		OBB3 merge(OBB3& other);
		void makeUnion(OBB3& other);

		OBB3 merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		OBB3 merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);

		void getPoints(ODVector3 pts[8]);
		void getPointsBodySpace(ODVector3 pts[8]);

		static void make(std::vector<ODVector3>& points, OBB3& obb);
		static void make(OBB3& a, OBB3& b, OBB3& out);


	};
}