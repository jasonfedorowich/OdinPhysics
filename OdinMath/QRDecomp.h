#pragma once
#include "OdinMath.h"

namespace OdinMath {

	enum QRMode{
		HOUSEHOLDER,
		GS
	};
	template<typename Matrix, typename Vect, typename real>
	void houseHolder(Matrix& A, Matrix& Q, Matrix& R, int d) {
		std::vector<Matrix> q;
		Matrix Z(A);
		Matrix Z1;
		real alpha;
		int dd = d - 1;
		for (int i = 0; i < dd; i++) {
			minor<Matrix, real>(i, Z, Z1, d);
			Vect x = Z1.getCol(i);
			alpha = x.length();
			if (A(i, i) > 0)
				alpha = -alpha;

			Vect e;
			e[i] = (real)1.0;
			e *= alpha;
			e += x;
			e.normalize();

			Matrix o;
			outerProduct(o, e, e);
			o *= (real)2.0;

			Matrix I;
			I -= o;
			Z = I * Z1;
			q.push_back(I);

		}

		Q = q[0];
		for (int i = 1; i < dd; i++) {
			Q %= q[i];

		}

		R = Q * A;
		Q.transpose();
	}

	template<typename Matrix, typename Vect, typename real>
	void gs(Matrix& A, Matrix& Q, Matrix& R, int d) {

		//assume matrix are identity
		for (int i = 0; i < d; i++) {
			Q(i, i) = (real)0.0;
			R(i, i) = (real)0.0;

		}

		for (int i = 0; i < d; i++) {
			Vect v = A.getCol(i);

			for (int j = 0; j < i-1; j++) {

				Vect q = Q.getCol(j);
				R(j, i) = v.dot(q);
				v -= (R(j, i) * q);

			}
			real l = v.length();
			v /= l;
			Q.setCol(i, v);
			R(i, i) = l;




		}

	}



	struct QRDecomp4 {

		Matrix4 Q, R, P;


		QRDecomp4(Matrix4& matrix, QRMode mode = QRMode::HOUSEHOLDER);
		QRDecomp4(Matrix4&& matrix, QRMode mode = QRMode::HOUSEHOLDER);

		void solve(Vector4& x, Vector4& b);
		void solve(Vector4& x, Vector4&& b);
		void solve(Matrix4& x, Matrix4& b);
		void solve(Matrix4& x, Matrix4&& b);
		void solve(Vector4& x, Vector4& b, Matrix4& qt);

		
		/*Calculates the absolute value of the determinant*/
		rl determinant();
		void inverse(Matrix4& inv);



	};

	struct QRDecomp3 {
		Matrix3 Q, R, P;


		QRDecomp3(Matrix3& matrix);
		QRDecomp3(Matrix3&& matrix);

		void solve(Vector3& x, Vector3& b);
		void solve(Vector3& x, Vector3&& b);
		void solve(Matrix3& x, Matrix3& b);
		void solve(Matrix3& x, Matrix3&& b);
		void solve(Vector3& x, Vector3& b, Matrix3& qt);


		/*Calculates the absolute value of the determinant*/
		rl determinant();
		void inverse(Matrix3& inv);
	};

	
}
