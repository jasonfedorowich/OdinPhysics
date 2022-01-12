#pragma once
#include "OdinMath.h"

namespace OdinMath {

	template<typename real>
	struct OMatrix3 : public Matrix<3, real> {
		OMatrix3() : OMatrix3((real)1.f, (real)0.f, (real)0.f,
			(real)0.f, (real)1.f, (real)0.f,
			(real)0.f, (real)0.f, (real)1.f) {}
		OMatrix3(real _00, real _01, real _02,
			real _10, real _11, real _12,
			real _20, real _21, real _22);



		OMatrix3(const OMatrix3& other) { *this = other; }
		~OMatrix3() {}

		void set(int r, int c, real v) { (*this)(r, c) = v; }

		OMatrix3& operator=(const OMatrix3& matrix);



		/*OMatrix3 mul(OMatrix3& m);
		OMatrix3 mul(OMatrix3&& m);*/

		////DXVector4 mul(DXVector4& v);
		////DXVector4 mul(DXVector4&& v);

		////DXMatrix4 mul(float scale);

		////DXMatrix4 add(DXMatrix4& m);
		////DXMatrix4 add(DXMatrix4&& m);

		////DXMatrix4 add(int increment);
		////DXMatrix4 add(float increment);

		OMatrix3 operator*(OMatrix3& matrix);
		OMatrix3 operator*(OMatrix3&& m);

		//todo
		/*A = A * M */
		void operator*=(OMatrix3& m);
		void operator*=(OMatrix3&& m);

		///*A = M * A */
		void operator%=(OMatrix3& M);
		//void operator%=(OMatrix3&& M);

		OVector3<real> operator*(OVector3<real>& v);
		//OMatrix3 operator*(OVector4&& v);

		OVector3<real>& operator*=(OVector3<real>& v);
		////DXVector4& operator*=(DXVector4&& v);

		OMatrix3 operator*(real scale);
		void operator*=(real scale);

		OMatrix3 operator+(OMatrix3& matrix);
		//OMatrix3 operator+(OMatrix3&& m);


		OMatrix3 operator-(OMatrix3& matrix);
		//OMatrix3 operator-(OMatrix3&& m);

		void operator-=(OMatrix3& m);
		void operator-=(OMatrix3&& m);

		void operator+=(OMatrix3& m);
		void operator+=(OMatrix3&& m);

		bool operator==(OMatrix3& m);
		bool operator==(OMatrix3&& m);


		////DXMatrix4& operator+=(int increment);



		bool invert(real epsilon = Math<real>::eps, real* determinant = nullptr);
		void transpose();

		OMatrix3<real> getInverse(real epsilon = Math<real>::eps, real* determinant = nullptr);
		OMatrix3<real> getTranspose();

		real& back() { return this->m[3][3]; }
		const real& back() const { return this->m[3][3]; }
		real& front() { return this->m[0][0]; }
		const real& front() const { return this->m[0][0]; }
		real determinant();

		real trace();
		real traceSq();

		////DXVector4 determinant();

		OVector4<real> getCol(int c) {
			if (c >= 4 || c < 0)
				throw std::invalid_argument("Invalid argument");
			return OVector4<real>(this->m[0][c], this->m[1][c], this->m[2][c], this->m[3][c]);
		}
		OVector4<real> getRow(int r) {
			if (r >= 4 || r < 0)
				throw std::invalid_argument("Invalid argument");
			return OVector4<real>(this->m[r][0], this->m[r][1], this->m[r][2], this->m[r][3]);
		}
		OVector4<real> diag() { return OVector4<real>((*this)(0, 0), (*this)(1, 1), (*this)(2, 2), (*this)(3, 3)); }
		////todo remove these as they are trace
		void setCol(int c, const OVector4<real>& v) {
			(*this)(0, c) = v[0];
			(*this)(1, c) = v[1];
			(*this)(2, c) = v[2];
			(*this)(3, c) = v[3];
		}
		void setCol(int c, OVector4<real>&& v);

