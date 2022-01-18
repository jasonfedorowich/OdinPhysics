#pragma once
#include "OdinCollision.h"

namespace OdinCollision {

	struct OBB {
		ODQuat orientation;
		ODVector3 extents;
		ODVector3 center;
	};
}