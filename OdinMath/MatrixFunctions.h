#pragma once
#include "OdinMath.h"
namespace OdinMath {

	
	template<typename Matrix, typename real>
	void minor(int d, Matrix& A, Matrix& R, int n) {
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < n; j++) {
				R(i, j) = i == j ? (real)1.0 : (real)0.0;
			}

		}
		for (int i = d; i < n; i++) {
			for (int j = d; j < n; j++) {
				R(i, j) = A(i, j);
			}

		}
	}

	template<typename Matrix, typename real>
	void pivot(Matrix& P, Matrix& A, int d) {
		real t;
		for (int i = 0; i < d; i++) {
			int maxR = i;
			real maxV = A(i, i);
			for (int j = i; j < d; j++) {
				t = Math<real>::odAbs(A(j, i));
				if (maxV < t) {
					maxR = j;
					maxV = t;
				}
			}

			if (maxR != i) {
				P.swapRows(i, maxR);
			}
		}
	}

	template<typename Matrix, typename Vect, typename real>
	void backSub(Matrix& U, Vect& x, Vect& b, int d) {
		for (int i = 0; i < d; i++) {
			x[i] = (real)0.0;
		}

		for (int i = d - 1; i >= 0; i--) {
			real t = b[i];
			for (int j = i + 1; j < d; j++) {
				t -= (U(i, j) * x[j]);
			}
			if (U(i, i) == (real)0.0)
				throw std::exception("Matrix is singular");
			x[i] = t / U(i, i);
		}

	}

	template<typename Matrix, typename Vect, typename real>
	void tridiag(Matrix& H, std::vector<Matrix>& reflectors, int n) {
		int j;
		real alpha;
		real sumSq;
		real r;
		real r2;
		std::vector<Matrix> Q;

		int iterations = n - 2;
		for (int i = 0; i < iterations; i++) {

			sumSq = (real)0.0;
			for (j = i + 1; j < n; j++)
				sumSq += (H(j, i) * H(j, i));

			alpha = Math<real>::odSqrt(sumSq);
			alpha *= ((real)-1.0 * Math<real>::sign(H(i + 1, i)));

			r = Math<real>::odSqrt((real)0.5 * (alpha * alpha - H(i + 1, i) * alpha));
			Vect v;
			r2 = (real)2.0 * r;
			int ij = i + 1;
			for (j = 0; j < ij; j++)
				v[j] = (real)0.0;
			v[i + 1] = (H(i + 1, i) - alpha) / r2;

			for (j = i + 2; j < n; j++)
				v[j] = H(j, i) / r2;

			Matrix P;
			outerProduct(P, v, v);
			Matrix I;
			P *= (real)-2.0;
			P += I;
			H %= P;
			H *= P;
			
			reflectors.push_back(P);

		}

		
	}


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
