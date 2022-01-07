#include "OdinMath.h"
namespace OdinMath {
	
	template <> void tquatfRotAxis<float>(float angle, float* axis, float* result)
	{
		InVectf v = _mm_set1_ps(angle);
		v = _mm_mul_ps(v, _mm_set1_ps(1.f / 2));
		InVectf c = _mm_cos_ps(v);
		InVectf s = _mm_sin_ps(v);

		//normalize axis
		InVectf a = loadVector3(axis);
		InVectf r;
		dotVect3(a, a, r);
		InVectf rs = _mm_rsqrt_ps(r);
		a = _mm_mul_ps(a, rs);

		c = _mm_shuffle_ps(s, c, _MM_SHUFFLE(0, 0, 0, 0));
		InVectf ang = _mm_shuffle_ps(s, c, _MM_SHUFFLE(3, 0, 0, 0));

		InVectf unit = _mm_set_ss(1.f);
		unit = _mm_shuffle_ps(unit, a, _MM_SHUFFLE(2, 2, 0, 0));
		a = _mm_shuffle_ps(a, unit, _MM_SHUFFLE(0, 2, 1, 0));

		a = _mm_mul_ps(a, ang);
		_mm_store_ps(result, a);
		


	}

	template <> void tquatfRotAxis<double>(double angle, double* axis, double* result)
	{
		InVectd v = _mm256_set1_pd(angle);
		v = _mm256_mul_pd(v, _mm256_set1_pd(1.0 / 2));
		InVectd c = _mm256_cos_pd(v);
		InVectd s = _mm256_sin_pd(v);

		//normalize axis
		InVectd a = loadVector3(axis);
		InVectd r;
		dotVect3(a, a, r);
		InVectd rs = _mm256_sqrt_pd(r);
		a = _mm256_div_pd(a, rs);

		c = _mm256_shuffle_pd(s, c, 0x0);
		__m128d tmp = _mm256_extractf128_pd(c, 0x0);
		InVectd ang = _mm256_insertf128_pd(s, tmp, 0x1);

		InVectd unit = _mm256_set1_pd(1.0);
		unit = _mm256_shuffle_pd(a, unit, 0x0);
		tmp = _mm256_extractf128_pd(unit, 0x1);
		a = _mm256_insertf128_pd(a, tmp, 0x1);
		a = _mm256_mul_pd(a, ang);
		_mm256_store_pd(result, a);


	}

	template <> void tquatfRotMat<float, 4>(float M[][4], float* data)
	{
		InMatrix4F A(M);
		InVectf out;
		tquatfRotMatf(A, out);
		_mm_store_ps(data, out);

		
	}

	template<> void tquatfRotMat<double, 4>(double M[][4], double* data)
	{
		InMatrix4D A(M);
		InVectd out;
		tquatfRotMatd(A, out);
		_mm256_store_pd(data, out);

		
	}

	template <> void tquatfRotMat<float, 3>(float M[][3], float* data)
	{
		InMatrix4F A(M);
		InVectf out;
		tquatfRotMatf(A, out);
		_mm_store_ps(data, out);


	}

