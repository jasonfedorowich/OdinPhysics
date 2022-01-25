#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	template<typename A, typename B>
	struct CollisionResult {
	
		A* colliderA;
		B* colliderB;

		bool insertsecting;
		bool contained;
		rl seperationDistance;
		rl overlap;
	
		


	};

}
