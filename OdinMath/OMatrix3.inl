#pragma once
#include "OMatrix3.h"

template<typename real>
inline void storeMatrix3(const OMatrix3<real>& src, OMatrix3<real>& dst) {
	dst(0, 0) = src(0, 0);
	dst(0, 1) = src(0, 1);
	dst(0, 2) = src(0, 2);

	dst(1, 0) = src(1, 0);
	dst(1, 1) = src(1, 1);
	dst(1, 2) = src(1, 2);

	dst(2, 0) = src(2, 0);
	dst(2, 1) = src(2, 1);
	dst(2, 2) = src(2, 2);
}

template<typename real>
inline void multMatrix3(OMatrix3<real>& R, OMatrix3<real>& A, OMatrix3<real>& B) {
	R(0, 0) = A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0);
	R(0, 1) = A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1);
	R(0, 2) = A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2);

	R(1, 0) = A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0);
	R(1, 1) = A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1);
	R(1, 2) = A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2);

	R(2, 0) = A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0);
	R(2, 1) = A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1);
	R(2, 2) = A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2);

	
}

template<typename real>
inline void matrixVector3(OVector3<real>& result, OMatrix3<real>& mat, OVector3<real>& vect) {
	result[0] = mat(0, 0) * vect[0] + mat(0, 1) * vect[1] + mat(0, 2) * vect[2];
	result[1] = mat(1, 0) * vect[0] + mat(1, 1) * vect[1] + mat(1, 2) * vect[2];
	result[2] = mat(2, 0) * vect[0] + mat(2, 1) * vect[1] + mat(2, 2) * vect[2];


}
template<typename real>
inline void matrixScale3(OMatrix3<real>& R, OMatrix3<real>& A, real scale) {
	R(0, 0) = A(0, 0) * scale;
	R(0, 1) = A(0, 1) * scale;
	R(0, 2) = A(0, 2) * scale;

	R(1, 0) = A(1, 0) * scale;
	R(1, 1) = A(1, 1) * scale;
	R(1, 2) = A(1, 2) * scale;

	R(2, 0) = A(2, 0) * scale;
	R(2, 1) = A(2, 1) * scale;
	R(2, 2) = A(2, 2) * scale;

}

template<typename real>
inline void addMatrix3(OMatrix3<real>& R, OMatrix3<real>& A, OMatrix3<real>& B) {
	R(0, 0) = A(0, 0) + B(0, 0);
	R(0, 1) = A(0, 1) + B(0, 1);
	R(0, 2) = A(0, 2) + B(0, 2);

	R(1, 0) = A(1, 0) + B(1, 0);
	R(1, 1) = A(1, 1) + B(1, 1);
	R(1, 2) = A(1, 2) + B(1, 2);

	R(2, 0) = A(2, 0) + B(2, 0);
	R(2, 1) = A(2, 1) + B(2, 1);
	R(2, 2) = A(2, 2) + B(2, 2);

}

template<typename real>
inline void subMatrix3(OMatrix3<real>& R, OMatrix3<real>& A, OMatrix3<real>& B) {
	R(0, 0) = A(0, 0) - B(0, 0);
	R(0, 1) = A(0, 1) - B(0, 1);
	R(0, 2) = A(0, 2) - B(0, 2);

	R(1, 0) = A(1, 0) - B(1, 0);
	R(1, 1) = A(1, 1) - B(1, 1);
	R(1, 2) = A(1, 2) - B(1, 2);

	R(2, 0) = A(2, 0) - B(2, 0);
	R(2, 1) = A(2, 1) - B(2, 1);
	R(2, 2) = A(2, 2) - B(2, 2);

}


