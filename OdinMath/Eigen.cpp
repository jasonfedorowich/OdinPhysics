#include "OdinMath.h"
namespace OdinMath {
	void QREigen4::hessenbergMatrix(Matrix4& H)
	{
		int j;
		rl alpha;
		rl sumSq;
		rl r;
		rl r2;

		for (int i = 0; i < 2; i++) {
			
			sumSq = (rl)0.0;
			for (j = i + 1; j < 4; j++) 
				sumSq += (H(j, i) * H(j, i));

			alpha = Math<rl>::odSqrt(sumSq);
			alpha *= Math<rl>::sign(H(i + 1, i));

			r = sqrt((rl)0.5 * (alpha * alpha - H(i + 1, i) * alpha));
			Vector4 v;
			r2 = (rl)2.0 * r;
			for (j = 0; j < i + 1; j++)
				v[j] = (rl)0.0;
			v[i + 1] = (H(i + 1, i) - alpha) / r2;

			for (j = i + 2; j < 4; j++)
				v[j] = H(j, i) / r2;

			Matrix4 P;
			outterProduct(P, v, v);
			Matrix4 I;
			P = I + (rl)-2.0 * P;

			


		}
	}
	QREigen4::QREigen4(Matrix4& A, bool computeEigenValues)
	{
		this->computeEigenValues = computeEigenValues;
		Matrix4 H = A;
		hessenbergMatrix(H);

	}
}