	template<> void tquatfRotMat<double, 3>(double M[][3], double* data)
	{
		InMatrix4D A(M);
		InVectd out;
		tquatfRotMatd(A, out);
		storeVector3(data, out);


	}

	
	void tquatfRotMatf(InMatrix4F& A, InVectf& out)
	{
		InVectf ones = _mm_set_ps1(1.0f);
		InVectf zeroes = _mm_set_ps1(0.f);

		InVectf xx = PERMUTE_PS(A.row[0], _MM_SHUFFLE(0, 0, 0, 0));
		InVectf yy = PERMUTE_PS(A.row[1], _MM_SHUFFLE(1, 1, 1, 1));
		InVectf zz = PERMUTE_PS(A.row[2], _MM_SHUFFLE(2, 2, 2, 2));

		InVectf m01 = PERMUTE_PS(A.row[0], _MM_SHUFFLE(1, 1, 1, 1));
		InVectf m10 = PERMUTE_PS(A.row[1], _MM_SHUFFLE(0, 0, 0, 0));
		InVectf m20 = PERMUTE_PS(A.row[2], _MM_SHUFFLE(0, 0, 0, 0));
		InVectf m02 = PERMUTE_PS(A.row[0], _MM_SHUFFLE(2, 2, 2, 2));
		InVectf m12 = PERMUTE_PS(A.row[1], _MM_SHUFFLE(2, 2, 2, 2));
		InVectf m21 = PERMUTE_PS(A.row[2], _MM_SHUFFLE(1, 1, 1, 1));

		InVectf pnnp = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);
		InVectf npnp = _mm_setr_ps(-1.f, 1.f, -1.f, 1.f);
		InVectf nnpp = _mm_setr_ps(-1.f, -1.f, 1.f, 1.f);


		InVectf t0 = _mm_shuffle_ps(m01, m20, _MM_SHUFFLE(0, 0, 0, 0));
		InVectf t1 = _mm_shuffle_ps(m10, m02, _MM_SHUFFLE(0, 0, 0, 0));
		t1 = _mm_mul_ps(npnp, t1);

		//m01 - m10, m01 + m10, m20 - m02, m20 + m02 
		t0 = _mm_add_ps(t0, t1);

		//m12 - m21, m12 - m21, m12 + m21, m12 + m21 
		t1 = _mm_mul_ps(nnpp, m21);
		t1 = _mm_add_ps(m12, t1);
		InVectf t2;


		InVectf t = _mm_add_ps(ones, _mm_mul_ps(pnnp, xx));
		t = _mm_add_ps(t, _mm_mul_ps(npnp, yy));
		t = _mm_add_ps(t, _mm_mul_ps(nnpp, zz));

		InVectf one = _mm_shuffle_ps(t, t1, _MM_SHUFFLE(0, 0, 0, 0));
		one = _mm_shuffle_ps(one, t0, _MM_SHUFFLE(3, 1, 3, 0));
		one = PERMUTE_PS(one, _MM_SHUFFLE(1, 3, 2, 0));

		InVectf two = _mm_shuffle_ps(t, t1, _MM_SHUFFLE(2, 2, 1, 1));
		two = _mm_shuffle_ps(two, t0, _MM_SHUFFLE(1, 2, 3, 0));
		two = PERMUTE_PS(two, _MM_SHUFFLE(2, 1, 0, 3));

		InVectf three = _mm_shuffle_ps(t, t1, _MM_SHUFFLE(3, 3, 2, 2));
		three = _mm_shuffle_ps(three, t0, _MM_SHUFFLE(3, 0, 3, 0));
		three = PERMUTE_PS(three, _MM_SHUFFLE(2, 0, 1, 3));

		InVectf four = _mm_shuffle_ps(t, t1, _MM_SHUFFLE(0, 0, 3, 3));
		four = _mm_shuffle_ps(four, t0, _MM_SHUFFLE(0, 2, 3, 0));
		four = PERMUTE_PS(four, _MM_SHUFFLE(0, 3, 2, 1));

		InVectf tmp = _mm_add_ps(_mm_mul_ps(nnpp, xx), yy);

		InVectf first = _mm_cmple_ps(zz, zeroes);
		InVectf second = _mm_cmple_ps(PERMUTE_PS(tmp, _MM_SHUFFLE(0, 0, 0, 0)), zeroes);
		InVectf third = _mm_cmple_ps(PERMUTE_PS(tmp, _MM_SHUFFLE(3, 3, 3, 3)), zeroes);

