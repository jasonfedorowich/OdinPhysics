#pragma once
#include "OdinMath.h"
#include <stdexcept>

namespace OdinMath {

	template<int SIZE, typename real>
	class Matrix {
	private:
		real matrix[SIZE][SIZE] = { (real)0.0 };

	public:
		Matrix() {};
		Matrix(std::initializer_list<std::initializer_list<real>>&& mat);
		Matrix(const Matrix<SIZE, real>& mat) { *this = mat; };
		~Matrix() {};

		
		Matrix<SIZE, real> mul(Matrix<SIZE, real>& B);
		Matrix<SIZE, real> strassenMult(Matrix<SIZE, real>& B, int n = SIZE);

		
		Matrix operator+(Matrix<SIZE, real>& mat);
		Matrix operator+(Matrix<SIZE, real>&& mat);
		Matrix operator-(Matrix<SIZE, real>& mat);
		Matrix operator-(Matrix<SIZE, real>&& mat);
		real& operator()(int row, int col);
		const real& operator()(int row, int col) const;
		bool operator==(Matrix<SIZE, real>& mat);
		Matrix& operator=(const Matrix<SIZE, real>& mat);

		void test();
		Matrix<SIZE, real> test123(Matrix<SIZE, real>& B);
	


	};

	
	
	
	


	

	template<int SIZE, typename real>
	inline Matrix<SIZE, real>::Matrix(std::initializer_list<std::initializer_list<real>>&& mat)
	{
		assert(mat.size() == SIZE);
		auto it = mat.begin();
		assert((*it).size() == SIZE);

		int i = 0; int j = 0;
		for (; it != mat.end(); it++, i++) {
			j = 0;
			for (auto itj = (*it).begin(); itj != (*it).end(); itj++, j++) {
				matrix[i][j] = *itj;
			}
		}
	}



	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::strassenMult(Matrix<SIZE, real>& B, int n)
	{
		if (n == 1) {
			Matrix<SIZE, real> C;
			C(0, 0) = (*this)(0, 0) * B(0, 0);
			return C;

		}
			
		Matrix<SIZE, real> C;
		Matrix<SIZE, real> A11, A12, A21, A22;
		Matrix<SIZE, real> B11, B12, B21, B22;
		int m = n / 2;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				A11(i, j) = (*this)(i, j);
				A12(i, j) = (*this)(i, j + m);
				A21(i, j) = (*this)(i + m, j);
				A22(i, j) = (*this)(i + m, j + m);

				B11(i, j) = B(i, j);
				B12(i, j) = B(i, j + m);
				B21(i, j) = B(i + m, j);
				B22(i, j) = B(i + m, j + m);
			}
		}
		Matrix<SIZE, real> S1 = B12 - B22;
		Matrix<SIZE, real> S2 = A11 + A12;
		Matrix<SIZE, real> S3 = A21 + A22;
		Matrix<SIZE, real> S4 = B21 - B11;
		Matrix<SIZE, real> S5 = A11 + A22;
		Matrix<SIZE, real> S6 = B11 + B22;
		Matrix<SIZE, real> S7 = A12 - A22;
		Matrix<SIZE, real> S8 = B21 + B22;
		Matrix<SIZE, real> S9 = A11 - A21;
		Matrix<SIZE, real> S10 = B11 + B12;


		Matrix<SIZE, real> P1 = A11.strassenMult(S1, n / 2);
		Matrix<SIZE, real> P2 = S2.strassenMult(B22, n / 2);
		Matrix<SIZE, real> P3 = S3.strassenMult( B11, n / 2);
		Matrix<SIZE, real> P4 = A22.strassenMult( S4, n / 2);
		Matrix<SIZE, real> P5 = S5.strassenMult( S6, n / 2);
		Matrix<SIZE, real> P6 = S7.strassenMult( S8, n / 2);
		Matrix<SIZE, real> P7 = S9.strassenMult( S10, n / 2);


		Matrix<SIZE, real> C11 = P5 + P4 - P2 + P6;
		Matrix<SIZE, real> C12 = P1 + P2;
		Matrix<SIZE, real> C21 = P3 + P4;
		Matrix<SIZE, real> C22 = P5 + P1 - P3 - P7;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				C(i, j) = C11(i, j);
				C(i, j + m) = C12(i, j);
				C(i + m, j) = C21(i, j);
				C(i + m, j + m) = C22(i, j);
			}
		}


		return C;
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::operator+(Matrix<SIZE, real>& mat)
	{
		Matrix<SIZE, real> C;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				C(i, j) = matrix[i][j] + mat(i, j);

			}
		}

		return C;
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::operator+(Matrix<SIZE, real>&& mat)
	{
		Matrix<SIZE, real> C;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				C(i, j) = matrix[i][j] + mat(i, j);

			}
		}

		return C;
	
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::operator-(Matrix<SIZE, real>& mat)
	{
		Matrix<SIZE, real> C;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				C(i, j) = matrix[i][j] - mat(i, j);

			}
		}

		return C;
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::operator-(Matrix<SIZE, real>&& mat)
	{
		Matrix<SIZE, real> C;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				C(i, j) = matrix[i][j] - mat(i, j);

			}
		}

		return C;
	}

	template<int SIZE, typename real>
	inline real& Matrix<SIZE, real>::operator()(int row, int col)
	{
		if (row >= SIZE || col >= SIZE || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return matrix[row][col];
	}

	template<int SIZE, typename real>
	inline const real& Matrix<SIZE, real>::operator()(int row, int col) const
	{
		if (row >= SIZE || col >= SIZE || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return matrix[row][col];
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real>& Matrix<SIZE, real>::operator=(const Matrix<SIZE, real>& mat)
	{
		if (this != &mat) {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					this->matrix[i][j] = mat(i, j);
				}
			}
		}
		return *this;
	}

	template<int SIZE, typename real>
	inline void Matrix<SIZE, real>::test()
	{
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::test123(Matrix<SIZE, real>& B)
	{
		return Matrix<SIZE, real>();
	}

}