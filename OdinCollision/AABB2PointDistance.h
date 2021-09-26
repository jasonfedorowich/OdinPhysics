#pragma once
#include "OdinCollision.h"
namespace OdinCollision {
	
	rl distanceSqr(AABB<3>& a, ODVector& p, ODVector& cp);
	rl distanceSqr(AABB<3>& a, ODVector& p);

	rl distance(AABB<3>& a, ODVector& p, ODVector& cp);
	rl distance(AABB<3>& a, ODVector& p);

	void nearestPoint(AABB<3>& b, ODVector& p, ODVector& cp);

	rl distanceSqr(AABB<2>& a, ODVector& p, ODVector& cp);
	rl distanceSqr(AABB<2>& a, ODVector& p);

	rl distance(AABB<2>& a, ODVector& p, ODVector& cp);
	rl distance(AABB<2>& a, ODVector& p);

	void nearestPoint(AABB<2>& b, ODVector& p, ODVector& cp);

}
