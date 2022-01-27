#pragma once
#include "OdinCollision.h"

namespace OdinCollision {


	struct BoundingCircle {
		ODVector2 center;
		rl radius;

		BoundingCircle(rl radius, ODVector2& center) { this->radius = radius;  this->center = center; }
		BoundingCircle(rl radius, ODVector2&& center) { this->radius = radius;  this->center = center; }
		BoundingCircle() { radius = (rl)0.0; }
		BoundingCircle(std::vector<ODVector2>& points);
		BoundingCircle(std::vector<ODVector2>&& points);
		BoundingCircle(const BoundingCircle& c) { *this = c; }

		

		BoundingCircle& operator=(const BoundingCircle& circle);

		bool intersects(BoundingCircle& other);
		bool contains(BoundingCircle& other);
		bool disjoint(BoundingCircle& other);


		BoundingCircle merge(BoundingCircle& other);
		void makeUnion(BoundingCircle& other);

		BoundingCircle merge(ODVector2& p);
		void makeUnion(ODVector2& p);

		BoundingCircle merge(ODVector2&& p);
		void makeUnion(ODVector2&& p);




	};
}