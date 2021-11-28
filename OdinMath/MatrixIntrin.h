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

	template <> inline void transpose4(float A[][4], float O[][4]) {
		InMatrix4F output;
		transpose4(A, output);

		_mm_store_ps(O[0], output.row[0]);
		_mm_store_ps(O[1], output.row[1]);
		_mm_store_ps(O[2], output.row[2]);
		_mm_store_ps(O[3], output.row[3]);

	}
	template <> inline void transpose4(double A[][4], double O[][4]) {
		InMatrix4D output;

		transpose4(A, output);

		_mm256_store_pd(O[0], output.row[0]);
		_mm256_store_pd(O[1], output.row[1]);
		_mm256_store_pd(O[2], output.row[2]);
		_mm256_store_pd(O[3], output.row[3]);

	}

#define PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )

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
