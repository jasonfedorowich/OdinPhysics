#include "OdinMath.h"

namespace OdinMath {
	
	
	QREigen4::QREigen4(Matrix4& A, EigenMode mode, bool computeEVs, bool sortEVas, int iterations)
	{
		//todo do we need to copy matrix?
		Matrix4 copy(A);
		this->computeEigenVectors = computeEVs;
		bool shift = false;

		switch (mode) {
		case QR_HESS_SHIFT:
			shift = true;
		case QR_HESS:
			hessenbergMatrix<Matrix4, Vector4, rl>(copy, V, 4, computeEigenVectors);
		case QR:
			qr<Matrix4, QRDecomp4, rl>(copy, V, iterations, computeEigenVectors, shift);
			break;
		case HESS_GIVENS:
			hessenbergMatrix<Matrix4, Vector4, rl>(copy, V, 4, computeEigenVectors);
		case GIVENS:
			givens<Matrix4, rl>(copy, V, iterations, 4, computeEigenVectors);
			break;
		}

		E[0] = copy(0, 0);
		E[1] = copy(1, 1);
		E[2] = copy(2, 2);
		E[3] = copy(3, 3);

		if (sortEVas)
			sortEigenvalues();
		
	}

	QREigen4::QREigen4(Matrix4&& A, EigenMode mode, bool computeEVs, bool sortEVas, int iterations)
	{
		//todo do we need to copy matrix?
		this->computeEigenVectors = computeEVs;
		bool shift = false;

		switch (mode) {
		case QR_HESS_SHIFT:
			shift = true;
		case QR_HESS:
			hessenbergMatrix<Matrix4, Vector4, rl>(A, V, 4, computeEigenVectors);
		case QR:
			qr<Matrix4, QRDecomp4, rl>(A, V, iterations, computeEigenVectors, shift);
			break;
		case HESS_GIVENS:
			hessenbergMatrix<Matrix4, Vector4, rl>(A, V, 4, computeEigenVectors);
		case GIVENS:
			givens<Matrix4, rl>(A, V, iterations, 4, computeEigenVectors);
			break;
		}

		E[0] = A(0, 0);
		E[1] = A(1, 1);
		E[2] = A(2, 2);
		E[3] = A(3, 3);

		if (sortEVas)
			sortEigenvalues();
	}
	
	void QREigen4::sortEigenvalues()
	{
		sortEV<Matrix4, Vector4, rl>(E, V, 4);
		
		
	}
	
	

	QREigen3::QREigen3(Matrix3& A, EigenMode mode, bool computeEVs, bool sortEVas, int iterations)
	{
		//todo do we need to copy matrix?
		Matrix3 copy(A);
		this->computeEigenVectors = computeEVs;
		bool shift = false;

		switch (mode) {
		case QR_HESS_SHIFT:
			shift = true;
		case QR_HESS:
			hessenbergMatrix<Matrix3, Vector3, rl>(copy, V, 3, computeEigenVectors);
		case QR:
			qr<Matrix3, QRDecomp3, rl>(copy, V, iterations, computeEigenVectors, shift);
			break;
		case HESS_GIVENS:
			hessenbergMatrix<Matrix3, Vector3, rl>(copy, V, 3, computeEigenVectors);
		case GIVENS:
			givens<Matrix3, rl>(copy, V, iterations, 3, computeEigenVectors);
			break;
		}

		E[0] = copy(0, 0);
		E[1] = copy(1, 1);
		E[2] = copy(2, 2);

		if (sortEVas)
			sortEigenvalues();
	}

	QREigen3::QREigen3(Matrix3&& A, EigenMode mode, bool computeEVs, bool sortEVas, int iterations)
	{
		//todo do we need to copy matrix?
		this->computeEigenVectors = computeEVs;
		bool shift = false;

		switch (mode) {
		case QR_HESS_SHIFT:
			shift = true;
		case QR_HESS:
			hessenbergMatrix<Matrix3, Vector3, rl>(A, V, 3, computeEigenVectors);
		case QR:
			qr<Matrix3, QRDecomp3, rl>(A, V, iterations, computeEigenVectors, shift);
			break;
		case HESS_GIVENS:
			hessenbergMatrix<Matrix3, Vector3, rl>(A, V, 3, computeEigenVectors);
		case GIVENS:
			givens<Matrix3, rl>(A, V, iterations, 3, computeEigenVectors);
			break;
		}

		E[0] = A(0, 0);
		E[1] = A(1, 1);
		E[2] = A(2, 2);

		if (sortEVas)
			sortEigenvalues();

	}

	void QREigen3::sortEigenvalues()
	{
		sortEV<Matrix3, Vector3, rl>(E, V, 3);
	}

}
