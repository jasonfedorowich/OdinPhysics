#pragma once
#include "Matrix.h"

template<int SIZE, typename real>
int gaussJordan(Matrix<SIZE, real>& A, Matrix<SIZE, real>& I)
{
    auto findMax = [&](Matrix<SIZE, real>& A, int k) {
        int maxi = A(k, k);
        int index = k;

        for (int i = k + 1; i < SIZE; i++) {
            if (maxi < abs(A(i, k))) {
                maxi = abs(A(i, k));
                index = i;

            }

        }

        return index;


    };


	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++) {

			if (i == j)
				I(i, j) = (real)1.0;
			else
				I(i, j) = (real)0.0;

		}
	}

    real temp;
    Vector<SIZE, real> pivoted;

    for (int i = 0; i < SIZE; i++) {

        int idx = findMax(A, i);
        if (A(idx,i) == (real)0.0)
            return SINGULAR;

        if (idx != i) {
            A.swapRows(idx, i);
            I.swapRows(idx, i);
        }

        for (int j = i + 1; j < SIZE; j++) {
            real c = A(j, i) / A(i, i);

            for (int k = 0; k < SIZE; k++) {
                A(j, k) = A(j, k) - c * A(i, k);
                I(j, k) = I(j, k) - c * I(i, k);
            }                 

        }
      
    }

    for (int i = SIZE - 1; i >= 0; i--) {

        for (int j = i - 1; j >= 0; j--) {

            real c = A(j, i) / A(i, i);

            for (int k = 0; k < SIZE; k++) {
                A(j, k) = A(j, k) - c * A(i, k);
                I(j, k) = I(j, k) - c * I(i, k);


            }
        }


    }


    for (int i = 0; i < SIZE; i++) {

        temp = A(i, i);
        if (temp == (real)0.0)
            return SINGULAR;
        A(i, i) /= temp;


        for (int j = 0; j < SIZE; j++) {

            I(i, j) = I(i, j) / temp;
        }
    }

    return NON_SINGULAR;

}

template<int SIZE, typename real>
inline Vector<SIZE, real> Matrix<SIZE, real>::getRow(int row)
{
    Vector<SIZE, real> rVect;
    for (int i = 0; i < SIZE; i++) {
        rVect[i] = m[row][i];
    }

    return rVect;
}

template<int SIZE, typename real>
inline Vector<SIZE, real> Matrix<SIZE, real>::getCol(int col)
{
    Vector<SIZE, real> cVect;
    for (int i = 0; i < SIZE; i++) {
        cVect[i] = m[i][col];
    }

    return cVect;
}

template<int SIZE, typename real>
inline void Matrix<SIZE, real>::swapRows(int to, int from)
{
    Vector<SIZE, real> temp = (*this)(to);
    this->setRow(to, (*this)(from));
    this->setRow(from, temp);

}

template<int SIZE, typename real>
inline void Matrix<SIZE, real>::setRow(int row, const Vector<SIZE, real>& vector)
{
    for (int i = 0; i < SIZE; i++) {
        m[row][i] = vector[i];

    }
}

template<int SIZE, typename real>
inline void Matrix<SIZE, real>::setRow(int row, Vector<SIZE, real>&& vector)
{
    for (int i = 0; i < SIZE; i++) {
        m[row][i] = vector[i];

    }
}

template<int SIZE, typename real>
inline void Matrix<SIZE, real>::setCol(int col, const Vector<SIZE, real>& vector)
{
    for (int i = 0; i < SIZE; i++) {
        m[i][col] = vector[i];
    }
}

template<int SIZE, typename real>
inline void Matrix<SIZE, real>::setCol(int col, Vector<SIZE, real>&& vector)
{
    for (int i = 0; i < SIZE; i++) {
        m[i][col] = vector[i];
    }
}
