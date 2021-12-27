#include "OdinMath.h"

namespace OdinMath {
    void matScale4f(InMatrix4F& Af, float scale, InMatrix4F& O)
    {
        InVectf vf = _mm_load1_ps(&scale);
        O.row[0] = _mm_mul_ps(Af.row[0], vf);
        O.row[1] = _mm_mul_ps(Af.row[1], vf);
        O.row[2] = _mm_mul_ps(Af.row[2], vf);
        O.row[3] = _mm_mul_ps(Af.row[3], vf);

    }

    void matScale4d(InMatrix4D& Af, double scale, InMatrix4D& O)
    {
        InVectd vf = _mm256_set_pd(scale, scale, scale, scale);
        O.row[0] = _mm256_mul_pd(Af.row[0], vf);
        O.row[1] = _mm256_mul_pd(Af.row[1], vf);
        O.row[2] = _mm256_mul_pd(Af.row[2], vf);
        O.row[3] = _mm256_mul_pd(Af.row[3], vf);
    }

    void addMat4f(InMatrix4F& A, InMatrix4F& B, InMatrix4F& O)
    {
        O.row[0] = _mm_add_ps(A.row[0], B.row[0]);
        O.row[1] = _mm_add_ps(A.row[1], B.row[1]);
        O.row[2] = _mm_add_ps(A.row[2], B.row[2]);
        O.row[3] = _mm_add_ps(A.row[3], B.row[3]);
    }

    void addMat4d(InMatrix4D& A, InMatrix4D& B, InMatrix4D& O)
    {
        O.row[0] = _mm256_add_pd(A.row[0], B.row[0]);
        O.row[1] = _mm256_add_pd(A.row[1], B.row[1]);
        O.row[2] = _mm256_add_pd(A.row[2], B.row[2]);
        O.row[3] = _mm256_add_pd(A.row[3], B.row[3]);
    }

    void subMat4f(InMatrix4F& A, InMatrix4F& B, InMatrix4F& O)
    {

        O.row[0] = _mm_sub_ps(A.row[0], B.row[0]);
        O.row[1] = _mm_sub_ps(A.row[1], B.row[1]);
        O.row[2] = _mm_sub_ps(A.row[2], B.row[2]);
        O.row[3] = _mm_sub_ps(A.row[3], B.row[3]);
    }

    void subMat4d(InMatrix4D& A, InMatrix4D& B, InMatrix4D& O)
    {
        O.row[0] = _mm256_sub_pd(A.row[0], B.row[0]);
        O.row[1] = _mm256_sub_pd(A.row[1], B.row[1]);
        O.row[2] = _mm256_sub_pd(A.row[2], B.row[2]);
        O.row[3] = _mm256_sub_pd(A.row[3], B.row[3]);
    }

    bool matEquals4f(InMatrix4F& A, InMatrix4F& B)
    {
        return equals4f(A.row[0], B.row[0])
            && equals4f(A.row[1], B.row[1])
            && equals4f(A.row[2], B.row[2])
            && equals4f(A.row[3], B.row[3]);
    }

    bool matEquals4d(InMatrix4D& A, InMatrix4D& B)
    {
        return equals4d(A.row[0], B.row[0])
            && equals4d(A.row[1], B.row[1])
            && equals4d(A.row[2], B.row[2])
            && equals4d(A.row[3], B.row[3]);
    }

    bool invert4f(InMatrix4F& A, InMatrix4F& O, float eps, float* deter)
    {
        InMatrix4F Mt;
        transpose4f(A, Mt);
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

        O.row[0] = _mm_mul_ps(tmp2, row0);
        O.row[1] = _mm_mul_ps(tmp2, row1);
        O.row[2] = _mm_mul_ps(tmp2, row2);
        O.row[3] = _mm_mul_ps(tmp2, row3);

        

        return _mm_extract_ps(tmp1, 0) != 0xFFFFFFFF;

    }


