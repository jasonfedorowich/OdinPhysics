#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	struct Ray2 {

		ODVector2 d, p;

		Ray2() {};
		Ray2(const Ray2& ray) { *this = ray; }
		Ray2(ODVector2& p, ODVector2& d) { this->d = d; this->p = p; }
		Ray2(ODVector2&& p, ODVector2&& d) { this->d = d; this->p = p; }
		//computes the start and end val such that end > start;
		Ray2(std::vector<ODVector2>& points);
		Ray2(std::vector<ODVector2>&& points);
		~Ray2() {};

		Ray2& operator=(const Ray2& s);

		bool intersects(Ray2& other);
		bool contains(Ray2& other);
		bool disjoint(Ray2& other);


		Ray2 merge(Ray2& other);
		void makeUnion(Ray2& other);

		Ray2 merge(ODVector2& p);
		void makeUnion(ODVector2& p);

		Ray2 merge(ODVector2&& p);
		void makeUnion(ODVector2&& p);




		/// <summary>
		/// Uses equation of line L = P1 + t*D1 and computes the closest points of both segments base algo from book "real time collision"
		/// </summary>
		/// <param name="other"> Other Segment</param>
		/// <param name="s"> of first segment</param>
		/// <param name="t"> of second segment</param>
		/// <param name="p1"> of first seg</param>
		/// <param name="p2"> of second seg</param>
		/// <returns></returns>
		bool intersectionPoint(Ray2& other, rl& s, rl& t, ODVector2& pt);


	};
}