		void setRow(int r, const OVector4<real>& v) {
			(*this)(r, 0) = v[0];
			(*this)(r, 1) = v[1];
			(*this)(r, 2) = v[2];
			(*this)(r, 3) = v[3];
		}
		void setRow(int r, OVector4<real>&& v);
		void swapRows(int i, int j);


		static OMatrix3<real> identity() { return OMatrix3<real>(); }
		static OMatrix3<real> zeros() {
			return OMatrix3<real>((real)0.f, (real)0.f, (real)0.f,
				(real)0.f, (real)01.f, (real)0.f,
				(real)0.f, (real)0.f, (real)0.f);
		}


	};

#include "OMatrix3.inl"

	template<typename real>
	inline OMatrix3<real>::OMatrix3(real _00, real _01, real _02, real _10, real _11, real _12, real _20, real _21, real _22)
	{
		this->m[0][0] = _00;
		this->m[0][1] = _01;
		this->m[0][2] = _02;

		this->m[1][0] = _10;
		this->m[1][1] = _11;
		this->m[1][2] = _12;

		this->m[2][0] = _20;
		this->m[2][1] = _21;
		this->m[2][2] = _22;

	}
	template<typename real>
	inline OMatrix3<real>& OMatrix3<real>::operator=(const OMatrix3& matrix)
	{
		if (this != &matrix) {

			storeMatrix3<real>(matrix, *this);
		}
		return *this;
	}

	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::operator*(OMatrix3<real>& matrix)
	{
#if defined(INTRINSICS)
		OMatrix3<real> result;
		matMult4<real>(this->m, matrix.m, result.m);
		return result;
#else
		OMatrix3 R;
		multMatrix3(R, *this, matrix);
		return R;
#endif
	}
	template<typename real>
	inline void OMatrix3<real>::operator*=(OMatrix3<real>& matrix)
	{
#if defined(INTRINSICS)
		matMult4<real>(this->m, matrix.m, this->m);
#else
		OMatrix3 R;
		multMatrix3(R, *this, matrix);
		storeMatrix3(R, *this);
#endif
	}
	template<typename real>
	inline void OMatrix3<real>::operator%=(OMatrix3<real>& matrix)
	{
#if defined(INTRINSICS)
		matMult4<real>(matrix.m, this->m, this->m);
#else
		OMatrix3 R;
		multMatrix3(R, matrix, *this);
		storeMatrix3(R, *this);
#endif
	}
	template<typename real>
	inline OVector3<real> OMatrix3<real>::operator*(OVector3<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> r;
		matVect4<real>(this->m, v.data, r.data);
		return r;
#else
		OVector3<real> R;
		matrixVector3<real>(R, *this, v);
		return R;
#endif	
	}
	template<typename real>
	inline OVector3<real>& OMatrix3<real>::operator*=(OVector3<real>& v)
	{
#if defined(INTRINSICS)
		matVect4<real>(this->m, v.data, v.data);
		return v;
#else
		OVector3<real> copy;
		matrixVector3<real>(copy, *this, v.data);
		v = copy;
		return v;
#endif
	}
	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::operator*(real scale)
	{
#if defined(INTRINSICS)
		OMatrix3<real> R;
		matScale4<real>(this->m, scale, R.m);
		return R;
#else
		OVector3<real> R;
		matrixScale3<real>(R, *this, scale);
		return R;
#endif
	}
	template<typename real>
	inline void OMatrix3<real>::operator*=(real scale)
	{
#if defined(INTRINSICS)
		OMatrix3<real> R;
		matScale4<real>(this->m, scale, this->m);
#else
		OVector3<real> R;
		matrixScale3<real>(R, *this, scale);
		*this = R;

#endif
	}
	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::operator+(OMatrix3& matrix)
	{
#if defined(INTRINSICS)
		OMatrix3<real> R;
		addMat4<real>(this->m, matrix.m, R.m);
		return R;
#else
		OVector3<real> R;
		addMatrix3(R, *this, matrix);
		return R;

#endif
	}
	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::operator-(OMatrix3<real>& matrix)
	{
#if defined(INTRINSICS)
		OMatrix3<real> R;
		subMat4<real>(this->m, matrix.m, R.m);
		return R;
#else
		OVector3<real> R;
		subMatrix3(R, *this, matrix);
		return R;

#endif
	}
	template<typename real>
	inline void OMatrix3<real>::operator-=(OMatrix3& matrix)
	{
#if defined(INTRINSICS)
		OMatrix3<real> R;
		subMat4<real>(this->m, matrix.m, this->m);
		return R;
#else
		OVector3<real> R;
		subMatrix3(R, *this, matrix);
		*this = R;

#endif

	}
	template<typename real>
	inline void OMatrix3<real>::operator+=(OMatrix3& matrix)
	{
#if defined(INTRINSICS)
		addMat4<real>(this->m, matrix.m, this->m);
#else
		OVector3<real> R;
		addMatrix3(R, *this, matrix);
		*this = R;

#endif

	}
	template<typename real>
	inline bool OMatrix3<real>::operator==(OMatrix3& matrix)
	{
#if defined(INTRINSICS)
		return matEquals4<real>(this->m, matrix.m);
#else
		return matrixEquals3<real>( *this, matrix);

#endif	
	}

