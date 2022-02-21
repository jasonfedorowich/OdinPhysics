#pragma once
#include "OdinMath.h"

namespace OdinMath {


	template<typename real>
	struct OMatrix2 : Matrix<2, real> {
		OMatrix2() : OMatrix2((real)1.f, (real)0.f,
			(real)0.f, (real)1.f) {}
		OMatrix2(real _00, real _01,
			real _10, real _11);

		OMatrix2(real v) : OMatrix2(v, v, v, v) {}
		OMatrix2(OVector2<real> rows[2]);
		OMatrix2(OVector2<real>& rows);
		OMatrix2(OVector2<real>&& rows);

		OMatrix2(const OMatrix2& other) { *this = other; }
		~OMatrix2() {}


		void set(int r, int c, real v) { (*this)(r, c) = v; }

		OMatrix2<real>& operator=(const OMatrix2<real>& matrix);



		/*OMatrix3 mul(OMatrix3& m);
		OMatrix3 mul(OMatrix3&& m);*/

		////DXVector4 mul(DXVector4& v);
		////DXVector4 mul(DXVector4&& v);

		////DXMatrix4 mul(float scale);

		////DXMatrix4 add(DXMatrix4& m);
		////DXMatrix4 add(DXMatrix4&& m);

		////DXMatrix4 add(int increment);
		////DXMatrix4 add(float increment);

		OMatrix2<real> operator*(OMatrix2<real>& matrix);
		OMatrix2<real> operator*(OMatrix2<real>&& m);

		//todo
		/*A = A * M */
		void operator*=(OMatrix2<real>& m);
		void operator*=(OMatrix2<real>&& m);

		///*A = M * A */
		void operator%=(OMatrix2<real>& M);
		//void operator%=(OMatrix3&& M);

		OVector2<real> operator*(OVector2<real>& v);
		//OMatrix3 operator*(OVector4&& v);

		OVector2<real>& operator*=(OVector2<real>& v);
		////DXVector4& operator*=(DXVector4&& v);

		OMatrix2<real> operator*(real scale);
		void operator*=(real scale);

		OMatrix2<real> operator+(OMatrix2<real>& matrix);
		//OMatrix3 operator+(OMatrix3&& m);


		OMatrix2<real> operator-(OMatrix2<real>& matrix);
		//OMatrix3 operator-(OMatrix3&& m);

		void operator-=(OMatrix2<real>& matrix);
		void operator-=(OMatrix2<real>&& matrix);

		void operator+=(OMatrix2<real>& matrix);
		void operator+=(OMatrix2<real>&& matrix);

		bool operator==(OMatrix2<real>& matrix);
		bool operator==(OMatrix2<real>&& matrix);


		////DXMatrix4& operator+=(int increment);

		OMatrix2<real> multTrans(OMatrix3<real>& B);

		bool invert(real epsilon = Math<real>::eps, real* determinant = nullptr);
		void transpose();

		OMatrix2<real> getInverse(real epsilon = Math<real>::eps, real* determinant = nullptr);
		OMatrix2<real> getTranspose();

		real& back() { return this->m[3][3]; }
		const real& back() const { return this->m[3][3]; }
		real& front() { return this->m[0][0]; }
		const real& front() const { return this->m[0][0]; }
		real determinant();

		real trace();
		real traceSq();

		void absM();

		////DXVector4 determinant();

		OVector2<real> getCol(int c) {
			if (c >= 2 || c < 0)
				throw std::invalid_argument("Invalid argument");
			return OVector2<real>(this->m[0][c], this->m[1][c]);
		}
		OVector2<real> getRow(int r) {
			if (r >= 2 || r < 0)
				throw std::invalid_argument("Invalid argument");
			return OVector2<real>(this->m[r][0], this->m[r][1]);
		}
		OVector2<real> diag() { return OVector2<real>((*this)(0, 0), (*this)(1, 1)); }
		////todo remove these as they are trace
		void setCol(int c, const OVector2<real>& v) {
			(*this)(0, c) = v[0];
			(*this)(1, c) = v[1];
		}
		void setCol(int c, OVector2<real>&& v);

		void setRow(int r, const OVector2<real>& v) {
			(*this)(r, 0) = v[0];
			(*this)(r, 1) = v[1];
	
		}
		void setRow(int r, OVector2<real>&& v) {
			(*this)(r, 0) = v[0];
			(*this)(r, 1) = v[1];
		}
		void swapRows(int i, int j);


		static OMatrix2<real> identity() { return OMatrix2<real>(); }
		static OMatrix2<real> zeros() {
			return OMatrix2<real>((real)0.f, (real)0.f,
				(real)0.f, (real)0.f);
		}


	};

#include "OMatrix2.inl"

