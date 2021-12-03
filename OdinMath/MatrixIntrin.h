#pragma once
#include "OdinMath.h"
#include <intrin.h>
#include <zmmintrin.h>
#include <xmmintrin.h>

namespace OdinMath {

	template<typename T, typename U>
	inline void loadRow(T* row, U& out) {
		return;
	}

	template<> inline void loadRow<float, InVectf>(float* row, InVectf& out) {
		out = _mm_loadu_ps(row);
	}

	template<> inline void loadRow<double, InVectd>(double* row, InVectd& out) {
		out = _mm256_loadu_pd(row);
	}

	template<typename real, typename Vect>
	struct InMatrix4 {
		Vect row[4];

		InMatrix4(real A[][4]) {
			loadRow<real, Vect>(A[0], row[0]);
			loadRow<real, Vect>(A[1], row[1]);
			loadRow<real, Vect>(A[2], row[3]);
			loadRow<real, Vect>(A[3], row[3]);
		}


	};

	struct InMatrix4F {
		InVectf row[4];

		InMatrix4F( float A[][4]) {
			row[0] = _mm_loadu_ps(A[0]);
			row[1] = _mm_loadu_ps(A[1]);
			row[2] = _mm_loadu_ps(A[2]);
			row[3] = _mm_loadu_ps(A[3]);
		}

		InMatrix4F(){}

	};

	struct InMatrix4D {
		InVectd row[4];

		InMatrix4D( double A[][4]) {
			row[0] = _mm256_loadu_pd(A[0]);
			row[1] = _mm256_loadu_pd(A[1]);
			row[2] = _mm256_loadu_pd(A[2]);
			row[3] = _mm256_loadu_pd(A[3]);
		}

		InMatrix4D() {}
	};	
	
	template<typename T>
	inline void matMult4(T A[][4],  T B[][4], T R[][4]) {
		return;

	}

