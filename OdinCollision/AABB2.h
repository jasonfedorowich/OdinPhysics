#pragma once
#include "OdinCollision.h"

namespace OdinCollision {

	struct AABB2 {

		ODVector2 extents, center;

		AABB2() {};
		AABB2(ODVector2& extents, ODVector2& center) { this->extents = extents; this->center = center; }
		AABB2(ODVector2&& extents, ODVector2&& center) { this->extents = extents; this->center = center; }
		AABB2(std::vector<ODVector2>& points);
		AABB2(std::vector<ODVector2>&& points);
		AABB2(const AABB2& aabb) { *this = aabb; }

		AABB2& operator=(const AABB2& aabb);

		bool intersects(AABB2& other);
		bool contains(AABB2& other);
		bool disjoint(AABB2& other);


		AABB2 merge(AABB2& other);
		void makeUnion(AABB2& other);

		AABB2 merge(ODVector2& p);
		void makeUnion(ODVector2& p);

		AABB2 merge(ODVector2&& p);
		void makeUnion(ODVector2&& p);



		ODVector2 minimum();
		ODVector2 maximum();

		static AABB2 make(ODVector2& mini, ODVector2& maxi);

	};
}
