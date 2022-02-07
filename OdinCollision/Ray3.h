#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	//uses equation P = P1 + mu * d
	struct Ray3 {
	
		ODVector3 d, p;

		Ray3() {};
		Ray3(const Ray3& ray) { *this = ray; }
		Ray3(ODVector3& p, ODVector3& d) { this->d = d; this->p = p; }
		Ray3(ODVector3&& p, ODVector3&& d) { this->d = d; this->p = p; }
		//computes the start and end val such that end > start;
		Ray3(std::vector<ODVector3>& points);
		Ray3(std::vector<ODVector3>&& points);
		~Ray3() {};

		Ray3& operator=(const Ray3& s);

		bool intersects(Ray3& other);
		bool contains(Ray3& other);
		bool disjoint(Ray3& other);


		Ray3 merge(Ray3& other);
		void makeUnion(Ray3& other);

		Ray3 merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		Ray3 merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);


		

		/// <summary>
		/// Uses equation of line L = P1 + t*D1 and computes the closest points of both segments base algo from book "real time collision"
		/// </summary>
		/// <param name="other"> Other Segment</param>
		/// <param name="s"> of first segment</param>
		/// <param name="t"> of second segment</param>
		/// <param name="p1"> of first seg</param>
		/// <param name="p2"> of second seg</param>
		/// <returns></returns>
		rl closestPoints(Ray3& other, rl& s, rl& t, ODVector3& p1, ODVector3& p2);



	};


}