    bool invert4d(InMatrix4D& in, InMatrix4D& out, double eps, double* determinant)
    {
        InMatrix4D Mt;
        transpose4d(in, Mt);
        InVectd tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10;
        //10 * row3
        tmp1 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[2], 0xaa), Mt.row[3]);

        //11 * row3
        tmp2 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[2], 0xff), Mt.row[3]);

        //9 * row3
        tmp3 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[2], 0x55), Mt.row[3]);

        //8 * row3
        tmp4 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[2], 0x0), Mt.row[3]);

        //form first mul add 5 4 4 4 row 3 and mul 
        tmp5 = _mm256_permutex_pd(Mt.row[1], 0x01);

        //_MM_SHUFFLE(2, 2, 3, 3)
        tmp7 = _mm256_shuffle_pd(tmp1, tmp2, 0x4);
        //_MM_SHUFFLE(1, 1, 3, 3)
        tmp8 = _mm256_shuffle_pd(tmp3, tmp1, 0x6);
        tmp8 = _mm256_permutex_pd(tmp8, _MM_PERM_ENUM::_MM_PERM_BCCC);
        __m128d tmp = _mm256_extractf128_pd(tmp7, 0x1);
        __m256d tmp0125 = _mm256_insertf128_pd(tmp8, tmp, 0x0);
        tmp9 = _mm256_mul_pd(tmp5, tmp0125);

        //form second mul 6 6 5 5 row 3 and mul
        tmp6 = _mm256_permutex_pd(Mt.row[1], _MM_PERM_ENUM::_MM_PERM_BBCC);
        //_MM_SHUFFLE(3, 3, 1, 1)
        tmp7 = _mm256_shuffle_pd(tmp2, tmp4, 0xf);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_DDDA);
        tmp = _mm256_extractf128_pd(tmp7, 0x0);
        //_MM_SHUFFLE(2, 2, 0, 0)
        tmp8 = _mm256_shuffle_pd(tmp2, tmp4, 0x0);
        tmp8 = _mm256_permutex_pd(tmp8, _MM_PERM_ENUM::_MM_PERM_DAAA);
        __m256d tmp3678 = _mm256_insertf128_pd(tmp8, tmp, 0x0);

        tmp9 = _mm256_add_pd(tmp9, _mm256_mul_pd(tmp6, tmp3678));

        //form mul 7 7 7 6
        tmp10 = _mm256_permutex_pd(Mt.row[1], _MM_PERM_ENUM::_MM_PERM_CDDD);
        //_MM_SHUFFLE(0, 0, 2, 2)
        tmp7 = _mm256_shuffle_pd(tmp3, tmp1, 0x0);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_BBBC);
        //_MM_SHUFFLE(0, 0, 1, 1)
        tmp8 = _mm256_shuffle_pd(tmp4, tmp3, 0x1);
        tmp = _mm256_extractf128_pd(tmp8, 0x0);
        __m256d tmp491011 = _mm256_insertf128_pd(tmp7, tmp, 0x1);

        tmp9 = _mm256_add_pd(tmp9, _mm256_mul_pd(tmp10, tmp491011));

        //form first mul add 5 4 4 4 row 3 and mul 
        //_MM_SHUFFLE(3, 3, 2, 2)
        tmp7 = _mm256_shuffle_pd(tmp2, tmp1, 0x8);
        tmp = _mm256_extractf128_pd(tmp7, 0x1);
        // _MM_SHUFFLE(2, 2, 1, 1)
        tmp8 = _mm256_shuffle_pd(tmp2, tmp3, 0x1);
        tmp8 = _mm256_permutex_pd(tmp8, _MM_PERM_ENUM::_MM_PERM_DADD);
        __m256d tmp1034 = _mm256_insertf128_pd(tmp8, tmp, 0x0);

        tmp9 = _mm256_sub_pd(tmp9, _mm256_mul_pd(tmp5, tmp1034));

        //form second mul 6 6 5 5 row 3 and mul
        //_MM_SHUFFLE(0, 0, 3, 3)
        tmp7 = _mm256_shuffle_pd(tmp3, tmp2, 0x4);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_BBBC);
        //_MM_SHUFFLE(0, 0, 3, 3)
        tmp8 = _mm256_shuffle_pd(tmp4, tmp1, 0x4);
        tmp8 = _mm256_permutex_pd(tmp8, _MM_PERM_ENUM::_MM_PERM_BBBC);
        tmp = _mm256_extractf128_pd(tmp8, 0x0);

        __m256d tmp2769 = _mm256_insertf128_pd(tmp7, tmp, 0x1);

        tmp9 = _mm256_sub_pd(tmp9, _mm256_mul_pd(tmp6, tmp2769));

        //form mul 7 7 7 6
        //_MM_SHUFFLE(2, 2, 1, 1)
        tmp7 = _mm256_shuffle_pd(tmp1, tmp4, 0x1);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_DDDA);
        // _MM_SHUFFLE(1, 1, 0, 0)
        tmp8 = _mm256_shuffle_pd(tmp3, tmp4, 0x2);
        tmp = _mm256_extractf128_pd(tmp8, 0x0);
        __m256d tmp581110 = _mm256_insertf128_pd(tmp7, tmp, 0x1);

        out.row[0] = _mm256_sub_pd(tmp9, _mm256_mul_pd(tmp10, tmp581110));

        //form vector 1 0 0 0
        tmp5 = _mm256_permutex_pd(Mt.row[0], _MM_PERM_ENUM::_MM_PERM_AAAB);
        tmp8 = _mm256_mul_pd(tmp5, tmp1034);


        //form vector 2 2 1 1
        tmp9 = _mm256_permutex_pd(Mt.row[0], _MM_PERM_ENUM::_MM_PERM_BBCC);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp9, tmp2769));

        //form vector 3 3 3 2
        tmp10 = _mm256_permutex_pd(Mt.row[0], _MM_PERM_ENUM::_MM_PERM_CDDD);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp10, tmp581110));

        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp5, tmp0125));
        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp9, tmp3678));
        out.row[1] = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp10, tmp491011));


        //2 * row3
        tmp1 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[0], 0xaa), Mt.row[1]);

        //3 * row3
        tmp2 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[0], 0xff), Mt.row[1]);

        //1 * row3
        tmp3 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[0], 0x55), Mt.row[1]);

        //0 * row3
        tmp4 = _mm256_mul_pd(_mm256_permutex_pd(Mt.row[0], 0x00), Mt.row[1]);


        //form vector 13 12 12 12
        // _MM_SHUFFLE(0, 0, 0, 1)
        tmp5 = _mm256_permutex_pd(Mt.row[3], _MM_PERM_ENUM::_MM_PERM_AAAB);
        //_MM_SHUFFLE(2, 2, 3, 3)
        tmp6 = _mm256_shuffle_pd(tmp1, tmp2, 0x6);
        tmp = _mm256_extractf128_pd(tmp6, 0x1);
        // _MM_SHUFFLE(1, 1, 3, 3)
        tmp7 = _mm256_shuffle_pd(tmp3, tmp1, 0xf);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_BCCC);
        tmp0125 = _mm256_insertf128_pd(tmp7, tmp, 0x0);
        tmp8 = _mm256_mul_pd(tmp5, tmp0125);

        //form vector 14 14 13 13
        tmp9 = _mm256_permutex_pd(Mt.row[3], _MM_PERM_ENUM::_MM_PERM_BBCC);
        //_MM_SHUFFLE(3, 3, 1, 1)
        tmp6 = _mm256_shuffle_pd(tmp2, tmp4, 0xf);
        tmp6 = _mm256_permutex_pd(tmp6, _MM_PERM_ENUM::_MM_PERM_BBDA);
        tmp = _mm256_extractf128_pd(tmp6, 0x0);
        // _MM_SHUFFLE(2, 2, 0, 0)
        tmp7 = _mm256_shuffle_pd(tmp2, tmp4, 0x0);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_DADD);

        tmp3678 = _mm256_insertf128_pd(tmp7, tmp, 0x0);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp3678, tmp9));

        //form vector 15 15 15 14
        tmp10 = _mm256_permutex_pd(Mt.row[3], _MM_PERM_ENUM::_MM_PERM_CDDD);
        //_MM_SHUFFLE(0, 0, 2, 2)
        tmp6 = _mm256_shuffle_pd(tmp3, tmp1, 0x0);
        tmp6 = _mm256_permutex_pd(tmp6, _MM_PERM_ENUM::_MM_PERM_BBBC);
        tmp7 = _mm256_shuffle_pd(tmp4, tmp3, 0x1);
        tmp = _mm256_extractf128_pd(tmp7, 0x0);
        tmp491011 = _mm256_insertf128_pd(tmp6, tmp, 0x1);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp491011, tmp10));

        //_MM_SHUFFLE(3, 3, 2, 2)
        tmp6 = _mm256_shuffle_pd(tmp2, tmp1, 0x8);
        tmp = _mm256_extractf128_pd(tmp6, 0x1);
        //_MM_SHUFFLE(2, 2, 1, 1)
        tmp7 = _mm256_shuffle_pd(tmp2, tmp3, 0x1);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_DADD);
        tmp1034 = _mm256_insertf128_pd(tmp7, tmp, 0x0);
        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp5, tmp1034));


        //_MM_SHUFFLE(0, 0, 3, 3)
        tmp6 = _mm256_shuffle_pd(tmp3, tmp2, 0x4);
        tmp6 = _mm256_permutex_pd(tmp6, _MM_PERM_ENUM::_MM_PERM_AABC);
        //_MM_SHUFFLE(0, 0, 3, 3)
        tmp7 = _mm256_shuffle_pd(tmp4, tmp1, 0x4);
        tmp7 = _mm256_permutex_pd(tmp7, _MM_PERM_ENUM::_MM_PERM_BCBB);
        tmp = _mm256_extractf128_pd(tmp7, 0x1);
        tmp2769 = _mm256_insertf128_pd(tmp6, tmp, 0x1);
        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp9, tmp2769));

        //_MM_SHUFFLE(2, 2, 1, 1)
        tmp6 = _mm256_shuffle_pd(tmp1, tmp4, 0x1);
        tmp6 = _mm256_permutex_pd(tmp6, _MM_PERM_ENUM::_MM_PERM_AADA);
        //_MM_SHUFFLE(1, 1, 0, 0)
        tmp7 = _mm256_shuffle_pd(tmp3, tmp4, 0x2);
        tmp = _mm256_extractf128_pd(tmp7, 0x0);
        tmp581110 = _mm256_insertf128_pd(tmp6, tmp, 0x1);
        out.row[2] = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp10, tmp581110));


        //form vector 9 8 8 8
        tmp5 = _mm256_permutex_pd(Mt.row[2], _MM_PERM_ENUM::_MM_PERM_AAAB);
        tmp8 = _mm256_mul_pd(tmp5, tmp1034);

        //form vector 10 10 9 9
        tmp6 = _mm256_permutex_pd(Mt.row[2], _MM_PERM_ENUM::_MM_PERM_BBCC);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp6, tmp2769));

        //form vector 11 11 11 10
        tmp7 = _mm256_permutex_pd(Mt.row[2], _MM_PERM_ENUM::_MM_PERM_CDDD);
        tmp8 = _mm256_add_pd(tmp8, _mm256_mul_pd(tmp7, tmp581110));

        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp5, tmp0125));
        tmp8 = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp6, tmp3678));
        out.row[3] = _mm256_sub_pd(tmp8, _mm256_mul_pd(tmp7, tmp491011));


        __m256d det = _mm256_mul_pd(out.row[0], Mt.row[0]);
        det = _mm256_hadd_pd(det, det);
        tmp1 = _mm256_permutex_pd(det, _MM_PERM_ENUM::_MM_PERM_DDDD);
        det = _mm256_add_pd(det, tmp1);
        det = _mm256_permutex_pd(det, _MM_PERM_ENUM::_MM_PERM_AAAA);
        tmp4 = _mm256_mul_pd(det, det);
        tmp1 = _mm256_set1_pd(eps);
        tmp1 = _mm256_cmp_pd(tmp4, tmp1, 0x1);
        double v = tmp1.m256d_f64[0];


        if (v != 0.0)
            return false;



        tmp = _mm256_extractf128_pd(det, 0x0);

        //store single double value _sd
        if (determinant != nullptr)
            _mm_store_sd(determinant, tmp);


        tmp3 = _mm256_set1_pd(1.f);
        tmp2 = _mm256_div_pd(tmp3, det);

        out.row[0] = _mm256_mul_pd(tmp2, out.row[0]);
        out.row[1] = _mm256_mul_pd(tmp2, out.row[1]);
        out.row[2] = _mm256_mul_pd(tmp2, out.row[2]);
        out.row[3] = _mm256_mul_pd(tmp2, out.row[3]);
        return true;
    }


   

	template <> void matScale4<float>(float A[][4], float scale, float R[][4]) {
		InMatrix4F Af(A);
        InMatrix4F O;
        matScale4f(Af, scale, O);
        storeMat4(O, R);
		
	}

	template <> void matScale4<double>(double A[][4], double scale, double R[][4]) {
		InMatrix4D Af(A);
        InMatrix4D O;
        matScale4d(Af, scale, O);
        storeMat4(O, R);

	}

    template<> void matScale4<float>(float A[][3], float scale, float R[][3]) {
        InMatrix4F Af(A);
        InMatrix4F O;
        matScale4f(Af, scale, O);
        storeMat3(O, R);
    }
    template<> void matScale4<double>(double A[][3], double scale, double R[][3]) {
        InMatrix4D Af(A);
        InMatrix4D O;
        matScale4d(Af, scale, O);
        storeMat3(O, R);
    }
	
	template <> void addMat4<float>(float A[][4], float B[][4], float R[][4])
	{
		InMatrix4F Af(A);
		InMatrix4F Bf(B);
        InMatrix4F O;
        addMat4f(Af, Bf, O);
        storeMat4(O, R);

	}

	template <> void addMat4<double>(double A[][4], double B[][4], double R[][4])
	{
		InMatrix4D Af(A);
		InMatrix4D Bf(B);
        InMatrix4D O;
        addMat4d(Af, Bf, O);
        storeMat4(O, R);

	}

    template <> void addMat4<float>(float A[][3], float B[][3], float R[][3])
    {
        InMatrix4F Af(A);
        InMatrix4F Bf(B);
        InMatrix4F O;
        addMat4f(Af, Bf, O);
        storeMat3(O, R);

    }

    template <> void addMat4<double>(double A[][3], double B[][3], double R[][3])
    {
        InMatrix4D Af(A);
        InMatrix4D Bf(B);
        InMatrix4D O;
        addMat4d(Af, Bf, O);
        storeMat3(O, R);

    }

	template <> void subMat4<float>(float A[][4], float B[][4], float R[][4]) {
		InMatrix4F Af(A);
		InMatrix4F Bf(B);
        InMatrix4F O;
        subMat4f(Af, Bf, O);
        storeMat4(O, R);
		
	}

	template <> void subMat4<double>(double A[][4], double B[][4], double R[][4]) {
		InMatrix4D Af(A);
		InMatrix4D Bf(B);
        InMatrix4D O;
        subMat4d(Af, Bf, O);
        storeMat4(O, R);
		
	}

    template <> void subMat4<float>(float A[][3], float B[][3], float R[][3]) {
        InMatrix4F Af(A);
        InMatrix4F Bf(B);
        InMatrix4F O;
        subMat4f(Af, Bf, O);
        storeMat3(O, R);

    }

    template <> void subMat4<double>(double A[][3], double B[][3], double R[][3]) {
        InMatrix4D Af(A);
        InMatrix4D Bf(B);
        InMatrix4D O;
        subMat4d(Af, Bf, O);
        storeMat3(O, R);

    }

	template <> bool matEquals4<float>(float A[][4], float B[][4]) {
        InMatrix4F AA(A);
        InMatrix4F BB(B);
        return matEquals4f(AA, BB);
	}

	template <> bool matEquals4<double>(double A[][4], double B[][4]) {
        InMatrix4D AA(A);
        InMatrix4D BB(B);
        return matEquals4d(AA, BB);
	}

    template <> bool matEquals4<float>(float A[][3], float B[][3]) {
        InMatrix4F AA(A);
        InMatrix4F BB(B);
        return matEquals4f(AA, BB);
    }

    template <> bool matEquals4<double>(double A[][3], double B[][3]) {
        InMatrix4D AA(A);
        InMatrix4D BB(B);
        return matEquals4d(AA, BB);
    }

	
    template<> bool invert4<float>(float A[][4], float O[][4], float eps, float* deter) {
        InMatrix4F AA(A);
        InMatrix4F out;
        bool result = invert4f(AA, out, eps, deter);
        storeMat4(out, O);
        return result;
  

    }

    template<> bool invert4<double>(double A[][4], double O[][4], double eps, double* deter) {
        InMatrix4D AA(A);
        InMatrix4D out;
        bool result = invert4d(AA, out, eps, deter);
        storeMat4(out, O);
        return result;

    }
    template<> bool invert4<float>(float A[][3], float O[][3], float eps, float* deter) {
        InMatrix4F AA(A);
        InMatrix4F out;
        bool result = invert4f(AA, out, eps, deter);
        storeMat3(out, O);
        return result;


    }

    template<> bool invert4<double>(double A[][3], double O[][3], double eps, double* deter) {
        InMatrix4D AA(A);
        InMatrix4D out;
        bool result = invert4d(AA, out, eps, deter);
        storeMat3(out, O);
        return result;

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