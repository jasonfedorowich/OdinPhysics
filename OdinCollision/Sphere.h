#pragma once
#include "OdinCollision.h"
#include <vector>
namespace OdinCollision {


	struct BoundingSphere {
		ODVector3 center;
		rl radius;

		BoundingSphere(std::vector<ODVector3>& points);
		BoundingSphere(std::vector<ODVector3>&& points);
		BoundingSphere(const BoundingSphere& s);

		BoundingSphere() { radius = (rl)0.0; };
		BoundingSphere(ODVector3& center, rl radius) { this->center = center; this->radius = radius; }
		BoundingSphere(ODVector3&& center, rl radius) { this->center = center; this->radius = radius; }
		BoundingSphere& operator=(const BoundingSphere& s);

		bool intersects(BoundingSphere& other);
		bool contains(BoundingSphere& other);
		bool disjoint(BoundingSphere& other);


		BoundingSphere merge(BoundingSphere& other);
		void makeUnion(BoundingSphere& other);

		BoundingSphere merge(ODVector3& p);
		void makeUnion(ODVector3& p);

		BoundingSphere merge(ODVector3&& p);
		void makeUnion(ODVector3&& p);


	};
}