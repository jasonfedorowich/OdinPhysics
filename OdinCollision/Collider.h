#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	enum Type {
		AABB2, AABB3, OBB2, OBB3, Circle, Sphere,
		None
	};
	struct Collider {

		Type type;
		Collider() {

			type = Type::None;
		}


	};

}
