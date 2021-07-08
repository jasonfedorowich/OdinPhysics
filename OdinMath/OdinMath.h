#pragma once
#include <assert.h>
#include <stdexcept>
#include "MathCommon.h"

#include "RungeKutta.h"
#include "GaussianQuadratre.h"
#include "TrapezoidIntegration.h"
#include "DXVector4.h"
#include "DXMatrix4.h"
#include "Vect.h"
#include "Matrix.h"
#include "AdjugateMatrix.h"
//todo move the directx stuff into a precompiled directive

/*ODVector must have a index overloaded operator like operator()(int idx) */
namespace OdinMath {
#if 1
	using Vector4 = DXVector4;
	using Matrix4 = DXMatrix4;


#endif


}

#if 1
typedef float rl;
using ODVector = OdinMath::Vector4;


#endif