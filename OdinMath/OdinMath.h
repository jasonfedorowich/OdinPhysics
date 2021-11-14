#pragma once
#include <assert.h>
#include <stdexcept>
#include <vector>
#include <deque>
#include <map>

#include "MathCommon.h"

#include "RungeKutta.h"
#include "GaussianQuadratre.h"
#include "TrapezoidIntegration.h"



#include "DXVector4.h"
#include "DXVector3.h"
#include "DXVector2.h"
#include "DXMatrix4.h"
#include "DXMatrix3.h"
#include "DXMatrix2.h"
#include "DXQuat.h"

#define INTRINSICS
#ifdef INTRINSICS
#include "VectorIntrin.h"
#endif // INTRINSICS

#include "Vect.h"
#include "Matrix.h"
#include "OVector4.h"
#include "OMatrix4.h"

#include "VectorIntrin.h"

#include "MatrixFunctions.h"

//todo move the directx stuff into a precompiled directive

/*ODVector must have a index overloaded operator like operator()(int idx) */
/*ODVector must have a real distance(ODVector) function */
/*ODVector must have a operator/=(rl c)*/

/*ODMatrix must have ::identity*/
/*ODMatrix must have void outerProduct(M&, V&, V&)*/

namespace OdinMath {
#if 1
	using Vector4 = DXVector4;
	using Matrix4 = DXMatrix4;
	using Vector3 = DXVector3;
	using Vector2 = DXVector2;
	using Matrix3 = DXMatrix3;
	using Matrix2 = DXMatrix2;

#elif 0
	using Vector4 = DXVector4;
	using Matrix4 = DXMatrix4;
	using Vector3 = DXVector3;
	using Vector2 = DXVector2;
	using Matrix3 = DXMatrix3;
	using Matrix2 = DXMatrix2;



#endif


}


#if 1
typedef float rl;
using ODVector = OdinMath::Vector4;


#endif

#include "QRDecomp.h"
#include "Eigen.h"
#include "LUDecomp.h"
#include "BSpline.h"