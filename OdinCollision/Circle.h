#pragma once
#include "OdinCollision.h"

namespace OdinCollision {


	struct BoundingCircle {
		ODVector center;
		rl radius;

		BoundingCircle(rl radius, ODVector& center) { this->radius = radius;  this->center = center; }
		BoundingCircle(rl radius, ODVector&& center) { this->radius = radius;  this->center = center; }
		BoundingCircle() { radius = (rl)0.0; }
		BoundingCircle(std::vector<ODVector>& points);
		BoundingCircle(std::vector<ODVector>&& points);
		BoundingCircle(const BoundingCircle& c);



	};
}