#pragma once
#include "OdinMath.h"
#include <intrin.h>
#include <zmmintrin.h>
#include <xmmintrin.h>

namespace OdinMath {
	void tquatfRotMatf(InMatrix4F& in, InVectf& out);
	void tquatfRotMatd(InMatrix4D& in, InVectd& out);
	void trotMatfQuatf(InVectf& q, InMatrix4F& out);
	void trotMatfQuatd(InVectd& q, InMatrix4D& out);
	void tquatfEulerf(InVectf& v, InVectf& q);
	void tquatfEulerd(InVectd& v, InVectd& q);

	template<typename real>
	void tquatfRotAxis(real angle, real* axis, real* result);

	template<typename real, int N>
	void tquatfRotMat(real M[][N], real* data);

	template<typename real, int N>
	void trotMatfQuat(real* data, real M[][N]);

	template<typename real>
	void tquatfEuler(real roll, real pitch, real yaw, real* data);

	template<typename real>
	void tEulerfQuat(real* data, real* rpy);


}