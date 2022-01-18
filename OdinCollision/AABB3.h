#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	struct AABB3 {
		
		ODVector3 extents, center;
		AABB3() {};
		AABB3(ODVector3& extents, ODVector3& center) { this->extents = extents; this->center = center; }
		AABB3(ODVector3&& extents, ODVector3&& center) { this->extents = extents; this->center = center; }
		AABB3(std::vector<ODVector3>& points);
		AABB3(std::vector<ODVector3>&& points);
		AABB3(const AABB3& aabb) { *this = aabb; }

		AABB3& operator=(const AABB3& aabb);

		bool intersects(AABB3& other);
		bool contains(AABB3& other);
		bool disjoint(AABB3& other);


		AABB3 merge(AABB3& other);
		void makeUnion(AABB3& other);

		AABB3 merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		AABB3 merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);

		

		ODVector3 minimum();
		ODVector3 maximum();

		static AABB3 make(ODVector3& mini, ODVector3& maxi);
	
	


	};

	


	
}
