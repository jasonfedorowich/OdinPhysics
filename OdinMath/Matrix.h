#pragma once
#include "OdinMath.h"

namespace OdinMath {

#define SINGULAR 1
#define NON_SINGULAR 0

	//TODO put iterator in matrix to loop over columns
	///iterator should give vectors which support iterator as well

	template<int SIZE, typename real>
	class Matrix {

	protected:
		real m[SIZE][SIZE] = { (real)0.0 };
	private:
		friend struct Iterator;


		

		struct Iterator {
			Matrix<SIZE, real>* mat;
			int row;

			Iterator(Matrix* matrix) : mat(matrix), row(0) { }
			Iterator(Matrix* matrix, int pos) : mat(matrix), row(pos) { }

			Vector<SIZE, real> operator*() const { 
				if (row < SIZE)
					return this->mat->getRow(row);
				else
					return Vector<SIZE, real>();
			}
			Iterator& operator++() { ++row; return *this; }
			Iterator operator++(int) { Iterator it = (*this); ++(*this); return it; }

			friend bool operator==(const Iterator& a, const Iterator& b) { return a.row == b.row; }
			friend bool operator!=(const Iterator& a, const Iterator& b) { return a.row != b.row; }
			
			Iterator& operator=(Vector<SIZE, real>& ro) {
				if (row < SIZE)
					this->mat->setRow(row, ro);
				return *this;
			}

			Iterator& operator=(Vector<SIZE, real>&& ro) {
				if (row < SIZE)
					this->mat->setRow(row, ro);
				return *this;
			}


		};

	public:
		Matrix() {};
		Matrix(std::initializer_list<std::initializer_list<real>>&& mat);
		Matrix(const Matrix<SIZE, real>& mat) { *this = mat; };
		~Matrix() {};

		
		Matrix<SIZE, real> mul(Matrix<SIZE, real>& B);
		/*Matrix<SIZE, real> strassenMult(Matrix<SIZE, real>& B, int n = SIZE);*/
		void transpose();
		Matrix<SIZE, real> getTranspose();
		
		Matrix operator+(Matrix<SIZE, real>& mat);
		Matrix operator+(Matrix<SIZE, real>&& mat);
		Matrix operator-(Matrix<SIZE, real>& mat);
		Matrix operator-(Matrix<SIZE, real>&& mat);
		real& operator()(int row, int col);
		const real& operator()(int row, int col) const;
		bool operator==(Matrix<SIZE, real>& mat);
		Matrix& operator=(const Matrix<SIZE, real>& mat);
		void operator*=(real c);


		Iterator begin() { return Iterator(this); }
		Iterator end() { return Iterator(this, SIZE); }

		Vector<SIZE, real> operator()(int row);

		void test();
		Matrix<SIZE, real> test123(Matrix<SIZE, real>& B);
	
		void setRow(int row, const Vector<SIZE, real>& vector);
		void setRow(int row, Vector<SIZE, real>&& vector);

		void setCol(int col, const Vector<SIZE, real>& vector);
		void setCol(int col, Vector<SIZE, real>&& vector);

		Vector<SIZE, real> getRow(int row);
		Vector<SIZE, real> getCol(int col);

		void swapRows(int to, int from);

		
	


	};
	template<int SIZE, typename real>
	inline Vector<SIZE, real> operator*(Matrix<SIZE, real>& M, Vector<SIZE, real>& V) {
		Vector<SIZE, real> R;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {

				R(i) = M(i, j) * V(j);
			}
		}

