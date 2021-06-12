#pragma once
#include "OdinMath.h"

namespace OdinMath {
	template<typename real>
	inline void computeProperties(std::vector<Vector4>& points, int tmax, std::vector<int>& indices, real& mass, Vector4& centerOfMass, Matrix4& inertia, bool bodyCoords=true);
#include "MassProperties.inl"
}
