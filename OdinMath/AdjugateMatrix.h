#pragma once
#include "OdinMath.h"
namespace OdinMath {



	template<typename real>
	inline void minor(Matrix<3, real>& A, int r, int c, Matrix<2, real>& M) {

		int mi = 0;
		int mj = 0;
		for (int i = 0; i < 3; i++) {
			if (r == i)
				continue;
			mj = 0;
			for (int j = 0; j < 3; j++) {
				if (c == j)
					continue;
				M(mi, mj) = A(i, j);
				mj++;
			}
			mi++;

		}


	}

	template<typename real>
	inline void minor(Matrix<4, real>& A, int r, int c, Matrix<3, real>& M) {

		int mi = 0;
		int mj = 0;
		for (int i = 0; i < 4; i++) {
			if (r == i)
				continue;
			mj = 0;
			for (int j = 0; j < 4; j++) {
				if (c == j)
					continue;
				M(mi, mj) = A(i, j);
				mj++;
			}
			mi++;

		}


	}

	template<typename real>
	inline real determinant(Matrix<2, real>& M) {
		return M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0);
	}

	template<typename real>
	inline real determinant(Matrix<1, real>& M) {
		return M(0, 0);
	}

	template<typename real>
	inline real determinant(Matrix<3, real>& M) {
		real det = (real)0.0;
		int sign = 1;

		for (int i = 0; i < 3; i++) {
			Matrix<2, real> mnr;
			minor(M, 0, i, mnr);
			det += ((sign)*M(0, i) * determinant(mnr));
			sign *= -1;
		}

		return det;

	}

	template<typename real>
	inline real determinant(Matrix<4, real>& M) {
		real det = (real)0.0;
		int sign = 1;

		for (int i = 0; i < 4; i++) {
			Matrix<3, real> mnr;
			minor(M, 0, i, mnr);
			det += ((sign)*M(0, i) * determinant(mnr));
			sign *= -1;
		}

		return det;

	}

	template<typename real>
	inline int adjugateInverse(Matrix<2, real>& A, Matrix<2, real>& I, real& det) {
		det = determinant(A);
		if (det == (real)0.0)
			return SINGULAR;

		I(0, 0) = A(1, 1);
		I(0, 1) = (real)-1.0 * A(0, 1);
		I(1, 0) = (real)-1.0 * A(1, 0);
		I(1, 1) = A(0, 0);
		return NON_SINGULAR;
	}


	template<typename real>
	inline int adjugateInverse(Matrix<3, real>& A, Matrix<3, real>& I, real& det) {
		det = determinant(A);
		if (det == (real)0.0)
			return SINGULAR;

		real dtr;
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {
				Matrix<2, real> mnr;
				minor(A, j, i, mnr);
				dtr = determinant(mnr);
				I(i, j) = (real)pow(-1.0, i + j) * dtr;
			}

		}

		I *= ((real)1.0 / det);
		return NON_SINGULAR;


	}

	template<typename real>
	inline int adjugateInverse(Matrix<4, real>& A, Matrix<4, real>& I, real& det) {
		det = determinant(A);
		if (det == (real)0.0)
			return SINGULAR;

		real dtr;
		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {
				Matrix<3, real> mnr;
				minor(A, j, i, mnr);
				dtr = determinant(mnr);
				I(i, j) = (real)pow(-1.0, i + j) * dtr;
			}

		}

		I *= ((real)1.0 / det);
		return NON_SINGULAR;


	}
}
