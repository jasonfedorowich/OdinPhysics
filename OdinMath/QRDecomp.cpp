#include "OdinMath.h"
namespace OdinMath {
	
	
	QRDecomp4::QRDecomp4(Matrix4& matrix)
	{
		/*Matrix4 copy(matrix);*/
		/*pivot<Matrix4, rl>(P, matrix, 4);
		copy *= P;*/
		houseHolder<Matrix4, Vector4, rl>(matrix, Q, R, 4);
	}
	QRDecomp4::QRDecomp4(Matrix4&& matrix)
	{
	/*	pivot<Matrix4, rl>(P, matrix, 3);
		matrix *= P;*/
		houseHolder<Matrix4, Vector4, rl>(matrix, Q, R, 4);
	}
	void QRDecomp4::solve(Vector4& x, Vector4& b)
	{
		/*b *= P;*/
		Matrix4 Qt = Q.getTranspose();
		Vector4 beta = Qt * b;
		backSub<Matrix4, Vector4, rl>(R, x, beta, 4);
	}
	void QRDecomp4::solve(Vector4& x, Vector4&& b)
	{
		/*b *= P;*/
		Matrix4 Qt = Q.getTranspose();
		Vector4 beta = Qt * b;
		backSub<Matrix4, Vector4, rl>(R, x, beta, 4);
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

		/*x *= P;*/

	}
	void QRDecomp4::solve(Matrix4& x, Matrix4&& b)
	{
		Matrix4 Qt = Q.getTranspose();
		for (int i = 0; i < 4; i++) {
			Vector4 v = b.getCol(i);
			Vector4 xx;
			solve(xx, v, Qt);
			x.setCol(i, xx);
		}

		/*x *= P;*/
	}
	void QRDecomp4::solve(Vector4& x, Vector4& b, Matrix4& qt)
	{
	/*	b *= P;*/
		Vector4 beta = qt * b;
		backSub<Matrix4, Vector4, rl>(R, x, beta, 4);
	}
	rl QRDecomp4::determinant()
	{
		rl result = (rl)R(0, 0);
		result *= (rl)R(1, 1);
		result *= (rl)R(2, 2);
		result *= (rl)R(3, 3);
		return result;
	}
	void QRDecomp4::inverse(Matrix4& inv)
	{
		Matrix4 I;
		solve(inv, I);
	}
	QRDecomp3::QRDecomp3(Matrix3& matrix)
	{
	/*	pivot<Matrix3, rl>(P, matrix, 3);
		matrix %= P;*/
		houseHolder<Matrix3, Vector3, rl>(matrix, Q, R, 3);
	}

	QRDecomp3::QRDecomp3(Matrix3&& matrix)
	{
		/*pivot<Matrix3, rl>(P, matrix, 4);
		matrix %= P;*/
		houseHolder<Matrix3, Vector3, rl>(matrix, Q, R, 3);
	}

	void QRDecomp3::solve(Vector3& x, Vector3& b)
	{
		//b *= P;
		Matrix3 Qt = Q.getTranspose();
		Vector3 beta = Qt * b;
		backSub<Matrix3, Vector3, rl>(R, x, beta, 3);
	}

	void QRDecomp3::solve(Vector3& x, Vector3&& b)
	{
		//b *= P;
		Matrix3 Qt = Q.getTranspose();
		Vector3 beta = Qt * b;
		backSub<Matrix3, Vector3, rl>(R, x, beta, 3);
	}

	void QRDecomp3::solve(Matrix3& x, Matrix3& b)
	{
		Matrix3 Qt = Q.getTranspose();
		for (int i = 0; i < 3; i++) {
			Vector3 v = b.getCol(i);
			Vector3 xx;
			solve(xx, v, Qt);
			x.setCol(i, xx);
		}

	/*	x *= P;*/
	}

	void QRDecomp3::solve(Matrix3& x, Matrix3&& b)
	{
		Matrix3 Qt = Q.getTranspose();
		for (int i = 0; i < 3; i++) {
			Vector3 v = b.getCol(i);
			Vector3 xx;
			solve(xx, v, Qt);
			x.setCol(i, xx);
		}

		/*x *= P;*/
	}

	void QRDecomp3::solve(Vector3& x, Vector3& b, Matrix3& qt)
	{
		/*b *= P;*/
		Vector3 beta = qt * b;
		backSub<Matrix3, Vector3, rl>(R, x, beta, 3);
	}

	rl QRDecomp3::determinant()
	{
		rl result = (rl)R(0, 0);
		result *= (rl)R(1, 1);
		result *= (rl)R(2, 2);
		return result;
	}

	void QRDecomp3::inverse(Matrix3& inv)
	{
		Matrix3 I;
		solve(inv, I);
	}

}