template<typename real>
inline bool matrixEquals3(OMatrix3<real>& A, OMatrix3<real>& B) {
	return (A(0, 0) == B(0, 0) &&
		A(0, 1) == B(0, 1) &&
		A(0, 2) == B(0, 2) &&
		A(1, 0) == B(1, 0) &&
		A(1, 1) == B(1, 1) &&
		A(1, 2) == B(1, 2) &&
		A(2, 0) == B(2, 0) &&
		A(2, 1) == B(2, 1) &&
		A(2, 2) == B(2, 2));
}


template<typename real>
inline bool invertMat3(real mat[][3], real dst[][3], real eps, real* deter) {

	real t1 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
	real t2 = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2];
	real t3 = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
	real t4 = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
	real t5 = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
	real t6 = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
	real t7 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
	real t8 = mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1];
	real t9 = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	real det = mat[0][0] * t1 + mat[0][1] * t4 + mat[0][2] * t7;

	

	if (Math<real>::odAbs(det) > eps)
	{
		real invDet = ((real)1) / det;
		dst[0][0] = t1 * invDet;
		dst[0][1] = t2 * invDet;
		dst[0][2] = t3 * invDet;
		dst[1][0] = t4 * invDet;
		dst[1][1] = t5 * invDet;
		dst[1][2] = t6 * invDet;
		dst[2][0] = t7 * invDet;
		dst[2][1] = t8 * invDet;
		dst[2][2] = t9 * invDet;

		if (*deter != nullptr) {
			*deter = det;
		}
		return true;

	
	}

	return false;

}

template<typename real>
inline void matTranspose3(real in[][3], real out[][3]) {
	real tmp[][3];

	//copy to tmp
	tmp[0][0] = in[0][0];
	tmp[0][1] = in[1][0];
	tmp[0][2] = in[2][0];

	tmp[1][0] = in[0][1];
	tmp[1][1] = in[1][1];
	tmp[1][2] = in[2][1];

	tmp[2][0] = in[0][2];
	tmp[2][1] = in[1][2];
	tmp[2][2] = in[2][2];

	//copy back

	out[0][0] = tmp[0][0];
	out[0][1] = tmp[1][0];
	out[0][2] = tmp[2][0];

	out[1][0] = tmp[0][1];
	out[1][1] = tmp[1][1];
	out[1][2] = tmp[2][1];

	out[2][0] = tmp[0][2];
	out[2][1] = tmp[1][2];
	out[2][2] = tmp[2][2];

}

template<typename real>
inline real matDeterminant3(real A[][3]) {
	real t1 = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]);
	real t2 = A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]);
	real t3 = A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);

	return t1 - t2 + t3;
}
template<typename real>
inline void matrixMultTrans3(OMatrix3<real>& A, OMatrix3<real>& B, OMatrix3<real>& C) {

	C(0, 0) = A(0, 0) * B(0, 0) + A(1, 0) * B(1, 0) + A(2, 0) * B(2, 0);
	C(0, 1) = A(0, 0) * B(0, 1) + A(1, 0) * B(1, 1) + A(2, 0) * B(2, 1);
	C(0, 2) = A(0, 0) * B(0, 2) + A(1, 0) * B(1, 2) + A(2, 0) * B(2, 2);

	C(1, 0) = A(0, 1) * B(0, 0) + A(1, 1) * B(1, 0) + A(2, 1) * B(2, 0);
	C(1, 1) = A(0, 1) * B(0, 1) + A(1, 1) * B(1, 1) + A(2, 1) * B(2, 1);
	C(1, 2) = A(0, 1) * B(0, 2) + A(1, 1) * B(1, 2) + A(2, 1) * B(2, 2);

	C(2, 0) = A(0, 2) * B(0, 0) + A(1, 2) * B(1, 0) + A(2, 2) * B(2, 0);
	C(2, 1) = A(0, 2) * B(0, 1) + A(1, 2) * B(1, 1) + A(2, 2) * B(2, 1);
	C(2, 2) = A(0, 2) * B(0, 2) + A(1, 2) * B(1, 2) + A(2, 2) * B(2, 2);

	
}
