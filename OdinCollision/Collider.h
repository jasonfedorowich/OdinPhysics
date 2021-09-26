#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	enum Type {
		AABB, Sphere, OBB, Circle,
		None
	};
	struct Collider {

		Type type;
		Collider() {

			type = Type::None;
		}


	};

}
