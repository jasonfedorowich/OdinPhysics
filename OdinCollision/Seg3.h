#pragma once
#include "OdinCollision.h"
namespace OdinCollision {
	struct Seg3 {
		ODVector3 start, end;

		Seg3() {};
		Seg3(const Seg3& ray) { *this = ray; }
		Seg3(ODVector3& p1, ODVector3& q1, bool direction = false);
		Seg3(ODVector3&& p1, ODVector3&& q1, bool direction = false);
		//computes the start and end val such that end > start;
		Seg3(std::vector<ODVector3>& points);
		Seg3(std::vector<ODVector3>&& points);
		~Seg3() {};

		Seg3& operator=(const Seg3& s);

		bool intersects(Seg3& other);
		bool contains(Seg3& other);
		bool disjoint(Seg3& other);

		
		Seg3 merge(Seg3& other);
		void makeUnion(Seg3& other);

		Seg3 merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		Seg3 merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);


		//invert the direction of the segment
		void invert() { OdinMath::Math<ODVector3>::odSwap(end, start); }

		/// <summary>
		/// Uses equation of line L = P1 + t*D1 and computes the closest points of both segments base algo from book "real time collision"
		/// </summary>
		/// <param name="other"> Other Segment</param>
		/// <param name="s"> of first segment</param>
		/// <param name="t"> of second segment</param>
		/// <param name="p1"> of first seg</param>
		/// <param name="p2"> of second seg</param>
		/// <returns></returns>
		rl closestPoints(Seg3& other, rl& s, rl& t, ODVector3& p1, ODVector3& p2);

		ODVector3 direction() { return end - start; }




	};
}
