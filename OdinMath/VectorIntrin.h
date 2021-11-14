#pragma once
#include "OdinMath.h"
#include <intrin.h>
#include <zmmintrin.h>
#include <xmmintrin.h>

namespace OdinMath {

	typedef __m128 InVectf;
	typedef __m256d InVectd;
	typedef __m128i InVecti;

	//inline void loadVector4(InVectf& out, const float* in) {
	//	out = _mm_loadu_ps(in);
	//}
	//inline void storeVector4(InVectf& in, float* out) {
	//	_mm_store_ps(out, in);
	//}

	//inline void loadVector4(InVectf& out, Vector<4, float>& in) {
	//	out = _mm_loadu_ps(in.getData());
	//}

	//inline void storeVector4(InVectf& in, Vector<4, float>& out) {
	//	_mm_store_ps(out.getData(), in);
	//}
	
		//template<> inline float dot3<float>(float* av, float* bv) {
	//	InVectf a = loadVector3(av);
	//	InVectf b = loadVector3(bv);

	//	InVectf r = _mm_mul_ps(a, b);
	//	a = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 1, 0, 0));
	//	b = _mm_add_ps(a, r);
	//	a = _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 2, 2, 2));
	//	b = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 3, 3, 3));
	//	r = _mm_add_ps(a, b);
	//	Vector<4, float> out;
	//	storeVector4(r, out);
	//	return out[0];
	//}

	//inline float dot4(InVectf a, InVectf b) {
	//	InVectf r = _mm_mul_ps(a, b);
	//	a = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 1, 0, 0));
	//	b = _mm_add_ps(a, r);
	//	a = _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 2, 2, 2));
	//	b = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 3, 3, 3));
	//	r = _mm_add_ps(a, b);
	//	Vector<4, float> out;
	//	storeVector4(r, out);
	//	return out[0];

	//}



	//inline float dot3(InVectf a, InVectf b) {

	//	InVectf r = _mm_mul_ps(a, b);
	//	a = _mm_shuffle_ps(r, r, _MM_SHUFFLE(1, 1, 1, 1));
	//	b = _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 2, 2, 2));
	//	b = _mm_add_ps(a, b);
	//	r = _mm_add_ps(r, b);
	//	Vector<4, float> out;
	//	storeVector4(r, out);
	//	return out[0];
	//}

	inline InVectd loadVector3(const double* in) {
		__m128d f1 = _mm_load_pd(&(in[0]));
		__m128d f2 = _mm_load_pd(&(in[1]));
		f2 = _mm_shuffle_pd(f2, f2, _MM_SHUFFLE(0, 0, 1, 1));
		return _mm256_set_m128d(f2, f1);
	}

	inline void storeVector3(double* out, InVectd& in) {
		_mm256_storeu_pd(out, in);
	}

	inline InVectf loadVector3(const float* in) {
		InVectf t1 = _mm_load_ss(&(in[0]));
		InVectf t2 = _mm_load_ss(&(in[1]));
		InVectf t3 = _mm_load_ss(&(in[2]));
		InVectf xy = _mm_unpacklo_ps(t1, t2);
		return _mm_movelh_ps(xy, t3);

	}