	template <> inline void matMult4<float>( float A[][4],  float B[][4], float R[][4]) {
		InMatrix4F Af(A);
		InMatrix4F Bf(B);

		InVectf row1 = _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0x00), Bf.row[0]);
		row1 = _mm_add_ps(row1, _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0x55), Bf.row[1]));
		row1 = _mm_add_ps(row1, _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0xaa), Bf.row[2]));
		row1 = _mm_add_ps(row1, _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0xff), Bf.row[3]));


		InVectf row2 = _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0x00), Bf.row[0]);
		row2 = _mm_add_ps(row2, _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0x55), Bf.row[1]));
		row2 = _mm_add_ps(row2, _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0xaa), Bf.row[2]));
		row2 = _mm_add_ps(row2, _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0xff), Bf.row[3]));

		InVectf row3 = _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0x00), Bf.row[0]);
		row3 = _mm_add_ps(row3, _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0x55), Bf.row[1]));
		row3 = _mm_add_ps(row3, _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0xaa), Bf.row[2]));
		row3 = _mm_add_ps(row3, _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0xff), Bf.row[3]));

		InVectf row4 = _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0x00), Bf.row[0]);
		row4 = _mm_add_ps(row4, _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0x55), Bf.row[1]));
		row4 = _mm_add_ps(row4, _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0xaa), Bf.row[2]));
		row4 = _mm_add_ps(row4, _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0xff), Bf.row[3]));

		_mm_store_ps(R[0], row1);
		_mm_store_ps(R[1], row2);
		_mm_store_ps(R[2], row3);
		_mm_store_ps(R[3], row4);
	}


	template <> inline void matMult4<double>( double A[][4],  double B[][4], double R[][4]) {
		InMatrix4D Af(A);
		InMatrix4D Bf(B);

		InVectd row1 = _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0x00), Bf.row[0]);
		row1 = _mm256_add_pd(row1, _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0x55), Bf.row[1]));
		row1 = _mm256_add_pd(row1, _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0xaa), Bf.row[2]));
		row1 = _mm256_add_pd(row1, _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0xff), Bf.row[3]));


		InVectd row2 = _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0x00), Bf.row[0]);
		row2 = _mm256_add_pd(row2, _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0x55), Bf.row[1]));
		row2 = _mm256_add_pd(row2, _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0xaa), Bf.row[2]));
		row2 = _mm256_add_pd(row2, _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0xff), Bf.row[3]));

		InVectd row3 = _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0x00), Bf.row[0]);
		row3 = _mm256_add_pd(row3, _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0x55), Bf.row[1]));
		row3 = _mm256_add_pd(row3, _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0xaa), Bf.row[2]));
		row3 = _mm256_add_pd(row3, _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0xff), Bf.row[3]));

		InVectd row4 = _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0x00), Bf.row[0]);
		row4 = _mm256_add_pd(row4, _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0x55), Bf.row[1]));
		row4 = _mm256_add_pd(row4, _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0xaa), Bf.row[2]));
		row4 = _mm256_add_pd(row4, _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0xff), Bf.row[3]));

		_mm256_store_pd(R[0], row1);
		_mm256_store_pd(R[1], row2);
		_mm256_store_pd(R[2], row3);
		_mm256_store_pd(R[3], row4);
	}

	template<typename T>
	inline void matVect4(T A[][4], T* v, T* r) {
		return;
	}

	template <> inline void matVect4<float>(float A[][4], float* v, float* r) {
		InMatrix4F Af(A);
		InVectf vf = _mm_loadu_ps(v);
		
		
		InVectf res = _mm_mul_ps(Af.row[0], vf);
		InVectf row = _mm_add_ps(res, _mm_shuffle_ps(res, res, 0x55));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xaa));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xff));
		
		_mm_store_ss(&r[0], row);

		res = _mm_mul_ps(Af.row[1], vf);
		row = _mm_add_ps(res, _mm_shuffle_ps(res, res, 0x55));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xaa));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xff));

		_mm_store_ss(&r[1], row);

		res = _mm_mul_ps(Af.row[2], vf);
		row = _mm_add_ps(res, _mm_shuffle_ps(res, res, 0xff));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xaa));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0x55));

		_mm_store_ss(&r[2], row);


		res = _mm_mul_ps(Af.row[3], vf);
		row = _mm_add_ps(res, _mm_shuffle_ps(res, res, 0xff));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0x55));
		row = _mm_add_ps(row, _mm_shuffle_ps(res, res, 0xaa));

		_mm_store_ss(&r[3], row);


	}

	template <> inline void matVect4<double>(double A[][4], double* v, double* r) {
		InMatrix4D Af(A);
		InVectd vf = _mm256_loadu_pd(v);


		InVectd res = _mm256_mul_pd(Af.row[0], vf);
		InVectd row = _mm256_add_pd(res, _mm256_permutex_pd(res, 0xff));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0x55));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0xaa));

		_mm256_store_pd(r, row);

		res = _mm256_mul_pd(Af.row[1], vf);
		row = _mm256_add_pd(res, _mm256_permutex_pd(res, 0xff));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0x55));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0xaa));

		_mm256_store_pd(&r[1], row);

		res = _mm256_mul_pd(Af.row[2], vf);
		row = _mm256_add_pd(res, _mm256_permutex_pd(res, 0xff));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0x55));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0xaa));

		_mm256_store_pd(&r[2], row);


		res = _mm256_mul_pd(Af.row[3], vf);
		row = _mm256_add_pd(res, _mm256_permutex_pd(res, 0xff));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0x55));
		row = _mm256_add_pd(row, _mm256_permutex_pd(res, 0xaa));

		_mm256_store_pd(&r[3], row);


	}


	inline void transpose4(float A[][4], InMatrix4F& output) {
		InMatrix4F M(A);

		InVectf vTemp1 = _mm_shuffle_ps(M.row[0], M.row[1], _MM_SHUFFLE(1, 0, 1, 0));
		InVectf vTemp3 = _mm_shuffle_ps(M.row[0], M.row[1], _MM_SHUFFLE(3, 2, 3, 2));
		InVectf vTemp2 = _mm_shuffle_ps(M.row[2], M.row[3], _MM_SHUFFLE(1, 0, 1, 0));
		InVectf vTemp4 = _mm_shuffle_ps(M.row[2], M.row[3], _MM_SHUFFLE(3, 2, 3, 2));

		output.row[0] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(2, 0, 2, 0));
		output.row[1] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(3, 1, 3, 1));
		output.row[2] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(2, 0, 2, 0));
		output.row[3] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(3, 1, 3, 1));

	}

	inline void transpose4(double A[][4], InMatrix4D& output) {
		InMatrix4D M(A);

		__m256d vTemp1 = _mm256_shuffle_pd(M.row[0], M.row[2], 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		__m256d vTemp2 = _mm256_shuffle_pd(M.row[1], M.row[3], 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		output.row[0] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[0], 0x55), _mm256_permutex_pd(M.row[2], 0x55), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[1], 0x55), _mm256_permutex_pd(M.row[3], 0x55), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		output.row[1] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[0], 0xaa), _mm256_permutex_pd(M.row[2], 0xaa), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[1], 0xaa), _mm256_permutex_pd(M.row[3], 0xaa), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		output.row[2] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[0], 0xff), _mm256_permutex_pd(M.row[2], 0xff), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(M.row[1], 0xff), _mm256_permutex_pd(M.row[3], 0xff), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		output.row[3] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

	}

	template<typename T>
	inline void transpose4(T A[][4], T O[][4]) { return; }

	template <> inline void transpose4<float>(float A[][4], float O[][4]) {
		InMatrix4F output;
		transpose4(A, output);

		_mm_store_ps(O[0], output.row[0]);
		_mm_store_ps(O[1], output.row[1]);
		_mm_store_ps(O[2], output.row[2]);
		_mm_store_ps(O[3], output.row[3]);

	}
	template <> inline void transpose4<double>(double A[][4], double O[][4]) {
		InMatrix4D output;

		transpose4(A, output);

		_mm256_store_pd(O[0], output.row[0]);
		_mm256_store_pd(O[1], output.row[1]);
		_mm256_store_pd(O[2], output.row[2]);
		_mm256_store_pd(O[3], output.row[3]);

	}

	template<typename T>
	inline T trace4(T A[][4]) {
		return 0.0;
	}

	
	template <> inline float trace4<float>(float A[][4]) {
		InMatrix4F M(A);
		InVectf tmp0 = _mm_add_ps(M.row[0], _mm_shuffle_ps(M.row[1], M.row[1], _MM_SHUFFLE(1, 1, 1, 1)));
		tmp0 = _mm_add_ps(tmp0, _mm_shuffle_ps(M.row[2], M.row[2], _MM_SHUFFLE(2, 2, 2, 2)));
		tmp0 = _mm_add_ps(tmp0, _mm_shuffle_ps(M.row[3], M.row[3], _MM_SHUFFLE(3, 3, 3, 3)));
		return _mm_cvtss_f32(tmp0);


	}

	template<typename T>
	inline T traceSq4(T A[][4]) {
		return 0.0;
	}

	template <> inline float traceSq4<float>(float A[][4]) {
		InMatrix4F M(A);
		InVectf tmp = _mm_shuffle_ps(M.row[0], M.row[1], _MM_SHUFFLE(1, 1, 0, 0));
		InVectf tmp1 = _mm_shuffle_ps(M.row[2], M.row[3], _MM_SHUFFLE(3, 3, 2, 2));
		tmp = _mm_shuffle_ps(tmp, tmp1, _MM_SHUFFLE(3, 0, 3, 0));
		tmp = _mm_mul_ps(tmp, tmp);
		tmp1 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 2, 1, 1));
		tmp = _mm_add_ps(tmp1, tmp);
		tmp = _mm_add_ss(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 3, 3, 3)));
		return _mm_cvtss_f32(tmp);
	}

