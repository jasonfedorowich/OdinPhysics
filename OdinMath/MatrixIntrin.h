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

		InMatrix4F(float A[][3]) {
			InVectf zeroes = _mm_set1_ps(0.f);
			InVectf t1 = _mm_loadu_ps(&A[0][0]);
			InVectf t2 = _mm_loadu_ps(&A[1][1]);
			InVectf t3 = _mm_load_ss(&A[2][2]);

			InVectf tmp = _mm_shuffle_ps(t1, zeroes, _MM_SHUFFLE(0, 0, 2, 2));
			row[0] = _mm_shuffle_ps(t1, tmp, _MM_SHUFFLE(3, 0, 1, 0));

			tmp = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(0, 0, 3, 3));
			InVectf tmp1 = _mm_shuffle_ps(t2, zeroes, _MM_SHUFFLE(3, 3, 1, 1));

			row[1] = _mm_shuffle_ps(tmp, tmp1, _MM_SHUFFLE(3, 0, 3, 0));
			row[2] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 0, 3, 2));
			row[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);

		}

		InMatrix4F(){}

	};

	struct InMatrix4D {
		InVectd row[4];

		InMatrix4D(double A[][4]) {
			row[0] = _mm256_loadu_pd(A[0]);
			row[1] = _mm256_loadu_pd(A[1]);
			row[2] = _mm256_loadu_pd(A[2]);
			row[3] = _mm256_loadu_pd(A[3]);
		}

		InMatrix4D(double A[][3]) {
			__m128d zeroes = _mm_set1_pd(0.0);
			__m128d t1 = _mm_loadu_pd(&A[0][0]);
			__m128d t2 = _mm_loadu_pd(&A[0][2]);
			__m128d t3 = _mm_loadu_pd(&A[1][1]);
			__m128d t4 = _mm_loadu_pd(&A[2][0]);
			__m128d t5 = _mm_load_pd1(&A[2][2]);

			__m128d tmp = _mm_shuffle_pd(t2, zeroes, 0x0);
			row[0] = _mm256_set_m128d(tmp, t1);

			tmp = _mm_shuffle_pd(t2, t3, 0x1);
			__m128d tmp1 = _mm_shuffle_pd(t3, zeroes, 0x1);
			row[1] = _mm256_set_m128d(tmp1, tmp);

			tmp = _mm_shuffle_pd(t5, zeroes, 0x0);
			row[2] = _mm256_set_m128d(tmp, t4);
			row[3] = _mm256_setr_pd(0.0, 0.0, 0.0, 1.0);

		}


		InMatrix4D() {}
	};


	
	inline void storeMat3(InMatrix4F& mat, float R[][3]) {
		InVectf tmp = _mm_shuffle_ps(mat.row[0], mat.row[1], _MM_SHUFFLE(0, 0, 2, 2));
		_mm_storeu_ps(&R[0][0], _mm_shuffle_ps(mat.row[0], tmp, _MM_SHUFFLE(3, 0, 1, 0)));
		
		tmp = _mm_shuffle_ps(mat.row[1], mat.row[1], _MM_SHUFFLE(2, 2, 1, 1));
		_mm_storeu_ps(&R[1][1], _mm_shuffle_ps(tmp, mat.row[2], _MM_SHUFFLE(1, 0, 3, 0)));
		_mm_store_ss(&R[2][2], _mm_shuffle_ps(mat.row[2], mat.row[2], _MM_SHUFFLE(2, 2, 2, 2)));
	}

	inline void storeMat3(InMatrix4D& mat, double R[][3]) {
		_mm256_storeu_pd(&R[0][0], mat.row[0]);
		_mm256_storeu_pd(&R[1][0], mat.row[1]);

		__m256d r = _mm256_shuffle_pd(mat.row[1], mat.row[2], 0x3);
		r = _mm256_permutex_pd(r, 0x56);
		r = _mm256_unpacklo_pd(r, mat.row[2]);
		_mm256_storeu_pd(&R[1][2], r);

		
	}

	inline void storeMat4(InMatrix4F& mat, float R[][4]) {
		_mm_store_ps(R[0], mat.row[0]);
		_mm_store_ps(R[1], mat.row[1]);
		_mm_store_ps(R[2], mat.row[2]);
		_mm_store_ps(R[3], mat.row[3]);

	}


	inline void storeMat4(InMatrix4D& mat, double R[][4]) {
		_mm256_store_pd(R[0], mat.row[0]);
		_mm256_store_pd(R[1], mat.row[1]);
		_mm256_store_pd(R[2], mat.row[2]);
		_mm256_store_pd(R[3], mat.row[3]);

	}

	inline void matMult4f(InMatrix4F& Af, InMatrix4F& Bf, InMatrix4F& O) {
		O.row[0] = _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0x00), Bf.row[0]);
		O.row[0] = _mm_add_ps(O.row[0], _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0x55), Bf.row[1]));
		O.row[0] = _mm_add_ps(O.row[0], _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0xaa), Bf.row[2]));
		O.row[0] = _mm_add_ps(O.row[0], _mm_mul_ps(_mm_shuffle_ps(Af.row[0], Af.row[0], 0xff), Bf.row[3]));


		O.row[1] = _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0x00), Bf.row[0]);
		O.row[1] = _mm_add_ps(O.row[1], _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0x55), Bf.row[1]));
		O.row[1] = _mm_add_ps(O.row[1], _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0xaa), Bf.row[2]));
		O.row[1] = _mm_add_ps(O.row[1], _mm_mul_ps(_mm_shuffle_ps(Af.row[1], Af.row[1], 0xff), Bf.row[3]));

		O.row[2] = _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0x00), Bf.row[0]);
		O.row[2] = _mm_add_ps(O.row[2], _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0x55), Bf.row[1]));
		O.row[2] = _mm_add_ps(O.row[2], _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0xaa), Bf.row[2]));
		O.row[2] = _mm_add_ps(O.row[2], _mm_mul_ps(_mm_shuffle_ps(Af.row[2], Af.row[2], 0xff), Bf.row[3]));

		O.row[3] = _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0x00), Bf.row[0]);
		O.row[3] = _mm_add_ps(O.row[3], _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0x55), Bf.row[1]));
		O.row[3] = _mm_add_ps(O.row[3], _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0xaa), Bf.row[2]));
		O.row[3] = _mm_add_ps(O.row[3], _mm_mul_ps(_mm_shuffle_ps(Af.row[3], Af.row[3], 0xff), Bf.row[3]));
	}

	inline void matMult4d(InMatrix4D& Af, InMatrix4D& Bf, InMatrix4D& O) {
		O.row[0] = _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0x00), Bf.row[0]);
		O.row[0] = _mm256_add_pd(O.row[0], _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0x55), Bf.row[1]));
		O.row[0] = _mm256_add_pd(O.row[0], _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0xaa), Bf.row[2]));
		O.row[0] = _mm256_add_pd(O.row[0], _mm256_mul_pd(_mm256_permutex_pd(Af.row[0], 0xff), Bf.row[3]));


		O.row[1] = _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0x00), Bf.row[0]);
		O.row[1] = _mm256_add_pd(O.row[1], _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0x55), Bf.row[1]));
		O.row[1] = _mm256_add_pd(O.row[1], _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0xaa), Bf.row[2]));
		O.row[1] = _mm256_add_pd(O.row[1], _mm256_mul_pd(_mm256_permutex_pd(Af.row[1], 0xff), Bf.row[3]));

		O.row[2] = _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0x00), Bf.row[0]);
		O.row[2] = _mm256_add_pd(O.row[2], _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0x55), Bf.row[1]));
		O.row[2] = _mm256_add_pd(O.row[2], _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0xaa), Bf.row[2]));
		O.row[2] = _mm256_add_pd(O.row[2], _mm256_mul_pd(_mm256_permutex_pd(Af.row[2], 0xff), Bf.row[3]));

		O.row[3] = _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0x00), Bf.row[0]);
		O.row[3] = _mm256_add_pd(O.row[3], _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0x55), Bf.row[1]));
		O.row[3] = _mm256_add_pd(O.row[3], _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0xaa), Bf.row[2]));
		O.row[3] = _mm256_add_pd(O.row[3], _mm256_mul_pd(_mm256_permutex_pd(Af.row[3], 0xff), Bf.row[3]));
	}
	
	template<typename T, int N>
	inline void matMult4(T A[][N],  T B[][N], T R[][N]) {
		return;

	}

	template <> inline void matMult4<float>( float A[][4],  float B[][4], float R[][4]) {
		InMatrix4F Af(A);
		InMatrix4F Bf(B);
		InMatrix4F O;

		matMult4f(Af, Bf, O);
		storeMat4(O, R);
	}

	template <> inline void matMult4<float>(float A[][3], float B[][3], float R[][3]) {
		InMatrix4F Af(A);
		InMatrix4F Bf(B);
		InMatrix4F O;

		matMult4f(Af, Bf, O);
		storeMat3(O, R);
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

	inline void matVect4f(InMatrix4F& M, InVectf& v, InVectf& O) {

		InVectf a1 = _mm_mul_ps(M.row[0], v);
		InVectf a2 = _mm_mul_ps(M.row[1], v);
		InVectf a3 = _mm_mul_ps(M.row[2], v);
		InVectf a4 = _mm_mul_ps(M.row[3], v);

		a1 = _mm_hadd_ps(a1, a2);
		a2 = _mm_hadd_ps(a3, a4);
		O = _mm_hadd_ps(a1, a2);


	}

	inline void matVect4d(InMatrix4D& M, InVectd& v, InVectd& O) {

		InVectd res1 = _mm256_mul_pd(M.row[0], v);
		InVectd res2 = _mm256_mul_pd(M.row[1], v);
		InVectd res3 = _mm256_mul_pd(M.row[2], v);
		InVectd res4 = _mm256_mul_pd(M.row[3], v);

		res1 = _mm256_hadd_pd(res1, res2);
		res3 = _mm256_hadd_pd(res3, res4);

		__m128d tmp3 = _mm256_extractf128_pd(res1, 0);
		__m128d tmp4 = _mm256_extractf128_pd(res1, 1);

		tmp3 = _mm_add_pd(tmp3, tmp4);

		__m128d tmp5 = _mm256_extractf128_pd(res3, 0);
		tmp4 = _mm256_extractf128_pd(res3, 1);

		tmp4 = _mm_add_pd(tmp5, tmp4);

		O = _mm256_set_m128d(tmp4, tmp3);
	

	}

	template<typename T, int N>
	inline void matVect4(T A[][N], T* v, T* r) {
		return;
	}

	template <> inline void matVect4<float>(float A[][4], float* v, float* r) {
		InMatrix4F Af(A);
		InVectf vf = _mm_loadu_ps(v);
		InVectf O;
		matVect4f(Af, vf, O);

		_mm_store_ps(r, O);


	}

	template <> inline void matVect4<double>(double A[][4], double* v, double* r) {
		InMatrix4D Af(A);
		InVectd vf = _mm256_loadu_pd(v);
		InVectd O;
		matVect4d(Af, vf, O);
		_mm256_store_pd(r, O);

	}

	template<> inline void matVect4<float>(float A[][3], float* v, float* r) {
		InMatrix4F Af(A);
		InVectf vf = loadVector3(v);
		InVectf O;
		matVect4f(Af, vf, O);
		storeVector3(r, O);

	}

	template<> inline void matVect4<double>(double A[][3], double* v, double* r) {
		InMatrix4D Ad(A);
		InVectd vf = loadVector3(v);
		InVectd O;
		matVect4d(Ad, vf, O);
		storeVector3(r, O);

	}

	template<typename T>
	inline void vectMatMult4(T* d, T M[][4], T* out) {
		return;
	}

	template<> inline void vectMatMult4(float* v, float A[][4], float* out) {
		InMatrix4F M(A);

		InVectf v1 = _mm_set1_ps(v[0]);
		InVectf v2 = _mm_set1_ps(v[1]);
		InVectf v3 = _mm_set1_ps(v[2]);
		InVectf v4 = _mm_set1_ps(v[3]);

		InVectf t1 = _mm_mul_ps(v1, M.row[0]);
		InVectf t2 = _mm_mul_ps(v2, M.row[1]);
		InVectf t3 = _mm_mul_ps(v3, M.row[2]);
		InVectf t4 = _mm_mul_ps(v4, M.row[3]);

		t1 = _mm_add_ps(t1, t2);
		t3 = _mm_add_ps(t3, t4);
		t1 = _mm_add_ps(t1, t3);

		_mm_store_ps(out, t1);
	}

	
	inline void transpose4d(InMatrix4D& in, InMatrix4D& out) {
		__m256d vTemp1 = _mm256_shuffle_pd(in.row[0], in.row[2], 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		__m256d vTemp2 = _mm256_shuffle_pd(in.row[1], in.row[3], 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		out.row[0] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[0], 0x55), _mm256_permutex_pd(in.row[2], 0x55), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[1], 0x55), _mm256_permutex_pd(in.row[3], 0x55), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		out.row[1] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[0], 0xaa), _mm256_permutex_pd(in.row[2], 0xaa), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[1], 0xaa), _mm256_permutex_pd(in.row[3], 0xaa), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		out.row[2] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

		vTemp1 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[0], 0xff), _mm256_permutex_pd(in.row[2], 0xff), 0x4);
		vTemp1 = _mm256_permutex_pd(vTemp1, 0x10);
		vTemp2 = _mm256_shuffle_pd(_mm256_permutex_pd(in.row[1], 0xff), _mm256_permutex_pd(in.row[3], 0xff), 0x4);
		vTemp2 = _mm256_permutex_pd(vTemp2, 0x10);

		out.row[3] = _mm256_shuffle_pd(vTemp1, vTemp2, 0x0);

	}

	inline void transpose4f(InMatrix4F& in, InMatrix4F& out) {
		InVectf vTemp1 = _mm_shuffle_ps(in.row[0], in.row[1], _MM_SHUFFLE(1, 0, 1, 0));
		InVectf vTemp3 = _mm_shuffle_ps(in.row[0], in.row[1], _MM_SHUFFLE(3, 2, 3, 2));
		InVectf vTemp2 = _mm_shuffle_ps(in.row[2], in.row[3], _MM_SHUFFLE(1, 0, 1, 0));
		InVectf vTemp4 = _mm_shuffle_ps(in.row[2], in.row[3], _MM_SHUFFLE(3, 2, 3, 2));

		out.row[0] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(2, 0, 2, 0));
		out.row[1] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(3, 1, 3, 1));
		out.row[2] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(2, 0, 2, 0));
		out.row[3] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(3, 1, 3, 1));

	}

	template<typename T, int N>
	inline void transpose4(T A[][N], T O[][N]) { return; }

	template <> inline void transpose4<float>(float A[][4], float O[][4]) {
		InMatrix4F output;
		InMatrix4F AA(A);

		transpose4f(AA, output);
		storeMat4(AA, O);

	}
	template <> inline void transpose4<double>(double A[][4], double O[][4]) {
		InMatrix4D output;
		InMatrix4D AA(A);

		transpose4d(AA, output);
		storeMat4(AA, O);

	}

	template <> inline void transpose4<float>(float A[][3], float O[][3]) {
		InMatrix4F output;
		InMatrix4F AA(A);

		transpose4f(AA, output);
		storeMat3(AA, O);

	}
	template <> inline void transpose4<double>(double A[][3], double O[][3]) {
		InMatrix4D output;
		InMatrix4D AA(A);

		transpose4d(AA, output);
		storeMat3(AA, O);

	}

