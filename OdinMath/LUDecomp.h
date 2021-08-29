#pragma once
#include "OdinMath.h"
namespace OdinMath {
	struct LU4 {

		Matrix4 L, U, P;

		void pivot(Matrix4& A);

		LU4(Matrix4& A);
		LU4(Matrix4&& A);

		void forwardSub(Vector4& x, Vector4& b);
		void backSub(Vector4& x, Vector4& b);

		void solve(Vector4& x, Vector4& b);
		void solve(Vector4& x, Vector4&& b);
		void solve(Matrix4& x, Matrix4& b);
		void solve(Matrix4& x, Matrix4&& b);

		void invserse(Matrix4& inv);
		rl determinant();

	};

}