#define PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )

	template<typename T>
	inline T determinant4(T A[][4]) {
		return 0.0;
	}

	template<> inline float determinant4<float>(float A[][4]) {
		InMatrix4F M(A);

		__m128 v0 = PERMUTE_PS(M.row[0], _MM_SHUFFLE(0, 0, 0, 0));
		v0 = _mm_mul_ps(v0, M.row[1]);

		__m128 v1 = PERMUTE_PS(M.row[0], _MM_SHUFFLE(1, 1, 1, 1));
		v1 = _mm_mul_ps(v1, M.row[1]);

		__m128 v2 = PERMUTE_PS(M.row[0], _MM_SHUFFLE(2, 2, 2, 2));
		v2 = _mm_mul_ps(v2, M.row[1]);

		__m128 v3 = PERMUTE_PS(M.row[0], _MM_SHUFFLE(3, 3, 3, 3));
		v3 = _mm_mul_ps(v3, M.row[1]);

		__m128 v4 = _mm_mul_ps(PERMUTE_PS(M.row[2], _MM_SHUFFLE(0, 0, 0, 0)), M.row[3]);
		__m128 v5 = _mm_mul_ps(PERMUTE_PS(M.row[2], _MM_SHUFFLE(1, 1, 1, 1)), M.row[3]);
		__m128 v6 = _mm_mul_ps(PERMUTE_PS(M.row[2], _MM_SHUFFLE(2, 2, 2, 2)), M.row[3]);
		__m128 v7 = _mm_mul_ps(PERMUTE_PS(M.row[2], _MM_SHUFFLE(3, 3, 3, 3)), M.row[3]);

		__m128 tmp0 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(0, 3, 2, 1));
		__m128 tmp1 = _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(2, 2, 3, 3));
		tmp0 = _mm_shuffle_ps(tmp0, tmp1, _MM_SHUFFLE(3, 0, 1, 0));

		__m128 tmp2 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 tmp3 = _mm_shuffle_ps(v3, v2, _MM_SHUFFLE(1, 1, 0, 0));
		tmp2 = _mm_shuffle_ps(tmp2, tmp3, _MM_SHUFFLE(3, 0, 3, 0));

		__m128 fi = _mm_sub_ps(tmp0, tmp2);

		tmp0 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 3, 3, 3));
		tmp1 = _mm_shuffle_ps(v4, v4, _MM_SHUFFLE(2, 2, 1, 1));
		tmp0 = _mm_shuffle_ps(tmp0, tmp1, _MM_SHUFFLE(3, 0, 3, 0));

		tmp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(2, 2, 1, 1));
		tmp3 = _mm_shuffle_ps(v5, v6, _MM_SHUFFLE(0, 0, 0, 0));
		tmp2 = _mm_shuffle_ps(tmp2, tmp3, _MM_SHUFFLE(3, 0, 3, 0));

		__m128 se = _mm_sub_ps(tmp0, tmp2);

		tmp0 = _mm_shuffle_ps(v6, v5, _MM_SHUFFLE(3, 3, 3, 3));
		tmp1 = _mm_shuffle_ps(v5, v4, _MM_SHUFFLE(3, 3, 2, 2));
		tmp0 = _mm_shuffle_ps(tmp0, tmp1, _MM_SHUFFLE(3, 0, 3, 0));

		tmp2 = _mm_shuffle_ps(v7, v7, _MM_SHUFFLE(1, 1, 2, 2));
		tmp3 = _mm_shuffle_ps(v6, v7, _MM_SHUFFLE(0, 0, 1, 1));
		tmp2 = _mm_shuffle_ps(tmp2, tmp3, _MM_SHUFFLE(3, 0, 3, 0));

		__m128 th = _mm_sub_ps(tmp0, tmp2);

		tmp0 = _mm_mul_ps(fi, th);
		tmp1 = _mm_shuffle_ps(se, se, _MM_SHUFFLE(0, 0, 2, 3));
		tmp2 = _mm_mul_ps(tmp1, se);

		tmp0 = _mm_sub_ss(tmp0, tmp2);
		tmp0 = _mm_add_ss(tmp0, _mm_shuffle_ps(tmp2, tmp2, _MM_SHUFFLE(1, 1, 1, 1)));
		tmp0 = _mm_sub_ss(tmp0, _mm_shuffle_ps(tmp0, tmp0, _MM_SHUFFLE(1, 1, 1, 1)));
		tmp0 = _mm_add_ss(tmp0, _mm_shuffle_ps(tmp0, tmp0, _MM_SHUFFLE(2, 2, 2, 2)));
		tmp0 = _mm_add_ss(tmp0, _mm_shuffle_ps(tmp0, tmp0, _MM_SHUFFLE(3, 3, 3, 3)));

		return _mm_cvtss_f32(tmp0);
	}



	template<typename T>
	void matScale4(T A[][4], T scale, T R[][4]);

	template<typename T>
	void addMat4(T A[][4], T B[][4], T R[][4]);
	
	template<typename T>
	void subMat4(T A[][4], T B[][4], T R[][4]);

	template<typename T>
	bool matEquals4(T A[][4], T B[][4]);

	template<typename T>
	bool invert4(T A[][4], T O[][4], T episilon=Math<T>::eps, T* deteminant=nullptr);

	

}
