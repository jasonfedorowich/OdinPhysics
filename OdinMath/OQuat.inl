#pragma once
#include "OQuat.h"

template<typename real, int N>
inline void quatRotMatrix(Matrix<N, real>& m, OQuat<real>& q) {
	if (m(2, 2) <= (real)0.0) {
		real oneMinusm22 = (real)1.0 - m(2, 2);
		real m01m10 = m(0, 1) + m(1, 0);
		if ((m(1, 1) - m(0, 0)) <= (real)0.0) {
			real t = oneMinusm22 + m(0, 0) - m(1, 1);
			real invT = (real)0.5 / Math<real>::odSqrt(t);
			q[0] = t * invT;
			q[1] = m01m10 * invT;
			q[2] = (m(2, 0) + m(0, 2)) * invT;
			q[3] = (m(1, 2) - m(2, 1)) * invT;


		}
		else {

			real t = oneMinusm22 - m(0, 0) + m(1, 1);
			real invT = (real)0.5 / Math<real>::odSqrt(t);
			q[0] = m01m10 * invT;
			q[1] = t * invT;
			q[2] = (m(1, 2) + m(2, 1)) * invT;
			q[3] = (m(2, 0) - m(0, 2)) * invT;

		}
		

	}
	else {
		real onePlusm22 = (real)1.0 + m(2, 2);
		real m01m10 = m(0, 1) - m(1, 0);
		if ((m(0, 0) + m(1, 1)) <= (real)0.0) {
			real t = onePlusm22 - m(0, 0) - m(1, 1);
			real invT = (real)0.5 / Math<real>::odSqrt(t);
			q[0] = (m(2, 0) + m(0, 2)) * invT;
			q[1] = (m(1, 2) + m(2, 1)) * invT;
			q[2] = t * invT;
			q[3] = m01m10 * invT;
		}
		else {
			real t = onePlusm22 + m(0, 0) + m(1, 1);
			real invT = (real)0.5 / Math<real>::odSqrt(t);
			q[0] = (m(1, 2) - m(2, 1)) * invT;
			q[1] = (m(2, 0) - m(0, 2)) * invT;
			q[2] = m01m10 * invT;
			q[3] = t * invT;

		}
	}


}
template<typename real, int N>
inline void rotMatrixQuat(OQuat<real>& q, Matrix<N, real>& M) {
	real xx = (real)2.0 * q[0] * q[0];
	real yy = (real)2.0 * q[1] * q[1];
	real zz = (real)2.0 * q[2] * q[2];
	real xy = (real)2.0 * q[0] * q[1];
	real xz = (real)2.0 * q[0] * q[2];
	real xw = (real)2.0 * q[0] * q[3];
	real yz = (real)2.0 * q[1] * q[2];
	real yw = (real)2.0 * q[1] * q[3];
	real zw = (real)2.0 * q[2] * q[3];

	M(0, 0) = (real)1.0 - yy - zz;
	M(0, 1) = xy + zw;
	M(0, 2) = xz - yw;

	M(1, 0) = xy - zw;
	M(1, 1) = (real)1.0 - xx - zz;
	M(1, 2) = yz + xw;
	
	M(2, 0) = xz + yw;
	M(2, 1) = yz - xw;
	M(2, 2) = (real)1.0 - xx - yy;



}

