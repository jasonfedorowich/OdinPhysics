#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	struct Seg2 {
		ODVector2 start, end;
		Seg2() {};
		Seg2(ODVector2& a1, ODVector2& a2, bool direction = false);
		Seg2(ODVector2&& a1, ODVector2&& a2, bool direction = false);
		//computes the start and end val such that end > start;
		Seg2(std::vector<ODVector2>& points);
		Seg2(std::vector<ODVector2>&& points);
		~Seg2() {};

		Seg2& operator=(const Seg2& s);

		bool intersects(Seg2& other);
		bool contains(Seg2& other);
		bool disjoint(Seg2& other);


		Seg2 merge(Seg2& other);
		void makeUnion(Seg2& other);

		Seg2 merge(ODVector2& p);
		void makeUnion(ODVector2& p);

		Seg2 merge(ODVector2&& p);
		void makeUnion(ODVector2&& p);


		//invert the direction of the segment
		void invert() { OdinMath::Math<ODVector2>::odSwap(end, start); }

		//assume there is some intersection point even if mua and mua are not in [0, 1]
		bool intersectionPoint(Seg2& other, rl& mua, rl& mub, ODVector2& pt);

		ODVector2 direction() { return end - start; }
		rl slope() { 
			ODVector2 tmp = end - start;
			return (tmp[1] / tmp[0]);
		}

		rl xIntercept();
		rl yIntercept();
	};


}