	//inline functions
	template<typename real>
	inline OMatrix2<real> operator*(float scale, OMatrix2<real>& m) {
		OMatrix2<real> res;
#if defined(INTRINSICS)
		matScale4<real, 2>(m.data, scale, res.data);
#else
		m(0, 0) *= scale;
		m(0, 1) *= scale;

		m(1, 0) *= scale;
		m(1, 1) *= scale;
#endif
		return res;
	}
	template<typename real>
	inline void operator*=(OVector2<real>& vector, OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		vectMatMult4(vector.data, matrix.m, vector.data);
#else
		real t1 = vector[0];
		real t2 = vector[1];

		vector[0] = t1 * matrix(0, 0) + t2 * matrix(1, 0);
		vector[1] = t1 * matrix(0, 1) + t2 * matrix(1, 1);
#endif

	}
	template<typename real>
	inline OVector2<real> operator*(OVector2<real>& vector, OMatrix2<real>& matrix)
	{
		OVector3<real> result;
#if defined(INTRINSICS)

		vectMatMult4(vector.data, matrix.m, result.data);

#else
		real t1 = vector[0];
		real t2 = vector[1];

		result[0] = t1 * matrix(0, 0) + t2 * matrix(1, 0);
		result[1] = t1 * matrix(0, 1) + t2 * matrix(1, 1);
#endif
		return result;
	}

	template<typename real>
	inline void outerProduct(OMatrix2<real>& matrix, const OVector2<real>& v1, const OVector2<real>& v2) {
#if defined(INTRINSICS)
		outerProduct4(v1.data, v2.data, matrix.m);
#else
		matrix(0, 0) = v1[0] * v2[0];
		matrix(0, 1) = v1[0] * v2[1];

		matrix(1, 0) = v1[1] * v2[0];
		matrix(1, 1) = v1[1] * v2[1];

#endif


	}





	template<typename real>
	inline OMatrix2<real>::OMatrix2(real _00, real _01, real _10, real _11)
	{
		this->m[0][0] = _00;
		this->m[0][1] = _01;
		this->m[1][0] = _10;
		this->m[1][1] = _11;
	}
	template<typename real>
	inline OMatrix2<real>::OMatrix2(OVector2<real> rows[2])
	{
		this->m[0][0] = rows[0][0];
		this->m[0][1] = rows[0][1];

		this->m[1][0] = rows[1][0];
		this->m[1][1] = rows[1][1];

	}
	template<typename real>
	inline OMatrix2<real>::OMatrix2(OVector2<real>&& rows)
	{
		this->m[0][0] = rows[0];
		this->m[0][1] = rows[1];

		this->m[1][0] = rows[0];
		this->m[1][1] = rows[1];
	}
	template<typename real>
	inline OMatrix2<real>::OMatrix2(OVector2<real>& rows)
	{
		this->m[0][0] = rows[0];
		this->m[0][1] = rows[1];

		this->m[1][0] = rows[0];
		this->m[1][1] = rows[1];
	}
	template<typename real>
	inline OMatrix2<real>& OMatrix2<real>::operator=(const OMatrix2<real>& matrix)
	{
		if (this != &matrix) {

			storeMatrix2<real>(matrix, *this);
		}
		return *this;

	}
	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::operator*(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		OMatrix2<real> result;
		matMult4<real, 2>(this->m, matrix.m, result.m);
		return result;
#else
		OMatrix2<real> R;
		multMatrix2(R, *this, matrix);
		return R;
#endif
	}
	template<typename real>
	inline void OMatrix2<real>::operator*=(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		matMult4<real>(this->m, matrix.m, this->m);
#else
		OMatrix2<real> R;
		multMatrix2(R, *this, matrix);
		storeMatrix2(R, *this);
#endif
	}
	template<typename real>
	inline void OMatrix2<real>::operator%=(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		matMult4<real>(matrix.m, this->m, this->m);
#else
		OMatrix2<real> R;
		multMatrix2(R, matrix, *this);
		storeMatrix2(R, *this);
#endif
	}
	template<typename real>
	inline OVector2<real> OMatrix2<real>::operator*(OVector2<real>& v)
	{
		OVector2<real> R;
#if defined(INTRINSICS)
		matVect4<real>(this->m, v.data, R.data);
#else
		matrixVector2(R, *this, v);
#endif
		return v;
	}
	template<typename real>
	inline OVector2<real>& OMatrix2<real>::operator*=(OVector2<real>& v)
	{
#if defined(INTRINSICS)
		matVect4<real>(this->m, v.data, v.data);
#else
		OVector2<real> R;
		matrixVector2(R, *this, v);
		v = R;
#endif
		return v;
	}
	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::operator*(real scale)
	{
		OMatrix2<real> R;
#if defined(INTRINSICS)
		matScale4<real>(this->m, scale, R.m);
#else
		matrixScale2<real>(R, *this, scale);
#endif
		return R;
	}
	template<typename real>
	inline void OMatrix2<real>::operator*=(real scale)
	{
#if defined(INTRINSICS)

		matScale4<real>(this->m, scale, this->m);
#else
		OMatrix2<real> R;
		matrixScale2<real>(R, *this, scale);
		*this = R;

#endif
	}
	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::operator+(OMatrix2<real>& matrix)
	{
		OMatrix2<real> R;
#if defined(INTRINSICS)
		addMat4<real>(this->m, matrix.m, R.m);
#else
		addMatrix2(R, *this, matrix);
#endif
		return R;
	}
	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::operator-(OMatrix2<real>& matrix)
	{
		OMatrix2<real> R;
#if defined(INTRINSICS)
		subMat4<real>(this->m, matrix.m, R.m);
#else
		subMatrix2(R, *this, matrix);
#endif
		return R;
	}
	template<typename real>
	inline void OMatrix2<real>::operator-=(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		subMat4<real>(this->m, matrix.m, this->m);
#else
		OMatrix2<real> R;
		subMatrix2(R, *this, matrix);
		*this = R;
#endif

	}
	template<typename real>
	inline void OMatrix2<real>::operator-=(OMatrix2<real>&& matrix)
	{
#if defined(INTRINSICS)
		subMat4<real>(this->m, matrix.m, this->m);
#else
		OMatrix2<real> R;
		subMatrix2(R, *this, matrix);
		*this = R;
#endif
	}
	template<typename real>
	inline void OMatrix2<real>::operator+=(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		addMat4<real>(this->m, matrix.m, this->m);
#else
		OMatrix2<real> R;
		addMatrix2(R, *this, matrix);
		*this = R;
#endif
	}
	template<typename real>
	inline void OMatrix2<real>::operator+=(OMatrix2<real>&& matrix)
	{
#if defined(INTRINSICS)
		addMat4<real>(this->m, matrix.m, this->m);
#else
		OMatrix2<real> R;
		addMatrix2(R, *this, matrix);
		*this = R;
#endif
	}
	template<typename real>
	inline bool OMatrix2<real>::operator==(OMatrix2<real>& matrix)
	{
#if defined(INTRINSICS)
		return matEquals4<real>(this->m, matrix.m);
#else
		return matrixEquals2<real>(*this, matrix);

#endif	
	}
	template<typename real>
	inline bool OMatrix2<real>::operator==(OMatrix2<real>&& matrix)
	{
#if defined(INTRINSICS)
		return matEquals4<real>(this->m, matrix.m);
#else
		return matrixEquals2<real>(*this, matrix);

#endif	

	}

	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::multTrans(OMatrix3<real>& mat)
	{
		OMatrix2<real> res;
#if defined(INTRINSICS)
		matMultTrans4<real, 2>(this->m, mat.m, res.m);
#else
		matrixMultTrans2<real>(*this, mat, res);
#endif
		return res;
	}