#define PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )

	inline float trace4f(InMatrix4F& M) {
		InVectf tmp0 = _mm_shuffle_ps(M.row[0], M.row[1], _MM_SHUFFLE(1, 1, 0, 0));
		InVectf tmp1 = _mm_shuffle_ps(M.row[2], M.row[3], _MM_SHUFFLE(3, 3, 2, 2));
		tmp0 = _mm_shuffle_ps(tmp0, tmp1, _MM_SHUFFLE(3, 0, 3, 0));
		tmp0 = _mm_hadd_ps(tmp0, tmp0);
		tmp0 = _mm_hadd_ps(tmp0, tmp0);
		return _mm_cvtss_f32(tmp0);

	}

	inline double trace4d(InMatrix4D& M) {
		InVectd tmp0 = _mm256_shuffle_pd(M.row[0], M.row[1], 0x2);
		InVectd tmp1 = _mm256_shuffle_pd(M.row[1], M.row[2], 0x8);
		tmp0 = _mm256_hadd_pd(tmp0, tmp1);
		tmp0 = _mm256_add_pd(tmp0, _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_DDDD));
		return _mm256_cvtsd_f64(tmp0);


	}

	template<typename T, int N>
	inline T trace4(T A[][N]) {
		return 0.0;
	}

	
	template <> inline float trace4<float>(float A[][4]) {
		InMatrix4F M(A);
		return trace4f(M);

	}

	template <> inline double trace4<double>(double A[][4]) {
		InMatrix4D M(A);
		return trace4d(M);

	}
	template <> inline float trace4<float>(float A[][3]) {
		InMatrix4F M(A);
		return trace4f(M);

	}

	template <> inline double trace4<double>(double A[][3]) {
		InMatrix4D M(A);
		return trace4d(M);

	}


	inline float traceSq4f(InMatrix4F& M) {
		InVectf tmp0 = _mm_shuffle_ps(M.row[0], M.row[1], _MM_SHUFFLE(1, 1, 0, 0));
		InVectf tmp1 = _mm_shuffle_ps(M.row[2], M.row[3], _MM_SHUFFLE(3, 3, 2, 2));
		tmp0 = _mm_shuffle_ps(tmp0, tmp1, _MM_SHUFFLE(3, 0, 3, 0));
		tmp0 = _mm_mul_ps(tmp0, tmp0);
		tmp0 = _mm_hadd_ps(tmp0, tmp0);
		tmp0 = _mm_hadd_ps(tmp0, tmp0);
		return _mm_cvtss_f32(tmp0);
	}

	inline double traceSq4d(InMatrix4D& M) {
		InVectd tmp0 = _mm256_shuffle_pd(M.row[0], M.row[1], 0x2);
		InVectd tmp1 = _mm256_shuffle_pd(M.row[1], M.row[2], 0x8);
		__m128d tmp = _mm256_extractf128_pd(tmp1, 0x1);
		tmp0 = _mm256_insertf128_pd(tmp0, tmp, 0x1);
		tmp0 = _mm256_hadd_pd(tmp0, tmp0);
		tmp0 = _mm256_add_pd(tmp0, _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_DDDD));
		return _mm256_cvtsd_f64(tmp0);
	}


	template<typename T, int N>
	inline T traceSq4(T A[][N]) {
		return 0.0;
	}

	template <> inline float traceSq4<float>(float A[][4]) {
		InMatrix4F M(A);
		return traceSq4f(M);
	}
	template <> inline double traceSq4<double>(double A[][4]) {
		InMatrix4D M(A);
		return traceSq4d(M);
	}
	template <> inline double traceSq4<double>(double A[][3]) {
		InMatrix4D M(A);
		return traceSq4d(M);
	}
	template <> inline float traceSq4<float>(float A[][3]) {
		InMatrix4F M(A);
		return traceSq4f(M);
	}

