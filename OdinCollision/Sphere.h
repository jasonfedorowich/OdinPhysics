#pragma once
#include "OdinCollision.h"
namespace OdinCollision {


	struct BoundingSphere {
		ODVector center;
		rl radius;

		BoundingSphere(std::vector<ODVector>& points);
		BoundingSphere(std::vector<ODVector>&& points);
		BoundingSphere(const BoundingSphere& s);

		BoundingSphere() { radius = (rl)0.0; };
		BoundingSphere(ODVector& center, rl radius) { this->center = center; this->radius = radius; }

		BoundingSphere& operator=(const BoundingSphere& s);

		bool overlaps(BoundingSphere& sphere);
		BoundingSphere merge(BoundingSphere& sphere);
		void makeUnion(BoundingSphere& sphere);

		rl seperation(BoundingSphere& s);

	};
}