	inline void storeVector3(float* out, InVectf& in) {
		_mm_store_ss(&(out[0]), in);
		InVectf t1 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&(out[1]), t1);
		InVectf t2 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ss(&(out[2]), t1);

	}

	inline void add4(InVectf& a, InVectf& b, InVectf& out) {
		out = _mm_add_ps(a, b);
	}
	template<typename T>
	inline void add4(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void add4<float>(const float* a, const float* b, float* out) {
		InVectf aVec = _mm_loadu_ps(a);
		InVectf bVec = _mm_loadu_ps(b);
		InVectf oVec = _mm_add_ps(aVec, bVec);
		_mm_store_ps(out, oVec);

	}
	template<> inline void add4<double>(const double* a, const double* b, double* out) {
		InVectd aVec = _mm256_loadu_pd(a);
		InVectd bVec = _mm256_loadu_pd(b);
		InVectd oVec = _mm256_add_pd(aVec, bVec);
		_mm256_store_pd(out, oVec);

	}


	inline void sub4(InVectf& a, InVectf& b, InVectf& out) {
		out = _mm_sub_ps(a, b);
	}

	template<typename T>
	inline void sub4(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void sub4<float>(const float* a, const float* b, float* out) {
		InVectf aVec = _mm_loadu_ps(a);
		InVectf bVec = _mm_loadu_ps(b);
		InVectf oVec = _mm_sub_ps(aVec, bVec);
		_mm_store_ps(out, oVec);

	}
	template<> inline void sub4<double>(const double* a, const double* b, double* out) {
		InVectd aVec = _mm256_loadu_pd(a);
		InVectd bVec = _mm256_loadu_pd(b);
		InVectd oVec = _mm256_sub_pd(aVec, bVec);
		_mm256_store_pd(out, oVec);

	}


	template<typename T>
	inline void div4(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void div4<float>(const float* a, const float* b, float* out) {
		InVectf aVec = _mm_loadu_ps(a);
		InVectf bVec = _mm_loadu_ps(b);
		InVectf oVec = _mm_div_ps(aVec, bVec);
		_mm_store_ps(out, oVec);

	}
	template<> inline void div4<double>(const double* a, const double* b, double* out) {
		InVectd aVec = _mm256_loadu_pd(a);
		InVectd bVec = _mm256_loadu_pd(b);
		InVectd oVec = _mm256_div_pd(aVec, bVec);
		_mm256_store_pd(out, oVec);


	}

	template<typename T>
	inline bool equals4(const T* a, const T* b) {
		return true;
	}

	template<> inline bool equals4<double>(const double* a, const double* b) {
		InVectd aVec = _mm256_loadu_pd(a);
		InVectd bVec = _mm256_loadu_pd(b);
		
		InVectd tempV = _mm256_xor_pd(aVec, bVec);
		InVecti temp = _mm256_cvtpd_epi32(tempV);
		int comp = 0;


		return (_mm_extract_epi32(temp, 0) == comp && _mm_extract_epi32(temp, 1) == comp &&
			_mm_extract_epi32(temp, 2) == comp && _mm_extract_epi32(temp, 3) == comp);


	}

	template<> inline bool equals4<float>(const float* a, const float* b) {
		InVectf aVec = _mm_loadu_ps(a);
		InVectf bVec = _mm_loadu_ps(b);
		InVectf tempV = _mm_cmpeq_ps(aVec, bVec);
		int comp = 0xFFFFFFFF;
		return (_mm_extract_ps(tempV, 0) == comp && _mm_extract_ps(tempV, 1) == comp &&
			_mm_extract_ps(tempV, 2) == comp && _mm_extract_ps(tempV, 3) == comp);


	}

	template<typename T>
	inline T dot4(const T* a, const T* b) {
		return 0;
	}

	template<> inline float dot4<float>(const float* af, const float* bf) {
		InVectf a = _mm_loadu_ps(af);
		InVectf b = _mm_loadu_ps(bf);

		InVectf r = _mm_mul_ps(a, b);
		a = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 1, 0, 0));
		b = _mm_add_ps(a, r);
		a = _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 2, 2, 2));
		b = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 3, 3, 3));
		r = _mm_add_ps(a, b);
		return _mm_cvtss_f32(r);

	}

	template<> inline double dot4<double>(const double* af, const double* bf) {
		InVectd aVect = _mm256_load_pd(af);
		InVectd bVect = _mm256_load_pd(bf);

		aVect = _mm256_mul_pd(aVect, bVect);
		bVect = _mm256_permutex_pd(aVect, _MM_PERM_ENUM::_MM_PERM_ABCD);
		aVect = _mm256_add_pd(aVect, bVect);
		bVect = _mm256_permute_pd(aVect, 0x1);
		aVect = _mm256_add_pd(aVect, bVect);
		return _mm256_cvtsd_f64(aVect);
	}

	template<typename T>
	inline T _dot3(const T* a, const T* b) {

		return 0;
	}

	template<> inline float _dot3<float>(const float* a, const float* b) {
		InVectf aVect = loadVector3(a);
		InVectf bVect = loadVector3(b);
		aVect = _mm_mul_ps(aVect, bVect);
		InVectf temp = _mm_shuffle_ps(aVect, aVect, _MM_SHUFFLE(1, 1, 1, 1));
		bVect = _mm_shuffle_ps(aVect, aVect, _MM_SHUFFLE(2, 2, 2, 2));
		aVect = _mm_add_ps(temp, aVect);
		aVect = _mm_add_ps(bVect, aVect);
		return _mm_cvtss_f32(aVect);



	}

	template<> inline double _dot3<double>(const double* a, const double* b) {
		InVectd aVect = loadVector3(a);
		InVectd bVect = loadVector3(b);

		aVect = _mm256_mul_pd(aVect, bVect);
		bVect = _mm256_permutex_pd(aVect, _MM_PERM_ENUM::_MM_PERM_ABCC);
		bVect = _mm256_add_pd(aVect, bVect);
		aVect = _mm256_permute_pd(aVect, 0x1);
		aVect = _mm256_add_pd(aVect, bVect);
		return _mm256_cvtsd_f64(aVect);
	}
	//cross 4 is for Vector4
	template<typename T>
	inline void cross4(const T* a, const T* b, T* r) {
		return;
	}
	//todo do we need to blank out w?
	template<> inline void cross4<float>(const float* af, const float* bf, float* r) {
		InVectf a = _mm_loadu_ps(af);
		InVectf b = _mm_loadu_ps(bf);

		InVectf temp1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
		InVectf temp2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
		temp1 = _mm_mul_ps(temp1, temp2);

		InVectf temp3 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
		InVectf temp4 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
		temp3 = _mm_mul_ps(temp3, temp4);


		temp3 = _mm_sub_ps(temp1, temp3);
		_mm_store_ps(r, temp3);
	}

	template<> inline void cross4<double>(const double* af, const double* bf, double* r) {
		InVectd aVect = _mm256_load_pd(af);
		InVectd bVect = _mm256_load_pd(bf);

		InVectd perm1 = _mm256_permutex_pd(aVect, _MM_PERM_ENUM::_MM_PERM_DACB);
		InVectd perm2 = _mm256_permutex_pd(bVect, _MM_PERM_ENUM::_MM_PERM_DBAC);
		perm1 = _mm256_mul_pd(perm1, perm2);

		perm2 = _mm256_permutex_pd(aVect, _MM_PERM_ENUM::_MM_PERM_DBAC);
		InVectd perm3 = _mm256_permutex_pd(bVect, _MM_PERM_ENUM::_MM_PERM_DACB);
		perm2 = _mm256_mul_pd(perm2, perm3);

		perm1 = _mm256_sub_pd(perm1, perm2);
		_mm256_store_pd(r, perm1);
	}

	template<typename T>
	inline void cross3(const T* a, const T* b, T* r) {
		return;
	}

	template<typename T>
	inline void scalarDiv4(T* d, T scalar) {
		return;
	}

	template <> inline void scalarDiv4<float>(float* d, float s) {
		InVectf b = _mm_set_ps(s, s, s, s);
		InVectf a = _mm_loadu_ps(d);
		a = _mm_div_ps(a, b);
		_mm_store_ps(d, a);

	}

	template <> inline void scalarDiv4<double>(double* d, double s) {
		InVectd b = _mm256_set_pd(s, s, s, s);
		InVectd a = _mm256_loadu_pd(d);
		a = _mm256_div_pd(a, b);
		_mm256_store_pd(d, a);
	}

	template<typename T>
	inline void scalarMul4(T* d, T scalar) {
		return;
	}

	template <> inline void scalarMul4<float>(float* d, float s) {
		InVectf b = _mm_set_ps(s, s, s, s);
		InVectf a = _mm_loadu_ps(d);
		a = _mm_mul_ps(a, b);
		_mm_store_ps(d, a);

	}

	template <> inline void scalarMul4<double>(double* d, double s) {
		InVectd b = _mm256_set_pd(s, s, s, s);
		InVectd a = _mm256_loadu_pd(d);
		a = _mm256_mul_pd(a, b);
		_mm256_store_pd(d, a);
	}

	template<typename T>
	inline void normalize43(T* d) {
		return;
	}

	template<> inline void normalize43<float>(float* data) {
		InVectf a = _mm_loadu_ps(data);
		float d3 = _dot3<float>(data, data);
		InVectf rs = _mm_rsqrt_ps(_mm_set_ps(d3, d3, d3, 1.f));
		_mm_store_ps(data, _mm_mul_ps(a, rs));

	}

	template<> inline void normalize43<double>(double* data) {
		InVectd a = _mm256_loadu_pd(data);
		double d3 = _dot3<double>(data, data);
		InVectd rs = _mm256_sqrt_pd(_mm256_set_pd(d3, d3, d3, 1.0));

		rs = _mm256_div_pd(_mm256_set1_pd(1.0), rs);
		_mm256_store_pd(data, _mm256_mul_pd(a, rs));

	}

	template<typename T>
	inline void normalize4(T* d) {
		return;
	}
	

	template <> inline void normalize4<float>(float* data) {
		InVectf a = _mm_loadu_ps(data);
		float d3 = dot4<float>(data, data);
		InVectf rs = _mm_rsqrt_ps(_mm_set_ps(d3, d3, d3, d3));
		_mm_store_ps(data, _mm_mul_ps(a, rs));
	}

	template <> inline void normalize4<double>(double* data) {
		InVectd a = _mm256_loadu_pd(data);
		double d3 = dot4<double>(data, data);
		InVectd rs = _mm256_sqrt_pd(_mm256_set_pd(d3, d3, d3, d3));

		rs = _mm256_div_pd(_mm256_set1_pd(1.0), rs);
		_mm256_store_pd(data, _mm256_mul_pd(a, rs));
	}

	template<typename T>
	inline T scalarMul(T s1, T s2) {
		return 0.0;
	}

	template <> inline float scalarMul<float>(float s1, float s2) {
		InVectf a = _mm_set_ps1(s1);
		InVectf b = _mm_set_ps1(s2);
		a = _mm_mul_ps(a, b);
		_mm_store_ps1(&s1, a);
		return s1;
	}

	template <> inline double scalarMul<double>(double s1, double s2) {
		InVectd a = _mm256_set1_pd(s1);
		InVectd b = _mm256_set1_pd(s2);
		a = _mm256_mul_pd(a, b);
		return _mm256_cvtsd_f64(a);

	}

	template<typename T>
	inline T scalarDiv(T s1, T s2) {
		return 0.0;
	}
	template <> inline float scalarDiv(float s1, float s2) {
		InVectf a = _mm_set_ps1(s1);
		InVectf b = _mm_set_ps1(s2);
		a = _mm_div_ps(a, b);
		_mm_store_ps1(&s1, a);
		return s1;
	}

	template <> inline double scalarDiv(double s1, double s2) {
		InVectd a = _mm256_set1_pd(s1);
		InVectd b = _mm256_set1_pd(s2);
		a = _mm256_div_pd(a, b);
		return _mm256_cvtsd_f64(a);

	}

	inline void cross3(InVectf& a, InVectf& b, InVectf& out) {


		InVectf temp1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
		InVectf temp2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
		temp1 = _mm_mul_ps(temp1, temp2);


		InVectf temp3 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
		InVectf temp4 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
		temp3 = _mm_mul_ps(temp3, temp4);


		out = _mm_sub_ps(temp1, temp3);

	}

	template<typename T>
	inline void store4(T* a, T* b) {

		return;
	}

	//store a in b
	template<> inline void store4<float>(float* a, float* b) {
		InVectf aVect = _mm_loadu_ps(a);
		_mm_store_ps(b, aVect);
	}

	//store a in b
	template<> inline void store4<double>(double* a, double* b) {
		InVectd aVect = _mm256_loadu_pd(a);
		_mm256_store_pd(b, aVect);
	}


}

