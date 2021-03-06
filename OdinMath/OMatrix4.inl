#pragma once
#include "OMatrix4.h"
template<typename real>
inline void storeMatrix4(const OMatrix4<real>& src, OMatrix4<real>& dest) {
	dest(0, 0) = src(0, 0);
	dest(0, 1) = src(0, 1);
	dest(0, 2) = src(0, 2);
	dest(0, 3) = src(0, 3);

	dest(1, 0) = src(1, 0);
	dest(1, 1) = src(1, 1);
	dest(1, 2) = src(1, 2);
	dest(1, 3) = src(1, 3);

	dest(2, 0) = src(2, 0);
	dest(2, 1) = src(2, 1);
	dest(2, 2) = src(2, 2);
	dest(2, 3) = src(2, 3);

	dest(3, 0) = src(3, 0);
	dest(3, 1) = src(3, 1);
	dest(3, 2) = src(3, 2);
	dest(3, 3) = src(3, 3);
}
template<typename real>
inline void addMatrix4(OMatrix4<real>& R, OMatrix4<real>& A, OMatrix4<real>& B) {
	R(0, 0) = A(0, 0) + B(0, 0);
	R(0, 1) = A(0, 1) + B(0, 1);
	R(0, 2) = A(0, 2) + B(0, 2);
	R(0, 3) = A(0, 3) + B(0, 3);

	R(1, 0) = A(1, 0) + B(1, 0);
	R(1, 1) = A(1, 1) + B(1, 1);
	R(1, 2) = A(1, 2) + B(1, 2);
	R(1, 3) = A(1, 3) + B(1, 3);

	R(2, 0) = A(2, 0) + B(2, 0);
	R(2, 1) = A(2, 1) + B(2, 1);
	R(2, 2) = A(2, 2) + B(2, 2);
	R(2, 3) = A(2, 3) + B(2, 3);


	R(3, 0) = A(3, 0) + B(3, 0);
	R(3, 1) = A(3, 1) + B(3, 1);
	R(3, 2) = A(3, 2) + B(3, 2);
	R(3, 3) = A(3, 3) + B(3, 3);
}

template<typename real>
inline void subMatrix4(OMatrix4<real>& R, OMatrix4<real>& A, OMatrix4<real>& B) {
    R(0, 0) = A(0, 0) - B(0, 0);
    R(0, 1) = A(0, 1) - B(0, 1);
    R(0, 2) = A(0, 2) - B(0, 2);
    R(0, 3) = A(0, 3) - B(0, 3);

    R(1, 0) = A(1, 0) - B(1, 0);
    R(1, 1) = A(1, 1) - B(1, 1);
    R(1, 2) = A(1, 2) - B(1, 2);
    R(1, 3) = A(1, 3) - B(1, 3);

    R(2, 0) = A(2, 0) - B(2, 0);
    R(2, 1) = A(2, 1) - B(2, 1);
    R(2, 2) = A(2, 2) - B(2, 2);
    R(2, 3) = A(2, 3) - B(2, 3);


    R(3, 0) = A(3, 0) - B(3, 0);
    R(3, 1) = A(3, 1) - B(3, 1);
    R(3, 2) = A(3, 2) - B(3, 2);
    R(3, 3) = A(3, 3) - B(3, 3);
}