	template<typename real>
	inline bool OMatrix3<real>::invert(real epsilon, real* determinant)
	{
#if defined(INTRINSICS)
		return invert4<real>(this->m, this->m, epsilon, determinant);
#else
		return invertMat3<real>(this->m, this->m, epsilon, determinant);

#endif		
	}

	template<typename real>
	inline void OMatrix3<real>::transpose()
	{
#if defined(INTRINSICS)
		transpose4<real>(this->m, this->m);
#else
		matTranspose3<real>(this->m, this->m);

#endif		
	}

	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::getInverse(real epsilon, real* determinant)
	{
#if defined(INTRINSICS)
		OMatrix3<real> O;
		invert4<real>(this->m, O.m, epsilon, determinant);
		return O;
#else
		OMatrix3<real> O;
		return invertMat3<real>(this->m, O.m, epsilon, determinant);

#endif		
	}

	template<typename real>
	inline OMatrix3<real> OMatrix3<real>::getTranspose()
	{
#if defined(INTRINSICS)
		OMatrix3<real> O;
		transpose4<real>(this->m, O.m);
		return O;
#else
		OMatrix3<real> O;
		matTranspose3<real>(this->m, O.m);
		return O;

#endif		
	}

	template<typename real>
	inline real OMatrix3<real>::determinant()
	{
#if defined(INTRINSICS)
		OMatrix3<real> O;
		transpose4<real>(this->m, O.m);
		return O;
#else
		OMatrix3<real> O;
		matTranspose3<real>(this->m, O.m);
		return O;

#endif		
	}

	template<typename real>
	inline real OMatrix3<real>::trace()
	{
#if defined(INTRINSICS)
		
		return trace4<real>(this->m);
		
#else
		return this->m[0][0] + this->m[1][1] + this->m[2][2];

#endif	
	}

	template<typename real>
	inline real OMatrix3<real>::traceSq()
	{
#if defined(INTRINSICS)

		return traceSq4<real>(this->m);

#else
		return this->m[0][0] * this->m[0][0] + this->m[1][1] * this->m[1][1] + this->m[2][2] * this->m[2][2];

#endif	
	}

	template<typename real>
	inline void OMatrix3<real>::swapRows(int i, int j)
	{
		Math<real>::odSwap(&this(i, 0), &this(j, 0));
		Math<real>::odSwap(&this(i, 1), &this(j, 1));
		Math<real>::odSwap(&this(i, 2), &this(j, 2));
	}
	
}