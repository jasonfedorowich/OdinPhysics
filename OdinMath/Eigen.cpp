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
			qr<Matrix4, QRDecomp4, rl>(copy, V, iterations, shift);
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
	
	void QREigen4::sortEigenvalues()
	{
		int i;
		for ( i = 1; i < 4; i++) {
			if (E[i] < E[i - 1])
				break;

		}
		if (i == 4)
			return;

		std::multimap<rl, Vector4> _map;
		i = 0;
		for (i = 0; i < 4; i++) {
			_map.insert({ E[i], V.getCol(i) });

		}
		i = 0;
		for (auto it = _map.begin(); it != _map.end(); it++, i++) {
			E[i] = it->first;
			V.setCol(i, it->second);
		}
		
		
	}
	
	
	void QREigen3::hessenbergMatrix(Matrix3& H)
	{
		Matrix3 copy = H;
		std::vector<Matrix3> reflectors;
		tridiag<Matrix3, Vector3, rl>(copy, reflectors, 3);

		while (!reflectors.empty()) {
			V %= reflectors.back();
			reflectors.pop_back();
		}
	}

	void QREigen3::rotation(Matrix3& A, Matrix3& R, Matrix3& RT, int i, int j)
	{
	}

}
