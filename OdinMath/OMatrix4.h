#pragma once
#include "OdinMath.h"

namespace OdinMath {
	template<typename real>
	struct OMatrix4 : public Matrix<4, real> {
		OMatrix4() : OMatrix4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f) {}
		OMatrix4(real _00, real _01, real _02, real _03,
			real _10, real _11, real _12, real _13,
			real _20, real _21, real _22, real _23,
			real _30, real _31, real _32, real _33);

	
		
		OMatrix4(const OMatrix4& other) { *this = other; }
		~OMatrix4() {}

		void set(int r, int c, float v) { (*this)(r, c) = v; }

		OMatrix4& operator=(const OMatrix4& matrix);
		//float& operator()(int row, int col);
		//const float& operator()(int row, int col) const;


		/*OMatrix4 mul(OMatrix4& m);
		OMatrix4 mul(OMatrix4&& m);*/

		////DXVector4 mul(DXVector4& v);
		////DXVector4 mul(DXVector4&& v);

		////DXMatrix4 mul(float scale);

		////DXMatrix4 add(DXMatrix4& m);
		////DXMatrix4 add(DXMatrix4&& m);

		////DXMatrix4 add(int increment);
		////DXMatrix4 add(float increment);

		OMatrix4 operator*(OMatrix4& matrix);
		OMatrix4 operator*(OMatrix4&& m);

		//todo
		/*A = A * M */
		void operator*=(OMatrix4& m);
		void operator*=(OMatrix4&& m);

		///*A = M * A */
		//void operator%=(OMatrix4& M);
		//void operator%=(OMatrix4&& M);

		//OMatrix4 operator*(OVector4& v);
		//OMatrix4 operator*(OVector4&& v);

		////DXVector4& operator*=(DXVector4& v);
		////DXVector4& operator*=(DXVector4&& v);

		//OMatrix4 operator*(float scale);
		//void operator*=(float scale);

		//OMatrix4 operator+(OMatrix4& matrix);
		//OMatrix4 operator+(OMatrix4&& m);

		////DXMatrix4& operator+=(DXMatrix4& m);
		////DXMatrix4& operator+=(DXMatrix4&& m);

		//OMatrix4 operator-(OMatrix4& matrix);
		//OMatrix4 operator-(OMatrix4&& m);

		//void operator-=(OMatrix4& m);
		//void operator-=(OMatrix4&& m);

		//void operator+=(OMatrix4& m);
		//void operator+=(OMatrix4&& m);

		//bool operator==(OMatrix4& m);
		//bool operator==(OMatrix4&& m);


		////DXMatrix4& operator+=(int increment);



		//void invert();
		//void transpose();

		//OMatrix4 getInverse();
		//OMatrix4 getTranspose();

		float& back() { return this->m[3][3]; }
		const float& back() const { return this->m[3][3]; }
		float& front() { return this->m[0][0]; }
		//const float& front() const { return m[0][0]; }
		//float determinant();

		//float trace() { float result = m[0][0]; result += m[1][1]; result += m[2][2]; result += m[3][3]; return result; }
		//float traceSq() { float result = m[0][0] * m[0][0]; result += (m[1][1] * m[1][1]); result += (m[2][2] * m[2][2]); result += (m[3][3] * m[3][3]); return result; }

		////DXVector4 determinant();

		//OMatrix4 getCol(int c);
		//OMatrix4 getRow(int r);
		//OVector4 diag() { return OVector4((*this)(0, 0), (*this)(1, 1), (*this)(2, 2), (*this)(3, 3)); }
		////todo remove these as they are trace
		//void setCol(int c, const OVector4& v);
		//void setCol(int c, OVector4&& v);

		//void setRow(int r, const OVector4& v);
		//void setRow(int r, OVector4&& v);

		//void swapRows(int i, int j);