#define PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )

	inline float deter4f(InMatrix4F& M) {

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


	inline double deter4d(InMatrix4D& M) {
		InVectd v0 = _mm256_permutex_pd(M.row[0], 0x0);
		v0 = _mm256_mul_pd(v0, M.row[1]);

		InVectd v1 = _mm256_permutex_pd(M.row[0], 0x55);
		v1 = _mm256_mul_pd(v1, M.row[1]);

		InVectd v2 = _mm256_permutex_pd(M.row[0], 0xAA);
		v2 = _mm256_mul_pd(v2, M.row[1]);

		InVectd v3 = _mm256_permutex_pd(M.row[0], 0xff);
		v3 = _mm256_mul_pd(v3, M.row[1]);

		InVectd v4 = _mm256_mul_pd(_mm256_permutex_pd(M.row[2], 0x0), M.row[3]);
		InVectd v5 = _mm256_mul_pd(_mm256_permutex_pd(M.row[2], 0x55), M.row[3]);
		InVectd v6 = _mm256_mul_pd(_mm256_permutex_pd(M.row[2], 0xaa), M.row[3]);
		InVectd v7 = _mm256_mul_pd(_mm256_permutex_pd(M.row[2], 0xff), M.row[3]);
		// _MM_SHUFFLE(0, 3, 2, 1)
		InVectd tmp0 = _mm256_permutex_pd(v0, _MM_PERM_ENUM::_MM_PERM_ADCB);
		//_MM_SHUFFLE(2, 2, 3, 3)
		InVectd tmp1 = _mm256_shuffle_pd(v0, v1, 0x4);
		__m128d tmp = _mm256_extractf128_pd(tmp1, 0x1);

		tmp0 = _mm256_insertf128_pd(tmp0, tmp, 0x1);

		InVectd tmp2 = _mm256_shuffle_pd(v1, v2, 0x0);
		tmp2 = _mm256_permutex_pd(tmp2, _MM_PERM_ENUM::_MM_PERM_AABA);
		//_MM_SHUFFLE(1, 1, 0, 0)
		InVectd tmp3 = _mm256_shuffle_pd(v3, v2, 0x2);
		tmp3 = _mm256_permutex_pd(tmp3, _MM_PERM_ENUM::_MM_PERM_BAAA);
		tmp = _mm256_extractf128_pd(tmp2, 0x0);
		tmp2 = _mm256_insertf128_pd(tmp3, tmp, 0x0);

		InVectd fi = _mm256_sub_pd(tmp0, tmp2);

		//_MM_SHUFFLE(3, 3, 3, 3)
		tmp0 = _mm256_shuffle_pd(v1, v2, 0xf);
		tmp = _mm256_extractf128_pd(tmp0, 0x1);
		//_MM_SHUFFLE(2, 2, 1, 1)
		tmp1 = _mm256_permutex_pd(v4, _MM_PERM_ENUM::_MM_PERM_CBCB);
		tmp0 = _mm256_insertf128_pd(tmp1, tmp, 0x0);

		//_MM_SHUFFLE(2, 2, 1, 1)
		tmp2 = _mm256_permutex_pd(v3, _MM_PERM_ENUM::_MM_PERM_CBCB);
		//_MM_SHUFFLE(0, 0, 0, 0)
		tmp3 = _mm256_shuffle_pd(v5, v6, 0x0);
		tmp = _mm256_extractf128_pd(tmp3, 0x0);
		tmp2 = _mm256_insertf128_pd(tmp2, tmp, 0x1);

		InVectd se = _mm256_sub_pd(tmp0, tmp2);

		tmp0 = _mm256_shuffle_pd(v6, v5, 0xf);
		tmp0 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_CADC);
		//_MM_SHUFFLE(3, 3, 2, 2)
		tmp1 = _mm256_shuffle_pd(v5, v4, 0x8);
		tmp = _mm256_extractf128_pd(tmp1, 0x1);
		tmp0 = _mm256_insertf128_pd(tmp0, tmp, 0x1);

		//_MM_SHUFFLE(1, 1, 2, 2)
		tmp2 = _mm256_permutex_pd(v7, _MM_PERM_ENUM::_MM_PERM_CCBC);
		//_MM_SHUFFLE(0, 0, 1, 1)
		tmp3 = _mm256_shuffle_pd(v6, v7, 0x1);
		tmp = _mm256_extractf128_pd(tmp3, 0x0);
		tmp2 = _mm256_insertf128_pd(tmp2, tmp, 0x1);

		InVectd th = _mm256_sub_pd(tmp0, tmp2);

		tmp0 = _mm256_mul_pd(fi, th);
		//_MM_SHUFFLE(0, 0, 2, 3)
		tmp1 = _mm256_permutex_pd(se, _MM_PERM_ENUM::_MM_PERM_AACD);
		tmp2 = _mm256_mul_pd(tmp1, se);
		tmp3 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_CCCB);
		tmp3 = _mm256_addsub_pd(tmp0, tmp3);
		tmp3 = _mm256_permutex_pd(tmp3, _MM_PERM_ENUM::_MM_PERM_DDDA);
		tmp3 = _mm256_addsub_pd(tmp3, tmp2);
		tmp3 = _mm256_add_pd(tmp3, _mm256_shuffle_pd(tmp3, tmp3, 0xf));


		return _mm256_cvtsd_f64(tmp3);



	}
	template<typename T, int N>
	inline T determinant4(T A[][N]) {
		return 0.0;
	}

	template<> inline float determinant4<float, 4>(float A[][4]) {
		InMatrix4F M(A);
		return deter4f(M);
	}
	template<> inline float determinant4<float, 3>(float A[][3]) {
		InMatrix4F M(A);
		return deter4f(M);
	}

	template<> inline double determinant4<double, 4>(double A[][4]) {
		InMatrix4D M(A);
		return deter4d(M);
	}
	template<> inline double determinant4<double, 3>(double A[][3]) {
		InMatrix4D M(A);
		return deter4d(M);
	}
	void matScale4f(InMatrix4F& M, float scale, InMatrix4F& O);
	void matScale4d(InMatrix4D& M, double scale, InMatrix4D& O);
	void addMat4f(InMatrix4F& A, InMatrix4F& B, InMatrix4F& O);
	void addMat4d(InMatrix4D& A, InMatrix4D& B, InMatrix4D& O);
	void subMat4f(InMatrix4F& A, InMatrix4F& B, InMatrix4F& O);
	void subMat4d(InMatrix4D& A, InMatrix4D& B, InMatrix4D& O);
	bool matEquals4f(InMatrix4F& A, InMatrix4F& B);
	bool matEquals4d(InMatrix4D& A, InMatrix4D& B);
	bool invert4f(InMatrix4F& A, InMatrix4F& O, float eps, float* determinant);
	bool invert4d(InMatrix4D& A, InMatrix4D& O, double eps, double* determinant);

	template<typename T>
	void outerProduct4(const T* v1, const T* v2, T R[][4]);

	template<typename T, int N>
	void matScale4(T A[][N], T scale, T R[][N]);

	template<typename T, int N>
	void addMat4(T A[][N], T B[][N], T R[][N]);
	
	template<typename T, int N>
	void subMat4(T A[][N], T B[][N], T R[][N]);

	template<typename T, int N>
	bool matEquals4(T A[][N], T B[][N]);

	template<typename T, int N>
	bool invert4(T A[][N], T O[][N], T episilon=Math<T>::eps, T* deteminant=nullptr);

	

}
