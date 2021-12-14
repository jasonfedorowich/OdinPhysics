#include "OdinMath.h"

namespace OdinMath {
	template <> void matScale4<float>(float A[][4], float scale, float R[][4]) {
		InMatrix4F Af(A);
		InVectf vf = _mm_load1_ps(&scale);

		InVectf row1 = _mm_mul_ps(Af.row[0], vf);
		InVectf row2 = _mm_mul_ps(Af.row[1], vf);
		InVectf row3 = _mm_mul_ps(Af.row[2], vf);
		InVectf row4 = _mm_mul_ps(Af.row[3], vf);

		_mm_store_ps(R[0], row1);
		_mm_store_ps(R[1], row2);
		_mm_store_ps(R[2], row3);
		_mm_store_ps(R[3], row4);
	}

	template <> void matScale4<double>(double A[][4], double scale, double R[][4]) {
		InMatrix4D Af(A);
		InVectd vf = _mm256_set_pd(scale, scale, scale, scale);

		InVectd row1 = _mm256_mul_pd(Af.row[0], vf);
		InVectd row2 = _mm256_mul_pd(Af.row[1], vf);
		InVectd row3 = _mm256_mul_pd(Af.row[2], vf);
		InVectd row4 = _mm256_mul_pd(Af.row[3], vf);

		_mm256_store_pd(R[0], row1);
		_mm256_store_pd(R[1], row2);
		_mm256_store_pd(R[2], row3);
		_mm256_store_pd(R[3], row4);
	}

	
	template <> void addMat4<float>(float A[][4], float B[][4], float R[][4])
	{
		InMatrix4F Af(A);
		InMatrix4F Bf(B);

		InVectf row1 = _mm_add_ps(Af.row[0], Bf.row[0]);
		InVectf row2 = _mm_add_ps(Af.row[1], Bf.row[0]);
		InVectf row3 = _mm_add_ps(Af.row[2], Bf.row[0]);
		InVectf row4 = _mm_add_ps(Af.row[3], Bf.row[0]);

		_mm_store_ps(R[0], row1);
		_mm_store_ps(R[1], row2);
		_mm_store_ps(R[2], row3);
		_mm_store_ps(R[3], row4);
	}

	template <> void addMat4<double>(double A[][4], double B[][4], double R[][4])
	{
		InMatrix4D Af(A);
		InMatrix4D Bf(B);

		InVectd row1 = _mm256_add_pd(Af.row[0], Bf.row[0]);
		InVectd row2 = _mm256_add_pd(Af.row[1], Bf.row[0]);
		InVectd row3 = _mm256_add_pd(Af.row[2], Bf.row[0]);
		InVectd row4 = _mm256_add_pd(Af.row[3], Bf.row[0]);

		_mm256_store_pd(R[0], row1);
		_mm256_store_pd(R[1], row2);
		_mm256_store_pd(R[2], row3);
		_mm256_store_pd(R[3], row4);
	}

	template <> void subMat4<float>(float A[][4], float B[][4], float R[][4]) {
		InMatrix4F Af(A);
		InMatrix4F Bf(B);

		InVectf row1 = _mm_sub_ps(Af.row[0], Bf.row[0]);
		InVectf row2 = _mm_sub_ps(Af.row[1], Bf.row[0]);
		InVectf row3 = _mm_sub_ps(Af.row[2], Bf.row[0]);
		InVectf row4 = _mm_sub_ps(Af.row[3], Bf.row[0]);

		_mm_store_ps(R[0], row1);
		_mm_store_ps(R[1], row2);
		_mm_store_ps(R[2], row3);
		_mm_store_ps(R[3], row4);
	}

	template <> void subMat4<double>(double A[][4], double B[][4], double R[][4]) {
		InMatrix4D Af(A);
		InMatrix4D Bf(B);

		InVectd row1 = _mm256_sub_pd(Af.row[0], Bf.row[0]);
		InVectd row2 = _mm256_sub_pd(Af.row[1], Bf.row[0]);
		InVectd row3 = _mm256_sub_pd(Af.row[2], Bf.row[0]);
		InVectd row4 = _mm256_sub_pd(Af.row[3], Bf.row[0]);

		_mm256_store_pd(R[0], row1);
		_mm256_store_pd(R[1], row2);
		_mm256_store_pd(R[2], row3);
		_mm256_store_pd(R[3], row4);
	}