template<typename real>
inline void multMatrix4(OMatrix4<real>& R, OMatrix4<real>& A, OMatrix4<real>& B) {
	R(0, 0) = A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0) + A(0, 3) * B(3, 0);
	R(0, 1) = A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1) + A(0, 3) * B(3, 1);
	R(0, 2) = A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2) + A(0, 3) * B(3, 2);
	R(0, 3) = A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3) * B(3, 3);

	R(1, 0) = A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0) + A(1, 3) * B(3, 0);
	R(1, 1) = A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1) + A(1, 3) * B(3, 1);
	R(1, 2) = A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2) + A(1, 3) * B(3, 2);
	R(1, 3) = A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3) * B(3, 3);

	R(2, 0) = A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0) + A(2, 3) * B(3, 0);
	R(2, 1) = A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1) + A(2, 3) * B(3, 1);
	R(2, 2) = A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2) + A(2, 3) * B(3, 2);
	R(2, 3) = A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3) * B(3, 3);

	R(3, 0) = A(3, 0) * B(0, 0) + A(3, 1) * B(1, 0) + A(3, 2) * B(2, 0) + A(3, 3) * B(3, 0);
	R(3, 1) = A(3, 0) * B(0, 1) + A(3, 1) * B(1, 1) + A(3, 2) * B(2, 1) + A(3, 3) * B(3, 1);
	R(3, 2) = A(3, 0) * B(0, 2) + A(3, 1) * B(1, 2) + A(3, 2) * B(2, 2) + A(3, 3) * B(3, 2);
	R(3, 3) = A(3, 0) * B(0, 3) + A(3, 1) * B(1, 3) + A(3, 2) * B(2, 3) + A(3, 3) * B(3, 3);


}

template<typename real>
inline void matrixVector4(OVector4<real>& result, OMatrix4<real>& mat, OVector4<real>& vect) {
    result[0] = mat(0, 0) * vect[0] + mat(0, 1) * vect[1] + mat(0, 2) * vect[2] + mat(0, 3) * vect[3];
    result[1] = mat(1, 0) * vect[0] + mat(1, 1) * vect[1] + mat(1, 2) * vect[2] + mat(1, 3) * vect[3];
    result[2] = mat(2, 0) * vect[0] + mat(2, 1) * vect[1] + mat(2, 2) * vect[2] + mat(2, 3) * vect[3];
    result[3] = mat(3, 0) * vect[0] + mat(3, 1) * vect[1] + mat(3, 2) * vect[2] + mat(3, 3) * vect[3];
}

