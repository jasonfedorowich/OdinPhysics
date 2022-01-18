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

	/*inline InVectd loadVector3(const double* in) {
		__m128d f1 = _mm_load_pd(&(in[0]));
		__m128d f2 = _mm_load_pd(&(in[1]));
		f2 = _mm_shuffle_pd(f2, f2, _MM_SHUFFLE(0, 0, 1, 1));
		return _mm256_set_m128d(f2, f1);
	}*/

	/*inline void storeVector3(double* out, InVectd& in) {
		_mm256_storeu_pd(out, in);
	}*/
#define PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )

	inline InVectf loadVector3(const float* in) {
		InVectf t1 = _mm_load_ss(&(in[0]));
		InVectf t2 = _mm_load_ss(&(in[1]));
		InVectf t3 = _mm_load_ss(&(in[2]));
		InVectf xy = _mm_unpacklo_ps(t1, t2);
		InVectf u = _mm_set_ss(0.f);
		t3 = _mm_shuffle_ps(t3, u, _MM_SHUFFLE(3, 3, 0, 0));
		return _mm_shuffle_ps(xy, t3, _MM_SHUFFLE(3, 0, 1, 0));

	}

	inline InVectd loadVector3(const double* in) {
		__m128d t1 = _mm_load_pd(in);
		__m128d t2 = _mm_load_sd(&(in[2]));
		__m128d t3 = _mm_set_sd(0.0);
		 t3 = _mm_unpacklo_pd(t2, t3);
		return _mm256_set_m128d(t3, t1);
	}

	inline void storeVector3(float* out, InVectf& in) {
		_mm_store_ss(&(out[0]), in);
		InVectf t1 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&(out[1]), t1);
		InVectf t2 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ss(&(out[2]), t2);

	}

	inline void storeVector3(float* out, InVectf&& in) {
		_mm_store_ss(&(out[0]), in);
		InVectf t1 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&(out[1]), t1);
		InVectf t2 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ss(&(out[2]), t2);
	}

	inline void storeVector3(double* out, InVectd& in) {
		__m128d lower = _mm256_extractf128_pd(in, 0x0);
		__m128d upper = _mm256_extractf128_pd(in, 0x1);
		_mm_store_sd(&(out[0]), lower);
		lower = _mm_shuffle_pd(lower, lower, 0x3);
		_mm_store_sd(&(out[1]), lower);
		_mm_store_sd(&(out[2]), upper);
	}

	inline void storeVector3(double* out, InVectd&& in) {
		__m128d lower = _mm256_extractf128_pd(in, 0x0);
		__m128d upper = _mm256_extractf128_pd(in, 0x1);
		_mm_store_sd(&(out[0]), lower);
		lower = _mm_shuffle_pd(lower, lower, 0x3);
		_mm_store_sd(&(out[1]), lower);
		_mm_store_sd(&(out[2]), upper);
	}

	template<typename T>
	inline void store4(T* a, const T* b) {

		return;
	}

	//store a in b
	template<> inline void store4<float>(float* a, const float* b) {
		InVectf bVect = _mm_loadu_ps(b);
		_mm_store_ps(a, bVect);
	}

	//store a in b
	template<> inline void store4<double>(double* a, const double* b) {
		InVectd bVect = _mm256_loadu_pd(b);
		_mm256_store_pd(a, bVect);
	}

	template<typename T>
	inline void store3(T* out, const T* in) {
		return;
	}

	template<> inline void store3<float>(float* out, const float* b) {
		InVectf in = loadVector3(b);
		_mm_store_ss(&(out[0]), in);
		InVectf t1 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&(out[1]), t1);
		InVectf t2 = _mm_shuffle_ps(in, in, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ss(&(out[2]), t2);
	}

	template<> inline void store3<double>(double* out, const double* b) {
		InVectd in = loadVector3(b);
		__m128d lower = _mm256_extractf128_pd(in, 0x0);
		__m128d upper = _mm256_extractf128_pd(in, 0x1);
		_mm_store_sd(&(out[0]), lower);
		lower = _mm_shuffle_pd(lower, lower, 0x3);
		_mm_store_sd(&(out[1]), lower);
		_mm_store_sd(&(out[2]), upper);
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

	template<typename T>
	inline void add3(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void add3<float>(const float* a, const float* b, float* out) {
		InVectf av = loadVector3(a);
		InVectf bv = loadVector3(b);
		storeVector3(out, _mm_add_ps(av, bv));

	}

	template<> inline void add3<double>(const double* a, const double* b, double* out) {
		InVectd av = loadVector3(a);
		InVectd bv = loadVector3(b);
		storeVector3(out, _mm256_add_pd(av, bv));

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
	inline void sub3(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void sub3<float>(const float* a, const float* b, float* out) {
		InVectf av = loadVector3(a);
		InVectf bv = loadVector3(b);
		storeVector3(out, _mm_sub_ps(av, bv));
	}
	template<> inline void sub3<double>(const double* a, const double* b, double* out) {
		InVectd av = loadVector3(a);
		InVectd bv = loadVector3(b);
		storeVector3(out, _mm256_sub_pd(av, bv));
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
	inline void div3(const T* a, const T* b, T* out) {
		return;
	}

	template<> inline void div3<float>(const float* a, const float* b, float* out) {
		InVectf aVec = loadVector3(a);
		InVectf bVec = loadVector3(b);
		_mm_store_ps(out, _mm_div_ps(aVec, bVec));
	}
	template<> inline void div3<double>(const double* a, const double* b, double* out) {
		InVectd aVec = loadVector3(a);
		InVectd bVec = loadVector3(b);
		_mm256_store_pd(out, _mm256_div_pd(aVec, bVec));
	}

	inline bool equals4f(InVectf& aVec, InVectf& bVec) {
		InVectf tempV = _mm_cmpeq_ps(aVec, bVec);
		tempV = _mm_and_ps(tempV, _mm_set1_ps(1.f));
		InVectf tmp = _mm_and_ps(tempV, PERMUTE_PS(tempV, _MM_SHUFFLE(0, 1, 2, 3)));
		tmp = _mm_and_ps(tmp, PERMUTE_PS(tmp, _MM_SHUFFLE(1, 1, 1, 1)));
		__m128i ii = _mm_cvtps_epi32(tmp);
		int v = _mm_extract_epi32(ii, 0);
		return v == 1;
	}

	inline bool equals4d(InVectd& aVec, InVectd& bVec) {
		InVectd tempV = _mm256_cmp_pd(aVec, bVec, 0x0);
		InVectd temp = _mm256_and_pd(tempV, _mm256_set1_pd(1.0));
		temp = _mm256_and_pd(temp, _mm256_permutex_pd(temp, _MM_PERM_ENUM::_MM_PERM_AACD));
		temp = _mm256_and_pd(temp, _mm256_permutex_pd(temp, _MM_PERM_ENUM::_MM_PERM_BBBB));
		InVecti tmp = _mm256_cvtpd_epi32(temp);
		return _mm_extract_epi32(tmp, 0x0) == 1;

	}

	template<typename T, int N>
	inline bool equals4(const T* a, const T* b) {
		return true;
	}

	template<> inline bool equals4<double, 4>(const double* a, const double* b) {
		InVectd aVec = _mm256_loadu_pd(a);
		InVectd bVec = _mm256_loadu_pd(b);
		
		return equals4d(aVec, bVec);


	}

	template<> inline bool equals4<float, 4>(const float* a, const float* b) {
		InVectf aVec = _mm_loadu_ps(a);
		InVectf bVec = _mm_loadu_ps(b);

		return equals4f(aVec, bVec);


	}

	template<> inline bool equals4<double, 3>(const double* a, const double* b) {
		InVectd aVec = loadVector3(a);
		InVectd bVec = loadVector3(b);

		return equals4d(aVec, bVec);


	}

	template<> inline bool equals4<float, 3>(const float* a, const float* b) {
		InVectf aVec = loadVector3(a);
		InVectf bVec = loadVector3(b);

		return equals4f(aVec, bVec);


	}


	template<typename T>
	inline bool equals3(const T* a, const T* b) {
		return true;
	}

	
	template <> inline bool equals3(const float* a, const float* b) {
		InVectf aVec = loadVector3(a);
		InVectf bVec = loadVector3(b);
		InVectf tempV = _mm_cmpeq_ps(aVec, bVec);
		int comp = 0xFFFFFFFF;
		return (_mm_extract_ps(tempV, 0) == comp && _mm_extract_ps(tempV, 1) == comp &&
			_mm_extract_ps(tempV, 2) == comp);
	}

	template<> inline bool equals3<double>(const double* a, const double* b) {
		InVectd aVec = loadVector3(a);
		InVectd bVec = loadVector3(b);

		InVectd tempV = _mm256_xor_pd(aVec, bVec);
		InVecti temp = _mm256_cvtpd_epi32(tempV);
		int comp = 0;


		return (_mm_extract_epi32(temp, 0) == comp && _mm_extract_epi32(temp, 1) == comp &&
			_mm_extract_epi32(temp, 2) == comp && _mm_extract_epi32(temp, 3) == comp);


	}


	/*returns a filled vector with registers as the answer*/
	inline void dotVect3(InVectf aVect, InVectf bVect, InVectf& r) {
		aVect = _mm_mul_ps(aVect, bVect);
		InVectf temp = _mm_shuffle_ps(aVect, aVect, _MM_SHUFFLE(1, 1, 1, 1));
		bVect = _mm_shuffle_ps(aVect, aVect, _MM_SHUFFLE(2, 2, 2, 2));
		aVect = _mm_add_ps(temp, aVect);
		aVect = _mm_add_ps(bVect, aVect);
		r = _mm_shuffle_ps(aVect, aVect, _MM_SHUFFLE(0, 0, 0, 0));

	}

	inline void dotVect3(InVectd aVect, InVectd bVect, InVectd& r) {
		aVect = _mm256_mul_pd(aVect, bVect);
		bVect = _mm256_permutex_pd(aVect, _MM_PERM_ENUM::_MM_PERM_ABCC);
		bVect = _mm256_add_pd(aVect, bVect);
		aVect = _mm256_permute_pd(aVect, 0x1);
		aVect = _mm256_add_pd(aVect, bVect);
		r = _mm256_permutex_pd(aVect, 0x0);
	}

	inline void dot4f(InVectf& a, InVectf& b, InVectf& out) {
		InVectf r = _mm_mul_ps(a, b);
		InVectf aa = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 1, 0, 0));
		InVectf bb = _mm_add_ps(aa, r);
		aa = _mm_shuffle_ps(bb, bb, _MM_SHUFFLE(2, 2, 2, 2));
		bb = _mm_shuffle_ps(bb, bb, _MM_SHUFFLE(3, 3, 3, 3));
		out = _mm_add_ps(aa, bb);
		out = _mm_shuffle_ps(out, out, _MM_SHUFFLE(0, 0, 0, 0));



	}

	inline void dot4d(InVectd& a, InVectd& b, InVectd& out) {

		InVectd aa = _mm256_mul_pd(a, b);
		InVectd bb = _mm256_permutex_pd(aa, _MM_PERM_ENUM::_MM_PERM_ABCD);
		aa = _mm256_add_pd(aa, bb);
		bb = _mm256_permute_pd(aa, 0x1);
		aa = _mm256_add_pd(aa, bb);
		out = _mm256_permutex_pd(aa, _MM_PERM_ENUM::_MM_PERM_AAAA);

	}


	template<typename T>
	inline T dot4(const T* a, const T* b) {
		return 0;
	}

	template<> inline float dot4<float>(const float* af, const float* bf) {
		InVectf a = _mm_loadu_ps(af);
		InVectf b = _mm_loadu_ps(bf);
		InVectf r;
		dot4f(a, b, r);

		return _mm_cvtss_f32(r);

	}

	template<> inline double dot4<double>(const double* af, const double* bf) {
		InVectd aVect = _mm256_load_pd(af);
		InVectd bVect = _mm256_load_pd(bf);
		InVectd r;
		dot4d(aVect, bVect, r);

		return _mm256_cvtsd_f64(aVect);
	}

	inline void length4f(InVectf& v, InVectf& out) {
		dot4f(v, v, out);
		out = _mm_sqrt_ps(out);


	}

	inline void length4d(InVectd& v, InVectd& out) {
		dot4d(v, v, out);
		out = _mm256_sqrt_pd(out);


	}
	template<typename T, int N>
	inline T _dot3(const T* a, const T* b) {

		return 0;
	}

	template<> inline float _dot3<float, 4>(const float* a, const float* b) {
		InVectf r;
		InVectf aa = _mm_load_ps(a);
		InVectf bb = _mm_load_ps(b);

		dotVect3(aa, bb, r);
		return _mm_cvtss_f32(r);

	}

	template<> inline double _dot3<double, 4>(const double* a, const double* b) {
		InVectd r;
		InVectd aa = _mm256_load_pd(a);
		InVectd bb = _mm256_load_pd(b);
		dotVect3(aa, bb, r);
		return _mm256_cvtsd_f64(r);
	}

	template<> inline float _dot3<float, 3>(const float* a, const float* b) {
		InVectf r;
		InVectf aa = loadVector3(a);
		InVectf bb = loadVector3(b);

		dotVect3(aa, bb, r);
		return _mm_cvtss_f32(r);

	}

	template<> inline double _dot3<double, 3>(const double* a, const double* b) {
		InVectd r;
		InVectd aa = loadVector3(a);
		InVectd bb = loadVector3(b);
		dotVect3(aa, bb, r);
		return _mm256_cvtsd_f64(r);
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

	template<> inline void cross3<float>(const float* af, const float* bf, float* r) {
		InVectf a = loadVector3(af);
		InVectf b = loadVector3(bf);

		InVectf temp1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
		InVectf temp2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
		temp1 = _mm_mul_ps(temp1, temp2);

		InVectf temp3 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
		InVectf temp4 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
		temp3 = _mm_mul_ps(temp3, temp4);


		temp3 = _mm_sub_ps(temp1, temp3);
		storeVector3(r, temp3);
	}

	template<> inline void cross3<double>(const double* af, const double* bf, double* r) {
		InVectd aVect = loadVector3(af);
		InVectd bVect = loadVector3(bf);

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
	inline void scalarDiv4(T* d, T scalar) {
		return;
	}

	template <> inline void scalarDiv4<float>(float* d, float s) {
		InVectf b = _mm_set1_ps(s);
		b = _mm_rcp_ps(b);
		InVectf a = _mm_loadu_ps(d);
		a = _mm_mul_ps(a, b);
		_mm_store_ps(d, a);

	}

	template <> inline void scalarDiv4<double>(double* d, double s) {
		InVectd b = _mm256_set1_pd(s);
		b = _mm256_rcp14_pd(b);
		InVectd a = _mm256_loadu_pd(d);
		a = _mm256_mul_pd(a, b);
		_mm256_store_pd(d, a);
	}

	template<typename T>
	inline void scalarDiv3(T* d, T scalar) {
		return;
	}

	template<> inline void scalarDiv3<float>(float* d, float s) {
		InVectf dv = loadVector3(d);
		InVectf b = _mm_set1_ps(s);
		b = _mm_rcp_ps(b);
		storeVector3(d, _mm_mul_ps(b, dv));
	}

	template<> inline void scalarDiv3<double>(double* d, double s) {
		InVectd b = _mm256_set1_pd(s);
		b = _mm256_rcp14_pd(b);
		InVectd a = loadVector3(d);
		a = _mm256_mul_pd(a, b);
		storeVector3(d, a);

	}
	template<typename T>
	inline void scalarMul4(T* d, T scalar) {
		return;
	}

	template <> inline void scalarMul4<float>(float* d, float s) {
		InVectf b = _mm_set1_ps(s);
		InVectf a = _mm_loadu_ps(d);
		a = _mm_mul_ps(a, b);
		_mm_store_ps(d, a);

	}

	template <> inline void scalarMul4<double>(double* d, double s) {
		InVectd b = _mm256_set1_pd(s);
		InVectd a = _mm256_loadu_pd(d);
		a = _mm256_mul_pd(a, b);
		_mm256_store_pd(d, a);
	}

	template<typename T>
	inline void scalarMul3(T* d, T s) {
		return;
	}

	template<> inline void scalarMul3<float>(float* d, float s) {
		InVectf av = loadVector3(d);
		InVectf b = _mm_set1_ps(s);
		av = _mm_mul_ps(av, b);
		storeVector3(d, av);
	}
	template<> inline void scalarMul3<double>(double* d, double s) {
		InVectd av = loadVector3(d);
		InVectd b = _mm256_set1_pd(s);
		av = _mm256_mul_pd(av, b);
		storeVector3(d, av);

	}
	
	inline void normalize4d(InVectd& in, InVectd& out) {
		InVectd d;
		dot4d(in, in, d);
		d = _mm256_sqrt_pd(d);
		InVectd zeros = _mm256_set1_pd(0.0);
		InVectd mask = _mm256_cmp_pd(zeros, d, 0x4);
		out = _mm256_and_pd(mask, _mm256_div_pd(in, d));
	}

	inline void normalize4f(InVectf& in, InVectf& out) {
		InVectf d;
		dot4f(in, in, d);
		d = _mm_sqrt_ps(d);
		InVectf zeros = _mm_set1_ps(0.0f);
		InVectf mask = _mm_cmpneq_ps(zeros, d);
		out = _mm_and_ps(mask, _mm_div_ps(in, d));

	}

	template<typename T>
	inline void normalize43(T* d) {
		return;
	}

	template<> inline void normalize43<float>(float* data) {
		InVectf out;
		InVectf in = loadVector3(data);
		normalize4f(in, out);
		storeVector3(data, out);


	}

	template<> inline void normalize43<double>(double* data) {
		InVectd out;
		InVectd in = loadVector3(data);
		normalize4d(in, out);
		storeVector3(data, out);

	}

	template<typename T>
	inline void normalize4(T* d) {
		return;
	}
	

	template <> inline void normalize4<float>(float* data) {
		InVectf a = _mm_loadu_ps(data);
		InVectf out;
		normalize4f(a, out);
		_mm_store_ps(data, out);
	}

	template <> inline void normalize4<double>(double* data) {
		InVectd a = _mm256_load_pd(data);
		InVectd out;
		normalize4d(a, out);
		_mm256_store_pd(data, out);
	}

	template<typename T>
	inline void normalize33(T* data) {

		return;
	}

	template<> inline void normalize33<float>(float* data) {
		InVectf in = loadVector3(data);
		InVectf out;
		normalize4f(in, out);
		storeVector3(data, out);
	}

	template<> inline void normalize33<double>(double* data) {
		InVectd in = loadVector3(data);
		InVectd out;
		normalize4d(in, out);
		storeVector3(data, out);
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
	/*Writes r with ones if true otherwise zeros*/
	inline void cmpgtf(InVectf& a, InVectf& b, InVectf& r) {
		r = _mm_cmpgt_ps(a, b);
		r = _mm_and_ps(r, _mm_set1_ps(1.f));
	}
	inline void cmpgtd(InVectd& a, InVectd& b, InVectd& r) {
		r = _mm256_cmp_pd(a, b, 30);
		r = _mm256_and_pd(r, _mm256_set1_pd(1.f));
	}

	template<typename T, int N>
	inline void cmpgt(const T* a, const T* b, T* r) {
		return;
	}

	
	template<> inline void cmpgt<float, 4>(const float* a, const float* b, float* r) {
		InVectf aa = _mm_load_ps(a);
		InVectf bb = _mm_load_ps(b);
		InVectf rr;
		cmpgtf(aa, bb, rr);
		_mm_store_ps(r, rr);
	}
	template<> inline void cmpgt<double, 4>(const double* a, const double* b, double* r) {
		InVectd aa = _mm256_load_pd(a);
		InVectd bb = _mm256_load_pd(b);
		InVectd rr;
		cmpgtd(aa, bb, rr);
		_mm256_store_pd(r, rr);
	}

	template<> inline void cmpgt<float, 3>(const float* a, const float* b, float* r) {
		InVectf aa = loadVector3(a);
		InVectf bb = loadVector3(b);
		InVectf rr;
		cmpgtf(aa, bb, rr);
		storeVector3(r, rr);
	}
	template<> inline void cmpgt<double, 3>(const double* a, const double* b, double* r) {
		InVectd aa = loadVector3(a);
		InVectd bb = loadVector3(b);
		InVectd rr;
		cmpgtd(aa, bb, rr);
		storeVector3(r, rr);
	}

	inline void cmpgtef(InVectf& a, InVectf& b, InVectf& r) {
		r = _mm_cmpge_ps(a, b);
		r = _mm_and_ps(r, _mm_set1_ps(1.f));
	}
	inline void cmpgted(InVectd& a, InVectd& b, InVectd& r) {
		r = _mm256_cmp_pd(a, b, 29);
		r = _mm256_and_pd(r, _mm256_set1_pd(1.f));
	}

	template<typename T, int N>
	inline void cmpgte(const T* a, const T* b, T* r) {
		return;
	}


	template<> inline void cmpgte<float, 4>(const float* a, const float* b, float* r) {
		InVectf aa = _mm_load_ps(a);
		InVectf bb = _mm_load_ps(b);
		InVectf rr;
		cmpgtef(aa, bb, rr);
		_mm_store_ps(r, rr);
	}
	template<> inline void cmpgte<double, 4>(const double* a, const double* b, double* r) {
		InVectd aa = _mm256_load_pd(a);
		InVectd bb = _mm256_load_pd(b);
		InVectd rr;
		cmpgted(aa, bb, rr);
		_mm256_store_pd(r, rr);
	}

	template<> inline void cmpgte<float, 3>(const float* a, const float* b, float* r) {
		InVectf aa = loadVector3(a);
		InVectf bb = loadVector3(b);
		InVectf rr;
		cmpgtef(aa, bb, rr);
		storeVector3(r, rr);
	}
	template<> inline void cmpgte<double, 3>(const double* a, const double* b, double* r) {
		InVectd aa = loadVector3(a);
		InVectd bb = loadVector3(b);
		InVectd rr;
		cmpgted(aa, bb, rr);
		storeVector3(r, rr);
	}


	/*template<typename T>
	inline void swizzle4(T* in, const int direction, T* out) {
		return;
	}

	template<> inline void swizzle4<float>(float* in, const int dir, float* out) {
		InVectf aVect = _mm_loadu_ps(in);
		aVect = _mm_shuffle_ps(aVect, aVect, dir);
		_mm_store_ps(out, aVect);
	}

	template<> inline void swizzle4<double>(double* in, const int dir, double* out) {
		InVectd aVect = _mm256_loadu_pd(in);
		aVect = _mm256_permutex_pd(aVect, dir);
		_mm256_store_pd(out, aVect);
	}*/

}

