#include "OdinMath.h"
namespace OdinMath {
	void QRDecomp4::houseHolder(Matrix4& A)
	{
		std::vector<Matrix4> q(4);
		Matrix4 Z = A;
		rl alpha;
		for (int i = 0; i < 4; i++) {
			Matrix4 m;
			upperIdentity(i, Z, m);
			Z = m;
			Vector4 x = Z.getCol(i);
			alpha = x.length4();
			if (A(i, i) > 0)
				alpha = -alpha;

			Vector4 e = { (rl)0.0, (rl)0.0, (rl)0.0, (rl)0.0 };
			e[i] = (rl)1.0;
			e *= alpha;
			x -= e;
			x.normalize4();

			Matrix4 o;
			outerProduct(o, x, x);
			o *= (rl)2.0;

			
			q[i] -= o;
			Z = q[i] * Z;

		}

		Q = q[0];
		for (int i = 1; i < 4; i++) {
			Q %= q[i];

		}

		R = Q * A;
		Q.transpose();
	}
	void QRDecomp4::upperIdentity(int d, Matrix4& A, Matrix4& m)
	{
		for (int i = d; i < 4; i++) {
			for (int j = d; j < 4; j++) {
				m(i, j) = A(i, j);
			}
				
		}
	}
	void QRDecomp4::backSub(Vector4& x, Vector4& b)
	{
		x[0] = (rl)0.0;
		x[1] = (rl)0.0;
		x[2] = (rl)0.0;
		x[3] = (rl)0.0;

		for (int i = 3; i >= 0; i--) {

			rl t = b[i];

			for (int j = i + 1; j < 4; j++) {
				t -= (R(i, j) * x[j]);
			}
			if (R(i, i) == (rl)0.0)
				throw std::exception("Matrix is singular");

			x[i] = t / R(i, i);
		}
	}
	QRDecomp4::QRDecomp4(Matrix4& matrix)
	{
		houseHolder(matrix);
	}
	void QRDecomp4::solve(Vector4& x, Vector4& b)
	{
		Matrix4 Qt = Q.getTranspose();
		Vector4 beta = Qt * b;
		backSub(x, beta);
	}
	void QRDecomp4::solve(Matrix4& x, Matrix4& b)
	{
		Matrix4 Qt = Q.getTranspose();
		for (int i = 0; i < 4; i++) {
			Vector4 v = b.getCol(i);
			Vector4 xx;
			solve(xx, v, Qt);
			x.setCol(i, xx);
		}

	}
	void QRDecomp4::solve(Vector4& x, Vector4& b, Matrix4& qt)
	{
		Vector4 beta = qt * b;
		backSub(x, beta);
	}
	rl QRDecomp4::determinant()
	{
		rl det = (rl)1.0;
		for (int i = 0; i < 4; i++) {
			det *= R(i, i);
		}
		return det;
	}
	void QRDecomp4::inverse(Matrix4& inv)
	{
		Matrix4 I;
		solve(inv, I);
	}
	void eigen(Matrix4& A, Matrix4& V, Vector4& E, int iterations)
	{
		Matrix4 X = A;
		for (int i = 0; i < iterations; i++) {
			QRDecomp4 qr = QRDecomp4(X);
			V *= qr.Q;
			X = qr.R * qr.Q;


		}

		E = X.diag();

		
	}
	void eigen(Matrix4&& A, Matrix4& V, Vector4& E, int iterations)
	{
		Matrix4 X = A;
		for (int i = 0; i < iterations; i++) {
			QRDecomp4 qr = QRDecomp4(X);
			V *= qr.Q;
			X = qr.R * qr.Q;


		}

		E = X.diag();

	}
}