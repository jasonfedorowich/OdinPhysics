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

		void inverse(Matrix4& inv);
		rl determinant();

	};

	struct LU3 {

		Matrix3 L, U, P;

		void pivot(Matrix3& A);

		LU3(Matrix3& A);
		LU3(Matrix3&& A);

		void forwardSub(Vector3& x, Vector3& b);
		void backSub(Vector3& x, Vector3& b);

		void solve(Vector3& x, Vector3& b);
		void solve(Vector3& x, Vector3&& b);
		void solve(Matrix3& x, Matrix3& b);
		void solve(Matrix3& x, Matrix3&& b);

		void inverse(Matrix3& inv);
		rl determinant();

	};

}
