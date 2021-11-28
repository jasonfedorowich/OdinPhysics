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
		void operator%=(OMatrix4& M);
		//void operator%=(OMatrix4&& M);

		OVector4<real> operator*(OVector4<real>& v);
		//OMatrix4 operator*(OVector4&& v);

		OVector4<real>& operator*=(OVector4<real>& v);
		////DXVector4& operator*=(DXVector4&& v);

		OMatrix4 operator*(float scale);
		void operator*=(float scale);

		OMatrix4 operator+(OMatrix4& matrix);
		//OMatrix4 operator+(OMatrix4&& m);


		OMatrix4 operator-(OMatrix4& matrix);
		//OMatrix4 operator-(OMatrix4&& m);

		void operator-=(OMatrix4& m);
		void operator-=(OMatrix4&& m);

		void operator+=(OMatrix4& m);
		void operator+=(OMatrix4&& m);

		bool operator==(OMatrix4& m);
		bool operator==(OMatrix4&& m);


		////DXMatrix4& operator+=(int increment);



		bool invert(real epsilon = Math<real>::eps, real* determinant=nullptr);
		void transpose();

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

#include "OMatrix4.inl"



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
#if defined(INTRINSICS)
		OMatrix4<real> result;
		matMult4<real>(this->m, matrix.m, result.m);
		return result;
#else
		OMatrix4 R;
		multMatrix4(R, *this, matrix);
		return R;
#endif
		
	}

	template<typename real>
	inline void OMatrix4<real>::operator*=(OMatrix4<real>& matrix)
	{
#if defined(INTRINSICS)
		
		matMult4<real>(this->m, matrix.m, this->m);

#else
		OMatrix4 R;
		multMatrix4(R, *this, matrix);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline void OMatrix4<real>::operator%=(OMatrix4& matrix)
	{
#if defined(INTRINSICS)

		matMult4<real>(matrix.m, this->m, this->m);

#else
		OMatrix4 R;
		multMatrix4(R, matrix, *this);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline OVector4<real> OMatrix4<real>::operator*(OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> result;
		matVect4<real>(this->m, v.data, result.data);
		return result;
#else
		//todo
		OMatrix4 R;
		multMatrix4(R, matrix, *this);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline OVector4<real>& OMatrix4<real>::operator*=(OVector4<real>& v)
	{
#if defined(INTRINSICS)
		matVect4<real>(this->m, v.data, v.data);
		return v;

#else
		//todo
		OMatrix4 R;
		multMatrix4(R, matrix, *this);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline OMatrix4<real> OMatrix4<real>::operator*(float scale)
	{
#if defined(INTRINSICS)
		OMatrix4<real> R;
		matScale4<real>(this->m, scale, R.m);
		return R;
#else
		//todo
		OMatrix4 R;
		multMatrix4(R, matrix, *this);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline void OMatrix4<real>::operator*=(float scale)
	{

#if defined(INTRINSICS)
		matScale4<real>(this->m, scale, this->m);

#else
		//todo
		OMatrix4 R;
		multMatrix4(R, matrix, *this);
		storeMatrix4(R, *this);
#endif
	}

	template<typename real>
	inline OMatrix4<real> OMatrix4<real>::operator+(OMatrix4& matrix)
	{
#if defined(INTRINSICS)
		OMatrix4<real> R;
		addMat4<real>(this->m, matrix.m, R.m);
		return R;

#else
		
		OMatrix4 R;
		addMatrix4(*this, matrix, R);
		return R;
#endif
	}

	template<typename real>
	inline void OMatrix4<real>::operator+=(OMatrix4<real>& matrix)
	{
#if defined(INTRINSICS)
		addMat4<real>(this->m, matrix.m, this->m);

#else
		OMatrix4 R;
		addMatrix4(*this, matrix, R);
		return R;
#endif
	}

	template<typename real>
	inline bool OMatrix4<real>::operator==(OMatrix4& matrix)
	{
#if defined(INTRINSICS)
		return matEquals4<real>(this->m, matrix.m);

#else
		//todo
		OMatrix4 R;
		matrixEquals4(*this, matrix, R);
		return R;
#endif
	}

	template<typename real>
	inline bool OMatrix4<real>::invert(real eps, real* determinant)
	{
#if defined(INTRINSICS)
		return invert4<real>(this->m, this->m, eps, determinant);

#else
		return invertMat4(this->m, this->m, eps, determinant);
#endif
	}

	template<typename real>
	inline OMatrix4<real> OMatrix4<real>::operator-(OMatrix4<real>& matrix)
	{
#if defined(INTRINSICS)
		OMatrix4<real> R;
		subMat4<real>(this->m, matrix.m, R.m);
		return R;

#else
		//todo
		OMatrix4 R;
		subMatrix4(*this, matrix, R);
		return R;
#endif
	}

	template<typename real>
	inline void OMatrix4<real>::operator-=(OMatrix4& matrix)
	{
#if defined(INTRINSICS)
		subMat4<real>(this->m, matrix.m, this->m);

#else
		//todo
		OMatrix4 R;
		subMatrix4(*this, matrix, R);
		return R;
#endif
	}

	

}
