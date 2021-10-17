#include "OdinMath.h"

namespace OdinMath {
	void LU4::pivot(Matrix4& A)
	{
		rl t;
		for (int i = 0; i < 4; i++) {
			int maxR = i;
			rl maxV = A(i, i);
			for (int j = i; j < 4; j++) {
				t = Math<rl>::odAbs(A(j, i));
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
	LU4::LU4(Matrix4& A)
	{
		
		pivot(A);
		A %= P;
		//Matrix4 Ap = P * A;
		

		for (int i = 0; i < 4; i++) {
			L(i, i) = (rl)1.0;
		}

		for (int i = 0; i < 4; i++) {
			U(i, i) = (rl)0.0;
		}

		for (int j = 0; j < 4; j++) {

			for (int i = 0; i <= j; i++) {

				rl sum = (rl)0.0;
				for (int k = 0; k < i; k++) {
					sum += (L(i, k) * U(k, j));
				}

				U(i, j) = A(i, j) - sum;
			}

			for (int i = j + 1; i < 4; i++) {

				rl sum = (rl)0.0;
				for (int k = 0; k < j; k++) {
					sum += (L(i, k) * U(k, j));
				}
				if (U(j, j) == (rl)0.0)
					throw std::exception("Matrix is singular");
				L(i, j) = ((rl)1.0 / U(j, j)) * (A(i, j) - sum);

			}
		}
	}
	void LU4::forwardSub(Vector4& x, Vector4& b)
	{
		x[0] = (rl)0.0;
		x[1] = (rl)0.0;
		x[2] = (rl)0.0;
		x[3] = (rl)0.0;

		for (int i = 0; i < 4; i++) {

			rl t = b[i];

			for (int j = 0; j < i; j++) {
				t -= (L(i, j) * x[j]);
			}

			x[i] = t / L(i, i);
		}
	}
	void LU4::backSub(Vector4& x, Vector4& b)
	{
		x[0] = (rl)0.0;
		x[1] = (rl)0.0;
		x[2] = (rl)0.0;
		x[3] = (rl)0.0;

		for (int i = 3; i >= 0; i--) {

			rl t = b[i];

			for (int j = i + 1; j < 4; j++) {
				t -= (U(i, j) * x[j]);
			}

			x[i] = t / U(i, i);
		}
	}
	void LU4::solve(Vector4& x, Vector4& b)
	{
		Vector4 z = P * b;
		Vector4 q;
		forwardSub(q, z);
		backSub(x, q);
	}
	void LU4::solve(Matrix4& x, Matrix4& b)
	{
		for (int i = 0; i < 4; i++) {
			Vector4 v = b.getCol(i);
			Vector4 r;
			solve(r, v);
			x.setCol(i, r);

		}
	}
	void LU4::invserse(Matrix4& inv)
	{
		Matrix4 I;
		solve(inv, I);
	}

	rl LU4::determinant()
	{
		rl det = (rl)1.0;
		for (int i = 0; i < 4; i++) {
			det *= U(i, i);
			if (P(i, i) != (rl)1.0)
				det *= (rl)-1.0;
		}

		return det;

	}
	
}
