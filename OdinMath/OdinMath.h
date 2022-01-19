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
#include "MatrixIntrin.h"
#include "QuatIntrin.h"
#endif // INTRINSICS

#include "Vect.h"
#include "Matrix.h"
#include "OVector4.h"
#include "OMatrix4.h"
#include "OVector3.h"
#include "OMatrix3.h"
#include "OVector2.h"
#include "VectorIntrin.h"
#include "OQuat.h"

#include "MatrixFunctions.h"

//todo move the directx stuff into a precompiled directive

/*ODVector must have a index overloaded operator like operator()(int idx) */
/*ODVector must have a real distance(ODVector) function */
/*ODVector must have a operator/=(rl c)*/

/*ODMatrix must have ::identity*/
/*ODMatrix must have void outerProduct(M&, V&, V&)*/

namespace OdinMath {
#if 1
	using Vector4 = OVector4<float>;
	using Matrix4 = OMatrix4<float>;
	using Vector3 = OVector3<float>;
	//using Vector2 = OVector2<float>;
	using Matrix3 = OMatrix3<float>;
	//using Matrix2 = OMa;
	using Quat = OQuat<float>;
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
using ODVector4 = OdinMath::Vector4;
using ODVector3 = OdinMath::Vector3;
using ODQuat = OdinMath::Quat;
using ODMatrix4 = OdinMath::Matrix4;
using ODMatrix3 = OdinMath::Matrix3;

#endif

#include "QRDecomp.h"
#include "Eigen.h"
#include "LUDecomp.h"
#include "BSpline.h"