#pragma once
#include "OMatrix2.h"

template<typename real>
inline void storeMatrix2(const OMatrix2<real>& src, OMatrix2<real>& dst) {
	dst(0, 0) = src(0, 0);
	dst(0, 1) = src(0, 1);

	dst(1, 0) = src(1, 0);
	dst(1, 1) = src(1, 1);
}

template<typename real>
inline void multMatrix2(OMatrix2<real>& R, OMatrix2<real>& A, OMatrix2<real>& B) {
	R(0, 0) = A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0);
	R(0, 1) = A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1);

	R(1, 0) = A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0);
	R(1, 1) = A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1);


}
template<typename real>
inline void matrixVector2(OVector2<real>& R, OMatrix2<real>& mat, OVector2<real>& vect) {
	R[0] = mat(0, 0) * vect[0] + mat(0, 1) * vect[1];
	R[1] = mat(1, 0) * vect[0] + mat(1, 1) * vect[1];
}

template<typename real>
inline void matrixScale2(OMatrix2<real>& R, OMatrix2<real>& A, real scale) {
	R(0, 0) = A(0, 0) * scale;
	R(0, 1) = A(0, 1) * scale;

	R(1, 0) = A(1, 0) * scale;
	R(1, 1) = A(1, 1) * scale;
}

template<typename real>
inline void addMatrix2(OMatrix2<real>& R, OMatrix2<real>& A, OMatrix2<real>& B) {
	R(0, 0) = A(0, 0) + B(0, 0);
	R(0, 1) = A(0, 1) + B(0, 1);

	R(1, 0) = A(1, 0) + B(1, 0);
	R(1, 1) = A(1, 1) + B(1, 1);
}

template<typename real>
inline void subMatrix2(OMatrix2<real>& R, OMatrix2<real>& A, OMatrix2<real>& B) {
	R(0, 0) = A(0, 0) - B(0, 0);
	R(0, 1) = A(0, 1) - B(0, 1);

	R(1, 0) = A(1, 0) - B(1, 0);
	R(1, 1) = A(1, 1) - B(1, 1);
}

template<typename real>
inline bool matrixEquals2(OMatrix2<real>& A, OMatrix2<real>& B) {
	return (A(0, 0) == B(0, 0) &&
		A(0, 1) == B(0, 1) &&
		A(1, 0) == B(1, 0) &&
		A(1, 1) == B(1, 1));
}

template<typename real>
inline bool invertMat2(real mat[][2], real dst[][2], real eps, real* deter) {


	real det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];



	if (Math<real>::odAbs(det) > eps)
	{
		real invDet = ((real)1) / det;
		//swap in the case of dst == mat
		Math<real>::odSwap(&mat[0][0], &mat[1][1]);
		dst[0][0] = mat[0][0] * invDet;
		dst[1][1] = mat[1][1] * invDet;
		dst[0][1] = -mat[0][1] * invDet;
		dst[1][0] = -mat[1][0] * invDet;

		if (*deter != nullptr) {
			*deter = det;
		}
		return true;


	}

	return false;

}
template<typename real>
inline void matTranspose2(real in[][2], real out[][2]) {
	real tmp[][2];

	//copy to tmp for the case of in == out store in tmp
	tmp[0][0] = in[0][0];
	tmp[0][1] = in[1][0];

	tmp[1][0] = in[0][1];
	tmp[1][1] = in[1][1];

	//copy back

	out[0][0] = tmp[0][0];
	out[0][1] = tmp[1][0];

	out[1][0] = tmp[0][1];
	out[1][1] = tmp[1][1];


}

template<typename real>
inline real matDeterminant2(real A[][2]) {
	return A[0][0] * A[1][1] - A[0][1] * A[1][0];
}

template<typename real>
inline void matrixMultTrans2(OMatrix2<real>& A, OMatrix2<real>& B, OMatrix2<real>& C) {

	C(0, 0) = A(0, 0) * B(0, 0) + A(1, 0) * B(1, 0);
	C(0, 1) = A(0, 0) * B(0, 1) + A(1, 0) * B(1, 1);

	C(1, 0) = A(0, 1) * B(0, 0) + A(1, 1) * B(1, 0);
	C(1, 1) = A(0, 1) * B(0, 1) + A(1, 1) * B(1, 1);



}
