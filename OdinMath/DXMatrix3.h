#pragma once
#include "OdinMath.h"

namespace OdinMath {

	struct DXMatrix3 : XMFLOAT3X3 {

		DXMatrix3() : DXMatrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f) {}
		DXMatrix3(float _00, float _01, float _02,
			float _10, float _11, float _12,
			float _20, float _21, float _22);

		DXMatrix3(const DXMatrix3& m) { *this = m; }
		DXMatrix3(XMFLOAT3X3& m);
		DXMatrix3(XMMATRIX& m) { store(m); }
		DXMatrix3(XMMATRIX&& m) { store(m); }

		const float& operator()(int r, int c) const;
		float& operator()(int r, int c);

		DXMatrix3& operator=(const DXMatrix3& m);

		DXMatrix3 operator+(const DXMatrix3& m);
		DXMatrix3 operator*(const DXMatrix3& m);

		DXVector3 operator*(DXVector3& v);
		DXVector3 operator*(DXVector3&& v);

		void operator*=(const DXMatrix3& m);
		void operator+=(const DXMatrix3& m);
		void operator%=(const DXMatrix3& m);
		void operator-=(const DXMatrix3& m);
		void operator-=(const DXMatrix3&& m);
		void operator*=(float scale);

		DXVector3 getRow(int r);
		DXVector3 getCol(int c);
		void setRow(int r, const DXVector3& v);
		void setRow(int r, const DXVector3&& v);
		void setCol(int c, const DXVector3& v);
		void setCol(int c, const DXVector3&& v);

		void swapRows(int i, int j);

		DXMatrix3 getInverse();
		void invert();

		float& back() { return m[2][2]; }
		const float& back() const { return m[2][2]; }
		float& front() { return m[0][0]; }
		const float& front() const { return m[0][0]; }

		float trace() { float result = m[0][0]; result += m[1][1]; result += m[2][2]; return result; }
		float traceSq(){ float result = m[0][0] * m[0][0]; result += (m[1][1] * m[1][1]); result += (m[2][2] * m[2][2]); return result; }

		DXVector3 diag() { return DXVector3((*this)(0, 0), (*this)(1, 1), (*this)(2, 2)); }
		

		float determinant();

		DXMatrix3 getTranspose();
		void transpose();

		void store(XMMATRIX& m) { XMStoreFloat3x3(this, m); }
		void store(XMMATRIX&& m) { XMStoreFloat3x3(this, m); }
		XMMATRIX getXMMatrix() const { return XMLoadFloat3x3(this); } 
		

	};


	inline void operator*=(DXVector3& vector, DXMatrix3& matrix)
	{
		XMVECTOR xmvector = vector.getXMVector();
		XMMATRIX xmmatrix = matrix.getXMMatrix();

		xmvector = XMVector4Transform(xmvector, xmmatrix);
		
	}

	inline DXVector3 operator*(DXVector3& vector, DXMatrix3& matrix)
	{
		XMVECTOR xmvector = vector.getXMVector();
		XMMATRIX xmmatrix = matrix.getXMMatrix();

		xmvector = XMVector4Transform(xmvector, xmmatrix);
		return DXVector3(xmvector);
	}

	inline void outerProduct(DXMatrix3& matrix, const DXVector3& v1, const DXVector3& v2) {
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {
				matrix(i, j) = v1[i] * v2[j];


			}

		}


	}


}