		return R;

	}
	template<int SIZE, typename real>
	inline Matrix<SIZE, real> operator*(real c, Matrix<SIZE, real>& M) {
		Matrix<SIZE, real> R;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {

				R(i, j) = M(i, j) * c;
			}
		}

		return R;
	}




	template<int SIZE, typename real>
	inline int gaussJordan(Matrix<SIZE, real>& A, Matrix<SIZE, real>& inverse);

	//cofactor expansion

	//strassen cofactor

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
				m[i][j] = *itj;
			}
		}
	}



	/*template<int SIZE, typename real>
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
		Matrix<SIZE, real> P3 = S3.strassenMult(B11, n / 2);
		Matrix<SIZE, real> P4 = A22.strassenMult(S4, n / 2);
		Matrix<SIZE, real> P5 = S5.strassenMult(S6, n / 2);
		Matrix<SIZE, real> P6 = S7.strassenMult(S8, n / 2);
		Matrix<SIZE, real> P7 = S9.strassenMult(S10, n / 2);


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
	}*/
	

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::mul(Matrix<SIZE, real>& B)
	{
		Matrix<SIZE, real> C;

		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {

				C(i, j) = (real)0.0;
				for (int k = 0; k < SIZE; k++) {
					C(i, j) += (*this)(i, k) * B(j, k);


				}

			}
		}

		return C;
	}

	template<int SIZE, typename real>
	inline void Matrix<SIZE, real>::transpose()
	{
		for (int i = 0; i < SIZE; i++) {

			for (int j = i; j < SIZE; j++) {

				std::swap((*this)(i, j), (*this)(j, i));
			}
		}
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::getTranspose()
	{
		Matrix<SIZE, real> transp = *this;
		transp.transpose();
		return transp;

	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real> Matrix<SIZE, real>::operator+(Matrix<SIZE, real>& mat)
	{
		Matrix<SIZE, real> C;
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				C(i, j) = m[i][j] + mat(i, j);

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
				C(i, j) = m[i][j] + mat(i, j);

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
				C(i, j) = m[i][j] - mat(i, j);

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
				C(i, j) = m[i][j] - mat(i, j);

			}
		}

		return C;
	}

	template<int SIZE, typename real>
	inline real& Matrix<SIZE, real>::operator()(int row, int col)
	{
		if (row >= SIZE || col >= SIZE || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return m[row][col];
	}

	template<int SIZE, typename real>
	inline const real& Matrix<SIZE, real>::operator()(int row, int col) const
	{
		if (row >= SIZE || col >= SIZE || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return m[row][col];
	}

	template<int SIZE, typename real>
	inline bool Matrix<SIZE, real>::operator==(Matrix<SIZE, real>& mat)
	{
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				if (!(*this)(i, j) != mat(i, j))
					return false;

			}
		}

		return true;
	}

	template<int SIZE, typename real>
	inline Matrix<SIZE, real>& Matrix<SIZE, real>::operator=(const Matrix<SIZE, real>& mat)
	{
		if (this != &mat) {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					this->m[i][j] = mat(i, j);
				}
			}
		}
		return *this;
	}

	template<int SIZE, typename real>
	inline void Matrix<SIZE, real>::operator*=(real c)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {

				m[i][j] *= c;
			}

		}
	}

	template<int SIZE, typename real>
	inline Vector<SIZE, real> Matrix<SIZE, real>::operator()(int row)
	{
		return getRow(row);
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

	//no support for 3x3 (because needed extra block to make 4x4 use regular 0(n^3) mult)
	template<typename real>
	inline Matrix<2, real> strassenMulti(Matrix<2, real>& A, Matrix<2, real>& B);

	template<typename real>
	inline Matrix<1, real> strassenMulti(Matrix<1, real>& A, Matrix<1, real>& B);

	template<typename real>
	inline Matrix<4, real> strassenMulti(Matrix<4, real>& A, Matrix<4, real>& B);

	

	



	template<typename real>
	inline Matrix<4, real> strassenMulti(Matrix<4, real>& A, Matrix<4, real>& B)
	{
		Matrix<4, real> C;
		Matrix<2, real> A11, A12, A21, A22;
		Matrix<2, real> B11, B12, B21, B22;
		int m = 2;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				A11(i, j) = A(i, j);
				A12(i, j) = A(i, j + m);
				A21(i, j) = A(i + m, j);
				A22(i, j) = A(i + m, j + m);

				B11(i, j) = B(i, j);
				B12(i, j) = B(i, j + m);
				B21(i, j) = B(i + m, j);
				B22(i, j) = B(i + m, j + m);
			}
		}
		Matrix<2, real> S1 = B12 - B22;
		Matrix<2, real> S2 = A11 + A12;
		Matrix<2, real> S3 = A21 + A22;
		Matrix<2, real> S4 = B21 - B11;
		Matrix<2, real> S5 = A11 + A22;
		Matrix<2, real> S6 = B11 + B22;
		Matrix<2, real> S7 = A12 - A22;
		Matrix<2, real> S8 = B21 + B22;
		Matrix<2, real> S9 = A11 - A21;
		Matrix<2, real> S10 = B11 + B12;

		
		Matrix<2, real> P1 = strassenMulti<real>(A11, S1);
		Matrix<2, real> P2 = strassenMulti<real>(S2, B22);
		Matrix<2, real> P3 = strassenMulti<real>(S3, B11);
		Matrix<2, real> P4 = strassenMulti<real>(A22, S4);
		Matrix<2, real> P5 = strassenMulti<real>(S5, S6);
		Matrix<2, real> P6 = strassenMulti<real>(S7, S8);
		Matrix<2, real> P7 = strassenMulti<real>(S9, S10);



		Matrix<2, real> C11 = P5 + P4 - P2 + P6;
		Matrix<2, real> C12 = P1 + P2;
		Matrix<2, real> C21 = P3 + P4;
		Matrix<2, real> C22 = P5 + P1 - P3 - P7;

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

	

	template<typename real>
	inline Matrix<2, real> strassenMulti(Matrix<2, real>& A, Matrix<2, real>& B)
	{
		Matrix<2, real> C;
		Matrix<1, real> A11, A12, A21, A22;
		Matrix<1, real> B11, B12, B21, B22;
		int m = 1;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				A11(i, j) = A(i, j);
				A12(i, j) = A(i, j + m);
				A21(i, j) = A(i + m, j);
				A22(i, j) = A(i + m, j + m);

				B11(i, j) = B(i, j);
				B12(i, j) = B(i, j + m);
				B21(i, j) = B(i + m, j);
				B22(i, j) = B(i + m, j + m);
			}
		}
		Matrix<1, real> S1 = B12 - B22;
		Matrix<1, real> S2 = A11 + A12;
		Matrix<1, real> S3 = A21 + A22;
		Matrix<1, real> S4 = B21 - B11;
		Matrix<1, real> S5 = A11 + A22;
		Matrix<1, real> S6 = B11 + B22;
		Matrix<1, real> S7 = A12 - A22;
		Matrix<1, real> S8 = B21 + B22;
		Matrix<1, real> S9 = A11 - A21;
		Matrix<1, real> S10 = B11 + B12;


		Matrix<1, real> P1 = strassenMulti<real>(A11, S1);
		Matrix<1, real> P2 = strassenMulti<real>(S2, B22);
		Matrix<1, real> P3 = strassenMulti<real>(S3, B11);
		Matrix<1, real> P4 = strassenMulti<real>(A22, S4);
		Matrix<1, real> P5 = strassenMulti<real>(S5, S6);
		Matrix<1, real> P6 = strassenMulti<real>(S7, S8);
		Matrix<1, real> P7 = strassenMulti<real>(S9, S10);



		Matrix<1, real> C11 = P5 + P4 - P2 + P6;
		Matrix<1, real> C12 = P1 + P2;
		Matrix<1, real> C21 = P3 + P4;
		Matrix<1, real> C22 = P5 + P1 - P3 - P7;

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


	template<typename real>
	inline Matrix<1, real> strassenMulti(Matrix<1, real>& A, Matrix<1, real>& B) 
	{
		Matrix<1, real> C;
		C(0, 0) = A(0, 0) * B(0, 0);
		return C;



	}


	typedef Matrix<4, float> Matrix4f;
	typedef Matrix<2, float> Matrix2f;
	typedef Matrix<1, float> Matrix1f;
	typedef Matrix<3, float> Matrix3f;

	typedef Matrix<4, double> Matrix4d;
	typedef Matrix<2, double> Matrix2d;
	typedef Matrix<1, double> Matrix1d;
	typedef Matrix<3, double> Matrix3d;

	//todo make intrinsic functions for matrix mult

#include "Matrix.inl"


}