		//OMatrix4 identity() { return OMatrix4(); }

	

	};

	template<typename real>
	inline void storeMatrix4(const OMatrix4<real>& src, OMatrix4<real>& dest) {
		dest(0, 0) = src(0, 0);
		dest(0, 1) = src(0, 1);
		dest(0, 2) = src(0, 2);
		dest(0, 3) = src(0, 3);

		dest(1, 0) = src(1, 0);
		dest(1, 1) = src(1, 1);
		dest(1, 2) = src(1, 2);
		dest(1, 3) = src(1, 3);

		dest(2, 0) = src(2, 0);
		dest(2, 1) = src(2, 1);
		dest(2, 2) = src(2, 2);
		dest(2, 3) = src(2, 3);

		dest(3, 0) = src(3, 0);
		dest(3, 1) = src(3, 1);
		dest(3, 2) = src(3, 2);
		dest(3, 3) = src(3, 3);
	}
	template<typename real>
	inline void addMatrix4(OMatrix4<real>& A, OMatrix4<real>& B, OMatrix4<real>& R) {
		R(0, 0) = A(0, 0) + B(0, 0);
		R(0, 1) = A(0, 1) + B(0, 1);
		R(0, 2) = A(0, 2) + B(0, 2);
		R(0, 3) = A(0, 3) + B(0, 3);

		R(1, 0) = A(1, 0) + B(1, 0);
		R(1, 1) = A(1, 1) + B(1, 1);
		R(1, 2) = A(1, 2) + B(1, 2);
		R(1, 3) = A(1, 3) + B(1, 3);

		R(2, 0) = A(2, 0) + B(2, 0);
		R(2, 1) = A(2, 1) + B(2, 1);
		R(2, 2) = A(2, 2) + B(2, 2);
		R(2, 3) = A(2, 3) + B(2, 3);


		R(3, 0) = A(3, 0) + B(3, 0);
		R(3, 1) = A(3, 1) + B(3, 1);
		R(3, 2) = A(3, 2) + B(3, 2);
		R(3, 3) = A(3, 3) + B(3, 3);
	}
	template<typename real>
	inline void multMatrix4(OMatrix4<real>& R, OMatrix4<real>& A, OMatrix4<real>& B) {
		R(0, 0) = A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0) + A(0, 3) * B(3, 0);
		R(0, 1) = A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1) + A(0, 3) * B(3, 1);
		R(0, 2) = A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2) + A(0, 3) * B(3, 2);
		R(0, 3) = A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3) * B(3, 3);

		R(1, 0) = A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0) + A(1, 3) * B(3, 0);
		R(1, 1) = A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1) + A(1, 3) * B(3, 1);
		R(1, 2) = A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2) + A(1, 3) * B(3, 2);
		R(1, 3) = A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3) * B(3, 3);

		R(2, 0) = A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0) + A(2, 3) * B(3, 0);
		R(2, 1) = A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1) + A(2, 3) * B(3, 1);
		R(2, 2) = A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2) + A(2, 3) * B(3, 2);
		R(2, 3) = A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3) * B(3, 3);

		R(3, 0) = A(3, 0) * B(0, 0) + A(3, 1) * B(1, 0) + A(3, 2) * B(2, 0) + A(3, 3) * B(3, 0);
		R(3, 1) = A(3, 0) * B(0, 1) + A(3, 1) * B(1, 1) + A(3, 2) * B(2, 1) + A(3, 3) * B(3, 1);
		R(3, 2) = A(3, 0) * B(0, 2) + A(3, 1) * B(1, 2) + A(3, 2) * B(2, 2) + A(3, 3) * B(3, 2);
		R(3, 3) = A(3, 0) * B(0, 3) + A(3, 1) * B(1, 3) + A(3, 2) * B(2, 3) + A(3, 3) * B(3, 3);


	}
	

	template<typename real>
	inline OMatrix4<real>::OMatrix4(real _00, real _01, real _02, real _03, real _10, real _11, real _12, real _13, real _20, real _21, real _22, real _23, real _30, real _31, real _32, real _33)
	{
		this->m[0][0] = _00;
		this->m[0][1] = _01;
		this->m[0][2] = _02;
		this->m[0][3] = _03;
		
		this->m[1][0] = _10;
		this->m[1][1] = _11;
		this->m[1][2] = _12;
		this->m[1][3] = _13;

		this->m[2][0] = _20;
		this->m[2][1] = _21;
		this->m[2][2] = _22;
		this->m[2][3] = _23;

		this->m[3][0] = _30;
		this->m[3][1] = _31;
		this->m[3][2] = _32;
		this->m[3][3] = _33;
	}

	template<typename real>
	inline OMatrix4<real>& OMatrix4<real>::operator=(const OMatrix4<real>& matrix)
	{
		if (this != &matrix) {
			storeMatrix4<real>(matrix, *this);
		}
		return *this;
	}

	template<typename real>
	inline OMatrix4<real> OMatrix4<real>::operator*(OMatrix4<real>& matrix)
	{
		OMatrix4 R;
		multMatrix4(R, *this, matrix);
		return R;
	}

	

}