		t0 = _mm_and_ps(second, one);
		t1 = _mm_andnot_ps(second, two);
		t0 = _mm_or_ps(t0, t1);
		t1 = _mm_and_ps(third, three);
		t2 = _mm_andnot_ps(third, four);
		t1 = _mm_or_ps(t1, t2);
		t0 = _mm_and_ps(first, t0);
		t1 = _mm_andnot_ps(first, t1);
		t0 = _mm_or_ps(t0, t1);

		length4f(t0, t1);
		out = _mm_div_ps(t0, t1);
	}

	void tquatfRotMatd(InMatrix4D& A, InVectd& out)
	{
		InVectd ones = _mm256_set1_pd(1.0);
		InVectd zeroes = _mm256_set1_pd(0.0);

		InVectd xx = _mm256_permutex_pd(A.row[0], _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd yy = _mm256_permutex_pd(A.row[1], _MM_PERM_ENUM::_MM_PERM_BBBB);
		InVectd zz = _mm256_permutex_pd(A.row[2], _MM_PERM_ENUM::_MM_PERM_CCCC);

		InVectd m01 = _mm256_permutex_pd(A.row[0], _MM_PERM_ENUM::_MM_PERM_BBBB);
		InVectd m10 = _mm256_permutex_pd(A.row[1], _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd m20 = _mm256_permutex_pd(A.row[2], _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd m02 = _mm256_permutex_pd(A.row[0], _MM_PERM_ENUM::_MM_PERM_CCCC);
		InVectd m12 = _mm256_permutex_pd(A.row[1], _MM_PERM_ENUM::_MM_PERM_CCCC);
		InVectd m21 = _mm256_permutex_pd(A.row[2], _MM_PERM_ENUM::_MM_PERM_BBBB);

		InVectd pnnp = _mm256_setr_pd(1.0, -1.0, -1.0, 1.0);
		InVectd npnp = _mm256_setr_pd(-1.0, 1.0, -1.0, 1.0);
		InVectd nnpp = _mm256_setr_pd(-1.0, -1.0, 1.0, 1.0);


		InVectd t0 = _mm256_shuffle_pd(m01, m20, 0x0);
		InVectd t1 = _mm256_shuffle_pd(m10, m02, 0x0);
		t1 = _mm256_mul_pd(nnpp, t1);

		//m01 - m10, m20 - m02, m01 + m10, m20 + m02 
		t0 = _mm256_add_pd(t0, t1);

		//m12 - m21, m12 - m21, m12 + m21, m12 + m21 
		t1 = _mm256_mul_pd(nnpp, m21);
		t1 = _mm256_add_pd(m12, t1);
		InVectd t2;


		InVectd t = _mm256_add_pd(ones, _mm256_mul_pd(pnnp, xx));
		t = _mm256_add_pd(t, _mm256_mul_pd(npnp, yy));
		t = _mm256_add_pd(t, _mm256_mul_pd(nnpp, zz));

		//t0, m12 - m21, ...
		InVectd one = _mm256_shuffle_pd(t, t1, 0x0);
		one = _mm256_permutex_pd(one, _MM_PERM_ENUM::_MM_PERM_BBAA);
		InVectd tmp0 = _mm256_permutex_pd(t0, _MM_PERM_ENUM::_MM_PERM_DDCC);
		//t0, m01 + m10, m12 - m21, m20 + m02
		one = _mm256_shuffle_pd(one, tmp0, 0x0);
		one = _mm256_permutex_pd(one, _MM_PERM_ENUM::_MM_PERM_CDBA);

		//t1, ..., ..., m12 + m21
		InVectd two = _mm256_shuffle_pd(t, t1, 0x1);
		two = _mm256_shuffle_pd(two, t0, 0x6);
		//t1, m20 - m02,  m12 + m21, m01 + m10
		two = _mm256_permutex_pd(two, _MM_PERM_ENUM::_MM_PERM_BCAD);

		//..., ..., t2,   m12 + m21
		InVectd three = _mm256_shuffle_pd(t, t1, 0x4);
		//t2, t2, m12 + m21, m12 + m21
		three = _mm256_permutex_pd(three, _MM_PERM_ENUM::_MM_PERM_DDCC);
		//t2, m01 - m10, m12 + m21,  m20 + m02 
		three = _mm256_shuffle_pd(three, t0, 0x8);
		three = _mm256_permutex_pd(three, _MM_PERM_ENUM::_MM_PERM_BACD);

		//..., m12 - m21, t3, ...
		InVectd four = _mm256_shuffle_pd(t, t1, 0x4);
		// m20 - m02,  m20 - m02, m01 - m10, m01 - m10
		tmp0 = _mm256_permutex_pd(t0, _MM_PERM_ENUM::_MM_PERM_AABB);

		//m12 - m21,  m20 - m02, t3,  m01 - m10
		four = _mm256_shuffle_pd(four, tmp0, 0x1);
		four = _mm256_permutex_pd(four, _MM_PERM_ENUM::_MM_PERM_CDBA);

		InVectd tmp = _mm256_add_pd(_mm256_mul_pd(nnpp, xx), yy);

		InVectd first = _mm256_cmp_pd(zz, zeroes, 0x2);
		InVectd second = _mm256_cmp_pd(_mm256_permutex_pd(tmp, _MM_PERM_ENUM::_MM_PERM_AAAA), zeroes, 0x2);
		InVectd third = _mm256_cmp_pd(_mm256_permutex_pd(tmp, _MM_PERM_ENUM::_MM_PERM_DDDD), zeroes, 0x2);

		t0 = _mm256_and_pd(second, one);
		t1 = _mm256_andnot_pd(second, two);
		t0 = _mm256_or_pd(t0, t1);
		t1 = _mm256_and_pd(third, three);
		t2 = _mm256_andnot_pd(third, four);
		t1 = _mm256_or_pd(t1, t2);
		t0 = _mm256_and_pd(first, t0);
		t1 = _mm256_andnot_pd(first, t1);
		t0 = _mm256_or_pd(t0, t1);

		length4d(t0, t1);
		out = _mm256_div_pd(t0, t1);
	}

	void trotMatfQuatf(InVectf& q, InMatrix4F& out)
	{
		InVectf x = PERMUTE_PS(q, _MM_SHUFFLE(0, 0, 0, 0));
		InVectf y = PERMUTE_PS(q, _MM_SHUFFLE(1, 1, 1, 1));
		InVectf z = PERMUTE_PS(q, _MM_SHUFFLE(2, 2, 2, 2));

		InVectf twos = _mm_set_ps(2.f, 2.f, 2.f, 2.f);
		InVectf zeroes = _mm_set_ps(0.0f, 0.f, 0.f, 0.f);

		InVectf nppz = _mm_setr_ps(-1.f, 1.f, 1.f, 0.0f);
		InVectf npnz = _mm_setr_ps(-1.f, 1.f, -1.f, 0.0f);
		InVectf pnpz = _mm_setr_ps(1.f, -1.f, 1.f, 0.f);
		InVectf nnpz = _mm_setr_ps(-1.f, -1.f, 1.f, 0.0f);
		InVectf ppnz = _mm_setr_ps(1.f, 1.f, -1.f, 0.0f);
		InVectf pnnz = _mm_setr_ps(1.f, -1.f, -1.f, 0.f);


		InVectf xxyzw2 = _mm_mul_ps(twos, _mm_mul_ps(x, q));
		InVectf yxyzw2 = _mm_mul_ps(twos, _mm_mul_ps(y, q));
		InVectf zxyzw2 = _mm_mul_ps(twos, _mm_mul_ps(z, q));

		InVectf row = _mm_setr_ps(1.f, 0.f, 0.f, 0.f);
		InVectf tmp0 = _mm_shuffle_ps(yxyzw2, xxyzw2, _MM_SHUFFLE(2, 2, 0, 1));
		
		row = _mm_add_ps(_mm_mul_ps(nppz, tmp0), row);
		tmp0 = _mm_shuffle_ps(zxyzw2, yxyzw2, _MM_SHUFFLE(3, 3, 3, 2));
		out.row[0] = _mm_add_ps(_mm_mul_ps(npnz, tmp0), row);

		row = _mm_setr_ps(0.f, 1.f, 0.f, 0.f);
		tmp0 = _mm_shuffle_ps(xxyzw2, yxyzw2, _MM_SHUFFLE(2, 2, 0, 1));
		row = _mm_add_ps(row, _mm_mul_ps(pnpz, tmp0));

		tmp0 = _mm_shuffle_ps(zxyzw2, xxyzw2, _MM_SHUFFLE(3, 3, 2, 3));
		out.row[1] = _mm_add_ps(_mm_mul_ps(tmp0, nnpz), row);

		row = _mm_setr_ps(0.f, 0.f, 1.f, 0.f);
		tmp0 = _mm_shuffle_ps(zxyzw2, xxyzw2, _MM_SHUFFLE(0, 0, 1, 0));
		row = _mm_add_ps(row, _mm_mul_ps(ppnz, tmp0));

		tmp0 = _mm_shuffle_ps(yxyzw2, xxyzw2, _MM_SHUFFLE(3, 3, 3, 1));
		tmp0 = PERMUTE_PS(tmp0, _MM_SHUFFLE(0, 0, 2, 1));
		out.row[2] = _mm_add_ps(row, _mm_mul_ps(pnnz, tmp0));

		out.row[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);



	}

	void trotMatfQuatd(InVectd& q, InMatrix4D& out)
	{
		InVectd x = _mm256_permutex_pd(q, _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd y = _mm256_permutex_pd(q, _MM_PERM_ENUM::_MM_PERM_BBBB);
		InVectd z = _mm256_permutex_pd(q, _MM_PERM_ENUM::_MM_PERM_CCCC);

		InVectd twos = _mm256_set_pd(2.0, 2.0, 2.0, 2.f);
		InVectd zeroes = _mm256_set_pd(0.0f, 0.f, 0.f, 0.f);

		InVectd nppz = _mm256_setr_pd(-1.f, 1.f, 1.f, 0.0f);
		InVectd npnz = _mm256_setr_pd(-1.f, 1.f, -1.f, 0.0f);
		InVectd pnpz = _mm256_setr_pd(1.f, -1.f, 1.f, 0.f);
		InVectd nnpz = _mm256_setr_pd(-1.f, -1.f, 1.f, 0.0f);
		InVectd ppnz = _mm256_setr_pd(1.f, 1.f, -1.f, 0.0f);
		InVectd pnnz = _mm256_setr_pd(1.f, -1.f, -1.f, 0.f);


		InVectd xxyzw2 = _mm256_mul_pd(twos, _mm256_mul_pd(x, q));
		InVectd yxyzw2 = _mm256_mul_pd(twos, _mm256_mul_pd(y, q));
		InVectd zxyzw2 = _mm256_mul_pd(twos, _mm256_mul_pd(z, q));

		InVectd row = _mm256_setr_pd(1.f, 0.f, 0.f, 0.f);
		__m128d tmp = _mm256_extractf128_pd(yxyzw2, 0x0);
		tmp = _mm_shuffle_pd(tmp, tmp, 0x1);
		InVectd tmp0 = _mm256_insertf128_pd(xxyzw2, tmp, 0x0);

		row = _mm256_add_pd(_mm256_mul_pd(nppz, tmp0), row);
		tmp = _mm256_extractf128_pd(zxyzw2, 0x1);
		tmp0 = _mm256_insertf128_pd(yxyzw2, tmp, 0x0);
		tmp0 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_DDBA);

		out.row[0] = _mm256_add_pd(_mm256_mul_pd(npnz, tmp0), row);

		row = _mm256_setr_pd(0.f, 1.f, 0.f, 0.f);
		tmp = _mm256_extractf128_pd(xxyzw2, 0x0);
		tmp = _mm_shuffle_pd(tmp, tmp, 0x1);
		tmp0 = _mm256_insertf128_pd(yxyzw2, tmp, 0x0);
		row = _mm256_add_pd(row, _mm256_mul_pd(pnpz, tmp0));

		tmp = _mm256_extractf128_pd(zxyzw2, 0x1);
		tmp = _mm_shuffle_pd(tmp, tmp, 0x1);
		tmp0 = _mm256_insertf128_pd(xxyzw2, tmp, 0x0);
		tmp0 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_DDBA);
		out.row[1] = _mm256_add_pd(_mm256_mul_pd(tmp0, nnpz), row);

		row = _mm256_setr_pd(0.f, 0.f, 1.f, 0.f);
		tmp = _mm256_extractf128_pd(zxyzw2, 0x0);
		tmp0 = _mm256_insertf128_pd(xxyzw2, tmp, 0x1);
		tmp0 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_AADC);
		row = _mm256_add_pd(row, _mm256_mul_pd(ppnz, tmp0));

		tmp0 = _mm256_shuffle_pd(yxyzw2, xxyzw2, 0xf);
		tmp0 = _mm256_permutex_pd(tmp0, _MM_PERM_ENUM::_MM_PERM_AADC);
		out.row[2] = _mm256_add_pd(row, _mm256_mul_pd(pnnz, tmp0));

		out.row[3] = _mm256_setr_pd(0.f, 0.f, 0.f, 1.f);
	}

	void tquatfEulerf(InVectf& v, InVectf& q)
	{
		v = _mm_div_ps(v, _mm_set_ps1(2.f));
		InVectf c = _mm_cos_ps(v);
		InVectf s = _mm_sin_ps(v);

		//roll
		InVectf tmp0 = _mm_shuffle_ps(c, s, _MM_SHUFFLE(0, 0, 0, 0));
		//pitch
		InVectf tmp1 = _mm_shuffle_ps(c, s, _MM_SHUFFLE(1, 1, 1, 1));
		//yaw
		InVectf tmp2 = _mm_shuffle_ps(c, s, _MM_SHUFFLE(2, 2, 2, 2));


		
		InVectf t1 = _mm_shuffle_ps(tmp0, c, _MM_SHUFFLE(0, 0, 0, 3));
		InVectf t2 = _mm_shuffle_ps(tmp1, c, _MM_SHUFFLE(1, 1, 3, 0));
		InVectf t3 = _mm_shuffle_ps(c, tmp2, _MM_SHUFFLE(0, 3, 2, 2));

		InVectf tmp = _mm_mul_ps(t1, t2);
		tmp = _mm_mul_ps(tmp, t3);

		t1 = _mm_shuffle_ps(tmp0, s, _MM_SHUFFLE(0, 0, 3, 0));
		t2 = _mm_shuffle_ps(tmp1, s, _MM_SHUFFLE(1, 1, 0, 3));
		t3 = _mm_shuffle_ps(s, tmp2, _MM_SHUFFLE(3, 0, 2, 2));


		t1 = _mm_mul_ps(t1, t2);
		t1 = _mm_mul_ps(t1, t3);

		t2 = _mm_setr_ps(-1.f, 1.0f, -1.0f, 1.0f);
		t1 = _mm_mul_ps(t1, t2);

		q = _mm_add_ps(tmp, t1);


	}

	void tquatfEulerd(InVectd& v, InVectd& q)
	{
		v = _mm256_div_pd(v, _mm256_set1_pd(2.f));
		InVectd c = _mm256_cos_pd(v);
		InVectd s = _mm256_sin_pd(v);

		InVectd cc0 = _mm256_permutex_pd(c, _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd cc1 = _mm256_permutex_pd(c, _MM_PERM_ENUM::_MM_PERM_BBBB);
		InVectd cc2 = _mm256_permutex_pd(c, _MM_PERM_ENUM::_MM_PERM_CCCC);

		InVectd ss0 = _mm256_permutex_pd(s, _MM_PERM_ENUM::_MM_PERM_AAAA);
		InVectd ss1 = _mm256_permutex_pd(s, _MM_PERM_ENUM::_MM_PERM_BBBB);
		InVectd ss2 = _mm256_permutex_pd(s, _MM_PERM_ENUM::_MM_PERM_CCCC);


		//c roll s roll c yaw s yaw
		InVectd tmp0 = _mm256_shuffle_pd(c, s, 0x0);
		//c pitch s roll ... empty
 		InVectd tmp1 = _mm256_shuffle_pd(c, s, 0xf);

		//c roll s roll
		__m128d tmp00 = _mm256_extractf128_pd(tmp0, 0x0);
		//c yaw s yaw
		__m128d tmp11 = _mm256_extractf128_pd(tmp0, 0x1);
		//c pitch s pitch
		__m128d tmp22 = _mm256_extractf128_pd(tmp1, 0x0);

		InVectd t1 = _mm256_insertf128_pd(cc0, _mm_shuffle_pd(tmp00, tmp00, 1), 0x0);
		InVectd t2 = _mm256_insertf128_pd(cc1, tmp22, 0x0);
		InVectd t3 = _mm256_insertf128_pd(cc2, _mm_shuffle_pd(tmp11, tmp11, 1), 0x1);

		InVectd tmp = _mm256_mul_pd(t1, t2);
		tmp = _mm256_mul_pd(tmp, t3);

		t1 = _mm256_insertf128_pd(ss0, tmp00, 0x0);
		t2 = _mm256_insertf128_pd(ss1, _mm_shuffle_pd(tmp22, tmp22, 0x1), 0x0);
		t3 = _mm256_insertf128_pd(ss2, tmp11, 0x1);


		t1 = _mm256_mul_pd(t1, t2);
		t1 = _mm256_mul_pd(t1, t3);

		t2 = _mm256_setr_pd(-1.f, 1.0f, -1.0f, 1.0f);
		t1 = _mm256_mul_pd(t1, t2);

		q = _mm256_add_pd(tmp, t1);
	}


	
	template<> void trotMatfQuat<float, 4>(float* data, float M[][4])
	{
		InVectf v = _mm_load_ps(data);
		InMatrix4F A;
		trotMatfQuatf(v, A);
		storeMat4(A, M);
	}

	template<> void trotMatfQuat<double, 4>(double* data, double M[][4]) {
		InVectd v = _mm256_load_pd(data);
		InMatrix4D A;
		trotMatfQuatd(v, A);
		storeMat4(A, M);
	}

	template<> void tquatfEuler<float>(float roll, float pitch, float yaw, float* data) {
		InVectf v = _mm_setr_ps(roll, pitch, yaw, 0.f);
		InVectf q;
		tquatfEulerf(v, q);
		_mm_store_ps(data, q);
	}

	template<> void tquatfEuler<double>(double roll, double pitch, double yaw, double* data) {
		InVectd v = _mm256_setr_pd(roll, pitch, yaw, 0.f);
		InVectd q;
		tquatfEulerd(v, q);
		_mm256_store_pd(data, q);
	}


	template<> void tEulerfQuat<float>(float* data, float* rpy) {
		InVectf v = _mm_load_ps(data);
		InVectf t0 = PERMUTE_PS(v, _MM_SHUFFLE(3, 3, 3, 3));
		InVectf t1 = PERMUTE_PS(v, _MM_SHUFFLE(3, 2, 1, 0));
		InVectf t2 = PERMUTE_PS(v, _MM_SHUFFLE(3, 0, 2, 1));
		InVectf t3 = PERMUTE_PS(v, _MM_SHUFFLE(3, 1, 0, 2));

		InVectf tt = _mm_set_ps1(2.f);
		t0 = _mm_mul_ps(t0, tt);
		t0 = _mm_mul_ps(t0, t1);

		t1 = _mm_mul_ps(tt, t2);
		t1 = _mm_mul_ps(t1, t3);

		t2 = _mm_setr_ps(1.f, -1.0, 1.f, 1.0f);
		t1 = _mm_mul_ps(t1, t2);
		t0 = _mm_add_ps(t1, t0);

		
		InVectf tt0 = _mm_set_ps1(1.0f);

		InVectf tt1 = _mm_mul_ps(v, v);
		tt1 = _mm_mul_ps(tt1, tt);


		InVectf div = _mm_sub_ps(tt0, PERMUTE_PS(tt1, _MM_SHUFFLE(1, 1, 1, 1)));
		div = _mm_sub_ps(div, PERMUTE_PS(tt1, _MM_SHUFFLE(2, 2, 2, 0)));

		t1 = _mm_atan2_ps(PERMUTE_PS(t0, _MM_SHUFFLE(2, 2, 2, 0)), div);

		_mm_store_ss(&rpy[0], t1);
		_mm_store_ss(&rpy[2], PERMUTE_PS(t1, _MM_SHUFFLE(1, 1, 1, 1)));
		_mm_store_ss(&rpy[1], _mm_asin_ps(PERMUTE_PS(t0, _MM_SHUFFLE(1, 1, 1, 1))));

	}

	template<> void tEulerfQuat<double>(double* data, double* rpy) {
		InVectd v = _mm256_load_pd(data);
		InVectd t0 = _mm256_permutex_pd(v, _MM_PERM_ENUM::_MM_PERM_DDDD);
		InVectd t1 = _mm256_permutex_pd(v, _MM_PERM_ENUM::_MM_PERM_DCBA);
		InVectd t2 = _mm256_permutex_pd(v, _MM_PERM_ENUM::_MM_PERM_AACB);
		InVectd t3 = _mm256_permutex_pd(v, _MM_PERM_ENUM::_MM_PERM_CBAC);

		InVectd tt = _mm256_set1_pd(2.0);
		t0 = _mm256_mul_pd(t0, tt);
		t0 = _mm256_mul_pd(t0, t1);

		t1 = _mm256_mul_pd(tt, t2);
		t1 = _mm256_mul_pd(t1, t3);

		t2 = _mm256_setr_pd(1.f, -1.0, 1.f, 1.0f);
		t1 = _mm256_mul_pd(t1, t2);
		t0 = _mm256_add_pd(t1, t0);


		InVectd tt0 = _mm256_set1_pd(1.0f);

		InVectd tt1 = _mm256_mul_pd(v, v);
		tt1 = _mm256_mul_pd(tt1, tt);


		InVectd div = _mm256_sub_pd(tt0, _mm256_permutex_pd(tt1, _MM_PERM_ENUM::_MM_PERM_BBBB));
		div = _mm256_sub_pd(div, _mm256_permutex_pd(tt1, _MM_PERM_ENUM::_MM_PERM_CCCA));

		t1 = _mm256_atan2_pd(_mm256_permutex_pd(t0, _MM_PERM_ENUM::_MM_PERM_CCCA), div);
		__m128d tmp = _mm256_extractf128_pd(t1, 0x0);
		__m128d tmp2 = _mm256_extractf128_pd(t0, 0x0);
		tmp2 = _mm_shuffle_pd(tmp2, tmp2, 0x3);

		_mm_store_sd(&rpy[0], tmp);
		_mm_store_sd(&rpy[2], _mm_shuffle_pd(tmp, tmp, 0x1));
		_mm_store_sd(&rpy[1], _mm_asin_pd(tmp2));

		

	}


}