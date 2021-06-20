#pragma once
#include <assert.h>
#include "RungeKutta.h"
#include "GaussianQuadratre.h"
#include "TrapezoidIntegration.h"
#include "DXVector4.h"
#include "DXMatrix4.h"

#include "Matrix.h"

namespace OdinMath {
#if 1
	using Vector4 = DXVector4;
	using Matrix4 = DXMatrix4;
#endif
}