template<typename real>
inline bool invertMat4(real mat[][4], real dst[][4], real eps, real* deter) {
    real tmp[12]; /* temp array for pairs */
    real src[4][4]; /* array of transpose source matrix */
    real det; /* determinant */
    /* transpose matrix */
    for (int i = 0; i < 4; i++) {
        src[i][0] = mat[0][i];
        src[i][1] = mat[1][i];
        src[i][2] = mat[2][i];
        src[i][3] = mat[3][i];


    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[2][2] * src[3][3];
    tmp[1] = src[2][3] * src[3][2];
    tmp[2] = src[2][1] * src[3][3];
    tmp[3] = src[2][3] * src[3][1];
    tmp[4] = src[2][1] * src[3][2];
    tmp[5] = src[2][2] * src[3][1];
    tmp[6] = src[2][0] * src[3][3];
    tmp[7] = src[2][3] * src[3][0];
    tmp[8] = src[2][0] * src[3][2];
    tmp[9] = src[2][2] * src[3][0];
    tmp[10] = src[2][0] * src[3][1];
    tmp[11] = src[2][1] * src[3][0];
    /* calculate first 8 elements (cofactors) */
    dst[0][0] = tmp[0] * src[1][1] + tmp[3] * src[1][2] + tmp[4] * src[1][3];
    dst[0][0] -= tmp[1] * src[1][1] + tmp[2] * src[1][2] + tmp[5] * src[1][3];
    dst[0][1] = tmp[1] * src[1][0] + tmp[6] * src[1][2] + tmp[9] * src[1][3];
    dst[0][1] -= tmp[0] * src[1][0] + tmp[7] * src[1][2] + tmp[8] * src[1][3];
    dst[0][2] = tmp[2] * src[1][0] + tmp[7] * src[1][1] + tmp[10] * src[1][3];
    dst[0][2] -= tmp[3] * src[1][0] + tmp[6] * src[1][1] + tmp[11] * src[1][3];
    dst[0][3] = tmp[5] * src[1][0] + tmp[8] * src[1][1] + tmp[11] * src[1][2];
    dst[0][3] -= tmp[4] * src[1][0] + tmp[9] * src[1][1] + tmp[10] * src[1][2];
    dst[1][0] = tmp[1] * src[0][1] + tmp[2] * src[0][2] + tmp[5] * src[0][3];
    dst[1][0] -= tmp[0] * src[0][1] + tmp[3] * src[0][2] + tmp[4] * src[0][3];
    dst[1][1] = tmp[0] * src[0][0] + tmp[7] * src[0][2] + tmp[8] * src[0][3];
    dst[1][1] -= tmp[1] * src[0][0] + tmp[6] * src[0][2] + tmp[9] * src[0][3];
    dst[1][2] = tmp[3] * src[0][0] + tmp[6] * src[0][1] + tmp[11] * src[0][3];
    dst[1][2] -= tmp[2] * src[0][0] + tmp[7] * src[0][1] + tmp[10] * src[0][3];
    dst[1][3] = tmp[4] * src[0][0] + tmp[9] * src[0][1] + tmp[10] * src[0][2];
    dst[1][3] -= tmp[5] * src[0][0] + tmp[8] * src[0][1] + tmp[11] * src[0][2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[0][2] * src[1][3];
    tmp[1] = src[0][3] * src[1][2];
    tmp[2] = src[0][1] * src[1][3];
    tmp[3] = src[0][3] * src[1][1];
    tmp[4] = src[0][1] * src[1][2];
    tmp[5] = src[0][2] * src[1][1];

    tmp[6] = src[0][0] * src[1][3];
    tmp[7] = src[0][3] * src[1][0];
    tmp[8] = src[0][0] * src[1][2];
    tmp[9] = src[0][2] * src[1][0];
    tmp[10] = src[0][0] * src[1][1];
    tmp[11] = src[0][1] * src[1][0];
    /* calculate second 8 elements (cofactors) */
    dst[2][0] = tmp[0] * src[3][1] + tmp[3] * src[3][2] + tmp[4] * src[3][3];
    dst[2][0] -= tmp[1] * src[3][1] + tmp[2] * src[3][2] + tmp[5] * src[3][3];
    dst[2][1] = tmp[1] * src[3][0] + tmp[6] * src[3][2] + tmp[9] * src[3][3];
    dst[2][1] -= tmp[0] * src[3][0] + tmp[7] * src[3][2] + tmp[8] * src[3][3];
    dst[2][2] = tmp[2] * src[3][0] + tmp[7] * src[3][1] + tmp[10] * src[3][3];
    dst[2][2] -= tmp[3] * src[3][0] + tmp[6] * src[3][1] + tmp[11] * src[3][3];
    dst[2][3] = tmp[5] * src[3][0] + tmp[8] * src[3][1] + tmp[11] * src[3][2];
    dst[2][3] -= tmp[4] * src[3][0] + tmp[9] * src[3][1] + tmp[10] * src[3][2];
    dst[3][0] = tmp[2] * src[2][2] + tmp[5] * src[2][3] + tmp[1] * src[2][1];
    dst[3][0] -= tmp[4] * src[2][3] + tmp[0] * src[2][1] + tmp[3] * src[2][2];
    dst[3][1] = tmp[8] * src[2][3] + tmp[0] * src[2][0] + tmp[7] * src[2][2];
    dst[3][1] -= tmp[6] * src[2][2] + tmp[9] * src[2][3] + tmp[1] * src[2][0];
    dst[3][2] = tmp[6] * src[2][1] + tmp[11] * src[2][3] + tmp[3] * src[2][0];
    dst[3][2] -= tmp[10] * src[2][3] + tmp[2] * src[2][0] + tmp[7] * src[2][1];
    dst[3][3] = tmp[10] * src[2][2] + tmp[4] * src[2][0] + tmp[9] * src[2][1];
    dst[3][3] -= tmp[8] * src[2][1] + tmp[11] * src[2][2] + tmp[5] * src[2][0];
    /* calculate determinant */
    det = src[0][0] * dst[0][0] + src[0][1] * dst[0][1] + src[0][2] * dst[0][2] + src[0][3] * dst[0][3];
    if (Math<real>::odAbs(det) <= eps)
        return false;
    
    /* calculate matrix inverse */
    det = (real)1.0 / det;

    for (int j = 0; j < 4; j++) {
        dst[j][0] *= det;
        dst[j][1] *= det;
        dst[j][2] *= det;
        dst[j][3] *= det;
    }

    if (deter != nullptr)
        *deter = det;

    return true;

}


template<typename real>
inline void matTranspose4(real mat[][4], real dst[][4]) {
    real tmp[][4];
   
    //copy to tmp
    tmp[0][0] = mat[0][0];
    tmp[0][1] = mat[1][0];
    tmp[0][2] = mat[2][0];
    tmp[0][3] = mat[3][0];

    tmp[1][0] = mat[0][1];
    tmp[1][1] = mat[1][1];
    tmp[1][2] = mat[2][1];
    tmp[1][3] = mat[3][1];

    tmp[2][0] = mat[0][2];
    tmp[2][1] = mat[1][2];
    tmp[2][2] = mat[2][2];
    tmp[2][3] = mat[3][2];

    tmp[3][0] = mat[0][3];
    tmp[3][1] = mat[1][3];
    tmp[3][2] = mat[2][3];
    tmp[3][3] = mat[3][3];

    //copy back

    dst[0][0] = tmp[0][0];
    dst[0][1] = tmp[1][0];
    dst[0][2] = tmp[2][0];
    dst[0][3] = tmp[3][0];

    dst[1][0] = tmp[0][1];
    dst[1][1] = tmp[1][1];
    dst[1][2] = tmp[2][1];
    dst[1][3] = tmp[3][1];

    dst[2][0] = tmp[0][2];
    dst[2][1] = tmp[1][2];
    dst[2][2] = tmp[2][2];
    dst[2][3] = tmp[3][2];

    dst[3][0] = tmp[0][3];
    dst[3][1] = tmp[1][3];
    dst[3][2] = tmp[2][3];
    dst[3][3] = tmp[3][3];


}

template<typename real>
inline real matDeterminant4(real mm[][4]) {
    real a0 = mm[0][0] * mm[1][1] - mm[0][1] * mm[1][0];
    real a1 = mm[0][0] * mm[1][2] - mm[0][2] * mm[1][0];
    real a2 = mm[0][0] * mm[1][3] - mm[0][3] * mm[1][0];
    real a3 = mm[0][1] * mm[1][2] - mm[0][2] * mm[1][1];

    real a4 = mm[0][1] * mm[1][3] - mm[0][3] * mm[1][1];
    real a5 = mm[0][2] * mm[1][3] - mm[0][3] * mm[1][2];
    real b0 = mm[2][0] * mm[3][1] - mm[2][1] * mm[3][0];
    real b1 = mm[2][0] * mm[3][2] - mm[2][2] * mm[3][0];

    real b5 = mm[2][2] * mm[3][3] - mm[2][3] * mm[3][2];
    real b4 = mm[2][1] * mm[3][3] - mm[2][3] * mm[3][1];
    real b3 = mm[2][1] * mm[3][2] - mm[2][2] * mm[3][1];
    real b2 = mm[2][0] * mm[3][3] - mm[2][3] * mm[3][0];



    real det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    return det;
}

template<typename real>
inline void matrixScale4(OMatrix4<real>& R, OMatrix4<real>& A, real scale) {
    R(0, 0) = A(0, 0) * scale;
    R(0, 1) = A(0, 1) * scale;
    R(0, 2) = A(0, 2) * scale;
    R(0, 3) = A(0, 3) * scale;

    R(1, 0) = A(1, 0) * scale;
    R(1, 1) = A(1, 1) * scale;
    R(1, 2) = A(1, 2) * scale;
    R(1, 3) = A(1, 3) * scale;

    R(2, 0) = A(2, 0) * scale;
    R(2, 1) = A(2, 1) * scale;
    R(2, 2) = A(2, 2) * scale;
    R(2, 3) = A(2, 3) * scale;

    R(3, 0) = A(3, 0) * scale;
    R(3, 1) = A(3, 1) * scale;
    R(3, 2) = A(3, 2) * scale;
    R(3, 3) = A(3, 3) * scale;
}

template<typename real>
inline bool matrixEquals4(OMatrix4<real>& A, OMatrix4<real>& B) {

    return (A(0, 0) == B(0, 0) &&
        A(0, 1) == B(0, 1) &&
        A(0, 2) == B(0, 2) &&
        A(0, 3) == B(0, 3) &&
        A(1, 0) == B(1, 0) &&
        A(1, 1) == B(1, 1) &&
        A(1, 2) == B(1, 2) &&
        A(1, 3) == B(1, 3) &&
        A(2, 0) == B(2, 0) &&
        A(2, 1) == B(2, 1) &&
        A(2, 2) == B(2, 2) &&
        A(2, 3) == B(2, 3) &&
        A(3, 0) == B(3, 0) &&
        A(3, 1) == B(3, 1) &&
        A(3, 2) == B(3, 2) &&
        A(3, 3) == B(3, 3));
}


template<typename real>
inline void matrixMultTrans4(OMatrix4<real>& A, OMatrix4<real>& B, OMatrix4<real>& C) {

    C(0, 0) = A(0, 0) * B(0, 0) + A(1, 0) * B(1, 0) + A(2, 0) * B(2, 0) + A(3, 0) * B(3, 0);
    C(0, 1) = A(0, 0) * B(0, 1) + A(1, 0) * B(1, 1) + A(2, 0) * B(2, 1) + A(3, 0) * B(3, 1);
    C(0, 2) = A(0, 0) * B(0, 2) + A(1, 0) * B(1, 2) + A(2, 0) * B(2, 2) + A(3, 0) * B(3, 2);
    C(0, 3) = A(0, 0) * B(0, 3) + A(1, 0) * B(1, 3) + A(2, 0) * B(2, 3) + A(3, 0) * B(3, 3);

    C(1, 0) = A(0, 1) * B(0, 0) + A(1, 1) * B(1, 0) + A(2, 1) * B(2, 0) + A(3, 1) * B(3, 0);
    C(1, 1) = A(0, 1) * B(0, 1) + A(1, 1) * B(1, 1) + A(2, 1) * B(2, 1) + A(3, 1) * B(3, 1);
    C(1, 2) = A(0, 1) * B(0, 2) + A(1, 1) * B(1, 2) + A(2, 1) * B(2, 2) + A(3, 1) * B(3, 2);
    C(1, 3) = A(0, 1) * B(0, 3) + A(1, 1) * B(1, 3) + A(2, 1) * B(2, 3) + A(3, 1) * B(3, 3);

    C(2, 0) = A(0, 2) * B(0, 0) + A(1, 2) * B(1, 0) + A(2, 2) * B(2, 0) + A(3, 2) * B(3, 0);
    C(2, 1) = A(0, 2) * B(0, 1) + A(1, 2) * B(1, 1) + A(2, 2) * B(2, 1) + A(3, 2) * B(3, 1);
    C(2, 2) = A(0, 2) * B(0, 2) + A(1, 2) * B(1, 2) + A(2, 2) * B(2, 2) + A(3, 2) * B(3, 2);
    C(2, 3) = A(0, 2) * B(0, 3) + A(1, 2) * B(1, 3) + A(2, 2) * B(2, 3) + A(3, 2) * B(3, 3);

    C(3, 0) = A(0, 3) * B(0, 0) + A(1, 3) * B(1, 0) + A(2, 3) * B(2, 0) + A(3, 3) * B(3, 0);
    C(3, 1) = A(0, 3) * B(0, 1) + A(1, 3) * B(1, 1) + A(2, 3) * B(2, 1) + A(3, 3) * B(3, 1);
    C(3, 2) = A(0, 3) * B(0, 2) + A(1, 3) * B(1, 2) + A(2, 3) * B(2, 2) + A(3, 3) * B(3, 2);
    C(3, 3) = A(0, 3) * B(0, 3) + A(1, 3) * B(1, 3) + A(2, 3) * B(2, 3) + A(3, 3) * B(3, 3);
}