	template<typename real>
	inline bool OdinMath::OMatrix2<real>::invert(real epsilon, real* determinant)
	{
#if defined(INTRINSICS)
		return invert4<real>(this->m, this->m, epsilon, determinant);
#else
		return invertMat2<real>(this->m, this->m, epsilon, determinant);

#endif

	}
	template<typename real>
	inline void OdinMath::OMatrix2<real>::transpose()
	{
#if defined(INTRINSICS)
		transpose4<real>(this->m, this->m);
#else
		matTranspose2<real>(this->m, this->m);

#endif	

	}

	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::getInverse(real epsilon, real* determinant)
	{
		OMatrix2<real> R;
#if defined(INTRINSICS)
		invert4<real>(this->m, R.m, epsilon, determinant);
#else
		invertMat2<real>(this->m, R.m, epsilon, determinant);

#endif
		return R;
	}

	template<typename real>
	inline OMatrix2<real> OMatrix2<real>::getTranspose()
	{
		OMatrix2<real> R;
#if defined(INTRINSICS)
		transpose4<real>(this->m, R.m);
#else
		matTranspose2<real>(this->m, R.m);

#endif	
	}

	template<typename real>
	inline real OMatrix2<real>::determinant()
	{
#if defined(INTRINSICS)
		return determinant4<real>(this->m);

#else
		return matDeterminant2<real>(this->m);

#endif		
	}

	template<typename real>
	inline real OMatrix2<real>::trace()
	{
#if defined(INTRINSICS)

		return trace4<real>(this->m);

#else
		return this->m[0][0] + this->m[1][1];

#endif	

	}

	template<typename real>
	inline real OMatrix2<real>::traceSq()
	{
#if defined(INTRINSICS)

		return traceSq4<real>(this->m);

#else
		return this->m[0][0] * this->m[0][0] + this->m[1][1] * this->m[1][1];

#endif	
	}

	template<typename real>
	inline void OMatrix2<real>::absM()
	{
#if defined(INTRINSICS)
		absM4<real>(this->m, this->m);
#else

		this->m[0][0] = Math<rl>::odAbs(this->m[0][0]);
		this->m[0][1] = Math<rl>::odAbs(this->m[0][1]);

		this->m[1][0] = Math<rl>::odAbs(this->m[1][0]);
		this->m[1][1] = Math<rl>::odAbs(this->m[1][1]);


#endif
	}

	template<typename real>
	inline void OMatrix2<real>::swapRows(int i, int j)
	{
		if (i >= 2 || i < 0 || j >= 2 || j < 0)
			throw std::invalid_argument("Cannot swap invalid rows");
		Math<real>::odSwap(&this->m[0][0], &this->m[0][1]);
		Math<real>::odSwap(&this->m[0][1], &this->m[1][1]);
	}


}
