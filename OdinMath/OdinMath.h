#pragma once
#include <assert.h>
#include <stdexcept>

#include "RungeKutta.h"
#include "GaussianQuadratre.h"
#include "TrapezoidIntegration.h"
#include "DXVector4.h"
#include "DXMatrix4.h"
#include "Vect.h"
#include "Matrix.h"
#include "AdjugateMatrix.h"

namespace OdinMath {
#if 1
	using Vector4 = DXVector4;
	using Matrix4 = DXMatrix4;
#endif
}