	template <> bool matEquals4<float>(float A[][4], float B[][4]) {
		return equals4<float>(A[0], B[0]) 
			&& equals4<float>(A[1], B[1]) 
			&& equals4<float>(A[2], B[2]) 
			&& equals4<float>(A[3], B[3]);
	}

	template <> bool matEquals4<double>(double A[][4], double B[][4]) {
		return equals4<double>(A[0], B[0])
			&& equals4<double>(A[1], B[1])
			&& equals4<double>(A[2], B[2])
			&& equals4<double>(A[3], B[3]);
	}


	
    template<> bool invert4<float>(float A[][4], float O[][4], float eps, float* deter) {
        InMatrix4F Mt;
        transpose4(A, Mt);
        InVectf tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10;
        //10 * row3
        tmp1 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[2], Mt.row[2], 0xaa), Mt.row[3]);

        //11 * row3
        tmp2 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[2], Mt.row[2], 0xff), Mt.row[3]);

        //9 * row3
        tmp3 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[2], Mt.row[2], 0x55), Mt.row[3]);

        //8 * row3
        tmp4 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[2], Mt.row[2], 0x0), Mt.row[3]);

        //form first mul add 5 4 4 4 row 3 and mul 
        tmp5 = PERMUTE_PS(Mt.row[1], _MM_SHUFFLE(0, 0, 0, 1));
        tmp7 = _mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(2, 2, 3, 3));
        tmp8 = _mm_shuffle_ps(tmp3, tmp1, _MM_SHUFFLE(1, 1, 3, 3));
        __m128 tmp0125 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));
        tmp9 = _mm_mul_ps(tmp5, tmp0125);

        //form second mul 6 6 5 5 row 3 and mul
        tmp6 = PERMUTE_PS(Mt.row[1], _MM_SHUFFLE(1, 1, 2, 2));
        tmp7 = _mm_shuffle_ps(tmp2, tmp4, _MM_SHUFFLE(3, 3, 1, 1));
        tmp8 = _mm_shuffle_ps(tmp2, tmp4, _MM_SHUFFLE(2, 2, 0, 0));
        __m128 tmp3678 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));

        tmp9 = _mm_add_ps(tmp9, _mm_mul_ps(tmp6, tmp3678));

        //form mul 7 7 7 6
        tmp10 = PERMUTE_PS(Mt.row[1], _MM_SHUFFLE(2, 3, 3, 3));
        tmp7 = _mm_shuffle_ps(tmp3, tmp1, _MM_SHUFFLE(0, 0, 2, 2));
        tmp8 = _mm_shuffle_ps(tmp4, tmp3, _MM_SHUFFLE(0, 0, 1, 1));
        __m128 tmp491011 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));

        tmp9 = _mm_add_ps(tmp9, _mm_mul_ps(tmp10, tmp491011));

        //form first mul add 5 4 4 4 row 3 and mul 
        tmp7 = _mm_shuffle_ps(tmp2, tmp1, _MM_SHUFFLE(3, 3, 2, 2));
        tmp8 = _mm_shuffle_ps(tmp2, tmp3, _MM_SHUFFLE(2, 2, 1, 1));
        __m128 tmp1034 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));

        tmp9 = _mm_sub_ps(tmp9, _mm_mul_ps(tmp5, tmp1034));

        //form second mul 6 6 5 5 row 3 and mul
        tmp7 = _mm_shuffle_ps(tmp3, tmp2, _MM_SHUFFLE(0, 0, 3, 3));
        tmp8 = _mm_shuffle_ps(tmp4, tmp1, _MM_SHUFFLE(0, 0, 3, 3));
        __m128 tmp2769 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));

        tmp9 = _mm_sub_ps(tmp9, _mm_mul_ps(tmp6, tmp2769));

        //form mul 7 7 7 6
        tmp7 = _mm_shuffle_ps(tmp1, tmp4, _MM_SHUFFLE(2, 2, 1, 1));
        tmp8 = _mm_shuffle_ps(tmp3, tmp4, _MM_SHUFFLE(1, 1, 0, 0));
        __m128 tmp581110 = _mm_shuffle_ps(tmp7, tmp8, _MM_SHUFFLE(3, 0, 3, 0));

        __m128 row0 = _mm_sub_ps(tmp9, _mm_mul_ps(tmp10, tmp581110));


        //form vector 1 0 0 0
        tmp5 = PERMUTE_PS(Mt.row[0], _MM_SHUFFLE(0, 0, 0, 1));
        tmp8 = _mm_mul_ps(tmp5, tmp1034);


        //form vector 2 2 1 1
        tmp9 = PERMUTE_PS(Mt.row[0], _MM_SHUFFLE(1, 1, 2, 2));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp9, tmp2769));

        //form vector 3 3 3 2
        tmp10 = PERMUTE_PS(Mt.row[0], _MM_SHUFFLE(2, 3, 3, 3));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp10, tmp581110));

        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp5, tmp0125));
        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp9, tmp3678));
        __m128 row1 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp10, tmp491011));

        //2 * row3
        tmp1 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[0], Mt.row[0], 0xaa), Mt.row[1]);

        //3 * row3
        tmp2 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[0], Mt.row[0], 0xff), Mt.row[1]);

        //1 * row3
        tmp3 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[0], Mt.row[0], 0x55), Mt.row[1]);

        //0 * row3
        tmp4 = _mm_mul_ps(_mm_shuffle_ps(Mt.row[0], Mt.row[0], 0x0), Mt.row[1]);

        //form vector 13 12 12 12
        tmp5 = PERMUTE_PS(Mt.row[3], _MM_SHUFFLE(0, 0, 0, 1));
        tmp6 = _mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(2, 2, 3, 3));
        tmp7 = _mm_shuffle_ps(tmp3, tmp1, _MM_SHUFFLE(1, 1, 3, 3));
        tmp0125 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        tmp8 = _mm_mul_ps(tmp5, tmp0125);

        //form vector 14 14 13 13
        tmp9 = PERMUTE_PS(Mt.row[3], _MM_SHUFFLE(1, 1, 2, 2));
        tmp6 = _mm_shuffle_ps(tmp2, tmp4, _MM_SHUFFLE(3, 3, 1, 1));
        tmp7 = _mm_shuffle_ps(tmp2, tmp4, _MM_SHUFFLE(2, 2, 0, 0));
        tmp3678 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp3678, tmp9));

        //form vector 15 15 15 14
        tmp10 = PERMUTE_PS(Mt.row[3], _MM_SHUFFLE(2, 3, 3, 3));
        tmp6 = _mm_shuffle_ps(tmp3, tmp1, _MM_SHUFFLE(0, 0, 2, 2));
        tmp7 = _mm_shuffle_ps(tmp4, tmp3, _MM_SHUFFLE(0, 0, 1, 1));
        tmp491011 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp491011, tmp10));

        tmp6 = _mm_shuffle_ps(tmp2, tmp1, _MM_SHUFFLE(3, 3, 2, 2));
        tmp7 = _mm_shuffle_ps(tmp2, tmp3, _MM_SHUFFLE(2, 2, 1, 1));
        tmp1034 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp5, tmp1034));

        tmp6 = _mm_shuffle_ps(tmp3, tmp2, _MM_SHUFFLE(0, 0, 3, 3));
        tmp7 = _mm_shuffle_ps(tmp4, tmp1, _MM_SHUFFLE(0, 0, 3, 3));
        tmp2769 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp9, tmp2769));

        tmp6 = _mm_shuffle_ps(tmp1, tmp4, _MM_SHUFFLE(2, 2, 1, 1));
        tmp7 = _mm_shuffle_ps(tmp3, tmp4, _MM_SHUFFLE(1, 1, 0, 0));
        tmp581110 = _mm_shuffle_ps(tmp6, tmp7, _MM_SHUFFLE(3, 0, 3, 0));
        __m128 row2 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp10, tmp581110));

        //form vector 9 8 8 8
        tmp5 = PERMUTE_PS(Mt.row[2], _MM_SHUFFLE(0, 0, 0, 1));
        tmp8 = _mm_mul_ps(tmp5, tmp1034);

        //form vector 10 10 9 9
        tmp6 = PERMUTE_PS(Mt.row[2], _MM_SHUFFLE(1, 1, 2, 2));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp6, tmp2769));

        //form vector 11 11 11 10
        tmp7 = PERMUTE_PS(Mt.row[2], _MM_SHUFFLE(2, 3, 3, 3));
        tmp8 = _mm_add_ps(tmp8, _mm_mul_ps(tmp7, tmp581110));

        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp5, tmp0125));
        tmp8 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp6, tmp3678));
        __m128 row3 = _mm_sub_ps(tmp8, _mm_mul_ps(tmp7, tmp491011));

        __m128 det = _mm_mul_ps(row0, Mt.row[0]);
        tmp1 = _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 2, 1, 1));
        det = _mm_add_ps(det, tmp1);
        tmp1 = _mm_shuffle_ps(det, det, _MM_SHUFFLE(3, 3, 3, 3));
        det = _mm_add_ps(det, tmp1);
        det = _mm_shuffle_ps(det, det, _MM_SHUFFLE(0, 0, 0, 0));

        tmp1 = _mm_set_ps1(eps);
        tmp1 = _mm_cmpeq_ps(tmp1, det);

        if (deter != nullptr)
            _mm_store_ss(deter, det);

        tmp3 = _mm_set_ps1(1.f);
        tmp2 = _mm_div_ps(tmp3, det);

        row0 = _mm_mul_ps(tmp2, row0);
        row1 = _mm_mul_ps(tmp2, row1);
        row2 = _mm_mul_ps(tmp2, row2);
        row3 = _mm_mul_ps(tmp2, row3);

        _mm_store_ps(O[0], row0);
        _mm_store_ps(O[1], row1);
        _mm_store_ps(O[2], row2);
        _mm_store_ps(O[3], row3);

        return _mm_extract_ps(tmp1, 0) != 0xFFFFFFFF;
     



    }

    template<> void outerProduct4<float>(const float* v1, const float* v2, float R[][4]) {
        InVectf tmp = _mm_load_ps(v2);

        InVectf r1 = _mm_set1_ps(v1[0]);
        r1 = _mm_mul_ps(r1, tmp);
        InVectf r2 = _mm_set1_ps(v1[1]);
        r2 = _mm_mul_ps(r2, tmp);
        InVectf r3 = _mm_set1_ps(v1[2]);
        r3 = _mm_mul_ps(r3, tmp);
        InVectf r4 = _mm_set1_ps(v1[3]);
        r4 = _mm_mul_ps(r4, tmp);

        _mm_store_ps(R[0], r1);
        _mm_store_ps(R[1], r2);
        _mm_store_ps(R[2], r3);
        _mm_store_ps(R[3], r4);

    }

    template<> void outerProduct4<double>(const double* v1, const double* v2, double R[][4]) {
        InVectd tmp = _mm256_load_pd(v2);

        InVectd r1 = _mm256_set1_pd(v1[0]);
        r1 = _mm256_mul_pd(r1, tmp);
        InVectd r2 = _mm256_set1_pd(v1[1]);
        r2 = _mm256_mul_pd(r2, tmp);
        InVectd r3 = _mm256_set1_pd(v1[2]);
        r3 = _mm256_mul_pd(r3, tmp);
        InVectd r4 = _mm256_set1_pd(v1[3]);
        r4 = _mm256_mul_pd(r4, tmp);

        _mm256_store_pd(R[0], r1);
        _mm256_store_pd(R[1], r2);
        _mm256_store_pd(R[2], r3);
        _mm256_store_pd(R[3], r4);
    }




}