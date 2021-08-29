#include "OdinMath.h"
#include <deque>
#include <map>
namespace OdinMath {
	void QREigen4::hessenbergMatrix(Matrix4& H)
	{
		int j;
		rl alpha;
		rl sumSq;
		rl r;
		rl r2;
		std::vector<Matrix4> Q;

		for (int i = 0; i < 2; i++) {
			
			sumSq = (rl)0.0;
			for (j = i + 1; j < 4; j++) 
				sumSq += (H(j, i) * H(j, i));

			alpha = Math<rl>::odSqrt(sumSq);
			alpha *= ((rl)-1.0 * Math<rl>::sign(H(i + 1, i)));

			r = sqrt((rl)0.5 * (alpha * alpha - H(i + 1, i) * alpha));
			Vector4 v;
			r2 = (rl)2.0 * r;
			for (j = 0; j < i + 1; j++)
				v[j] = (rl)0.0;
			v[i + 1] = (H(i + 1, i) - alpha) / r2;

			for (j = i + 2; j < 4; j++)
				v[j] = H(j, i) / r2;

			Matrix4 P;
			outerProduct(P, v, v);
			Matrix4 I;
			P = I + (rl)-2.0 * P;
			H %= P;
			H *= P;
			if(computeEigenValues)
				Q.push_back(P);


		}

		if (computeEigenValues) {

			while (!Q.empty()) {
				V %= Q.back();
				Q.pop_back();
			}

		}
	}
	void QREigen4::rotation(Matrix4& A, Matrix4& R, Matrix4& RT, int i, int j)
	{
		rl aij = A(i, j);
		rl ajj = A(j, j);
		rl cos, sin;

		if (ajj <= (rl)EIGEN_TOL) {
			cos = (rl)0.0;
			sin = (rl)1.0;

		}
		else {
			rl tan = aij / ajj;
			rl tanSqrt = Math<rl>::odSqrt((rl)1.0 + tan * tan);

			sin = tan / tanSqrt;
			cos = (rl)1.0 / tanSqrt;


		}

		RT(j, j) = cos;
		RT(j, i) = sin;
		RT(i, j) = -sin;
		RT(i, i) = cos;

		R(j, j) = cos;
		R(j, i) = -sin;
		R(i, j) = sin;
		R(i, i) = cos;

			

	}
	QREigen4::QREigen4(Matrix4& A, bool computeEigenValues, int iterations, bool sortEig)
	{
		this->computeEigenValues = computeEigenValues;
		Matrix4 H = A;
		hessenbergMatrix(H);
		

		while (iterations) {

			std::deque<Matrix4> transposes;


			for (int j = 0; j < 4; j++) {


				for (int i = j + 1; i < 4; i++) {
					Matrix4 R;
					Matrix4 RT;
					rotation(H, R, RT, i, j);

					H %= RT;
					transposes.push_back(R);

					if (computeEigenValues)
						V *= R;
					
				}
			}

			while (!transposes.empty()) {
				H *= transposes.front();
				
				transposes.pop_front();

			}

			

			iterations--;

		}
		
		for (int i = 0; i < 4; i++) {

			E[i] = H(i, i);
		}

		if (sortEig) {

			sortEigenvalues();

		}

		//
	}
	QREigen4::QREigen4(Matrix4&& A, bool computeEigenValues, int iterations, bool sortEig)
	{

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
}
