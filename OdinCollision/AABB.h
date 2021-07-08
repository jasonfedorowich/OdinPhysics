#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	template<int N>
	struct AABB {
		
		ODVector mini;
		ODVector maxi;
		AABB() {};
		AABB(ODVector& mini, ODVector& maxi) { this->maxi = maxi; this->mini = mini; }
		AABB(std::vector<ODVector>& points);
		AABB(std::vector<ODVector>&& points);
		AABB(const AABB& aabb) { *this = aabb; }

		bool overlaps(AABB& other);

		AABB merge(AABB& other);
		void makeUnion(AABB& other);

		AABB& operator=(const AABB& aabb);


	};

	

	typedef AABB<3> AABB3;
	typedef AABB<2> AABB2;

#include "AABB.inl"

	


}
