#pragma once
#include "OdinMath.h"

#define MAX_ITERATIONS 100
#define EIGEN_TOL 1e-8

namespace OdinMath {

	enum EigenMode {
		QR, QR_HESS, QR_HESS_SHIFT,
		GIVENS, HESS_GIVENS
	};

	template<typename Matrix, typename real>
	void rot(Matrix& A, Matrix& R, Matrix& RT, int i, int j) {
		real aij = A(i, j);
		real ajj = A(j, j);
		real cos, sin;

		if (ajj <= (real)1e-5) {
			cos = (real)0.0;
			sin = (real)1.0;

		}
		else {
			real tan = aij / ajj;
			real tanSqrt = Math<real>::odSqrt((real)1.0 + tan * tan);

			sin = tan / tanSqrt;
			cos = (real)1.0 / tanSqrt;


		}

		R(j, j) = cos;
		R(j, i) = sin;
		R(i, j) = -sin;
		R(i, i) = cos;

		RT(j, j) = cos;
		RT(j, i) = -sin;
		RT(i, j) = sin;
		RT(i, i) = cos;


	}

	template<typename Matrix, typename real>
	void givens(Matrix& H, Matrix& V, int iterations, int d, bool computeEigenVectors) {
		while (iterations) {
			real sum1 = H.sumDiagSq();

			std::deque<Matrix> transposes;


			for (int j = 0; j < d; j++) {


				for (int i = j + 1; i < d; i++) {
					Matrix R;
					Matrix RT;

					rot<Matrix4, real>(H, R, RT, i, j);

					H %= R;
					transposes.push_back(RT);


					if (computeEigenVectors)
						V *= RT;


				}
			}

			while (!transposes.empty()) {
				H *= transposes.front();

				transposes.pop_front();

			}
			real sum2 = H.sumDiagSq();

			if (Math<real>::odAbs(sum2 - sum1) <= EIGEN_TOL)
				return;
			iterations--;

		}
	}

	template<typename Matrix, typename QRDecomp, typename real>
	void qr(Matrix& A, Matrix& V, int iterations, bool computeEigenVectors, bool shift=false) {
		Matrix I;
		real sigma;
		while (iterations) {
			real sum1 = A.sumDiagSq();
			if (shift) {
				sigma = A.back();
				I = Matrix();
				I *= sigma;
				A -= I;


			}


			QRDecomp qrd(A);
			if (computeEigenVectors)
				V *= qrd.Q;

			A = qrd.R * qrd.Q;
			if (shift)
				A += I;


			rl sum2 = A.sumDiagSq();

			if (Math<rl>::odAbs(sum2 - sum1) <= EIGEN_TOL)
				return;
			iterations--;

		}
	}


	template<typename Matrix, typename Vect, typename real>
	void hessenbergMatrix(Matrix& H, Matrix& V, int d, bool computeEigenVectors) {
		Matrix copy = H;
		std::vector<Matrix> reflectors;
		tridiag<Matrix, Vect, real>(copy, reflectors, d);

		if (computeEigenVectors) {
			while (!reflectors.empty()) {
				V %= reflectors.back();
				reflectors.pop_back();
			}
		}
		


	}

	//compute the Eigenvalues and eigenvectors of Matrix 
	class QREigen4 {
	private:
		Vector4 E;
		Matrix4 V;

		bool computeEigenVectors;

		/*void hessenbergMatrix( Matrix4& H);*/
		/*Takes identity matrix R and given the row i and column j makes a rotation matrix*/
		/*void qr(Matrix4& A, int iterations, bool shift=false);
		void givens(Matrix4& A, int iterations);*/
		

	public:
		QREigen4(Matrix4& A, EigenMode mode, bool computeEVs = true, bool sortEVas=true, int iterations=MAX_ITERATIONS);
		QREigen4(Matrix4&& A, EigenMode mode, bool computeEVs = true, bool sortEVas=true, int iterations=MAX_ITERATIONS);

		void sortEigenvalues();
		Matrix4 getEigenVectors() { return V; }
		Vector4 getEigenValues() { return E; }
	};


	class QREigen3 {
	private:
		Vector3 E;
		Matrix3 V;
		bool computeEigenValues;
		void hessenbergMatrix(Matrix3& H);
		/*Takes identity matrix R and given the row i and column j makes a rotation matrix*/
		void rotation(Matrix3& A, Matrix3& R, Matrix3& RT, int i, int j);
		void qr(Matrix3& A, int iterations, bool shift = false);
		void givens(Matrix3& A, int iterations);

	public:
		QREigen3(Matrix3& A, EigenMode mode, bool computeEVs = true, bool sortEVas = true, int iterations = MAX_ITERATIONS);
		QREigen3(Matrix3&& A, EigenMode mode, bool computeEVs = true, bool sortEVas = true, int iterations = MAX_ITERATIONS);

		void sortEigenvalues();
		Matrix3 getEigenVectors() { return V; }
		Vector3 getEigenValues() { return E; }



	};
	
}

