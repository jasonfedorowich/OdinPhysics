#pragma once
#include "OdinMath.h"

namespace OdinMath {
	struct QRDecomp4 {

		Matrix4 Q, R;

		void houseHolder(Matrix4& A);
		void upperIdentity(int d, Matrix4& A, Matrix4& m);
		void backSub(Vector4& x, Vector4& b);

		//todo add pivoting
		QRDecomp4(Matrix4& matrix);
		QRDecomp4(Matrix4&& matrix);

		void solve(Vector4& x, Vector4& b);
		void solve(Vector4& x, Vector4&& b);
		void solve(Matrix4& x, Matrix4& b);
		void solve(Matrix4& x, Matrix4&& b);
		void solve(Vector4& x, Vector4& b, Matrix4& qt);

		
		/*Calculates the absolute value of the determinant*/
		rl determinant();
		void inverse(Matrix4& inv);

	};

	void eigen(Matrix4& A ,Matrix4& V, Vector4& E, int iterations);
	void eigen(Matrix4&& A, Matrix4& V, Vector4& E, int iterations);
}
