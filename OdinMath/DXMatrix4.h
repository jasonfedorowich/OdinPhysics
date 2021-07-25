#pragma once
#include "OdinMath.h"

namespace OdinMath {
	class DXMatrix4 : XMFLOAT4X4 {

	public:
		DXMatrix4() : DXMatrix4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f) {}
		DXMatrix4(float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33);
		
		DXMatrix4(XMMATRIX matrix) { XMStoreFloat4x4(this, matrix); }
		DXMatrix4(XMFLOAT4X4& xmfloat4x4);
		DXMatrix4(const DXMatrix4& other) { *this = other; }
		~DXMatrix4() {}

		void set(int r, int c, float v) { (*this)(r, c) = v; }

		DXMatrix4& operator=(const DXMatrix4& matrix);
		float& operator()(int row, int col);
		const float& operator()(int row, int col) const;


		//DXMatrix4 mul(DXMatrix4& m);
		//DXMatrix4 mul(DXMatrix4&& m);

		//DXVector4 mul(DXVector4& v);
		//DXVector4 mul(DXVector4&& v);

		//DXMatrix4 mul(float scale);

		//DXMatrix4 add(DXMatrix4& m);
		//DXMatrix4 add(DXMatrix4&& m);

		//DXMatrix4 add(int increment);
		//DXMatrix4 add(float increment);

		//DXMatrix4 operator*(DXMatrix4& matrix);
		//DXMatrix4 operator*(DXMatrix4&& m);

		//DXMatrix4& operator*=(DXMatrix4& m);
		//DXMatrix4& operator*=(DXMatrix4&& m);

		//DXVector4 operator*(DXVector4& DXVector4);
		//DXVector4 operator*(DXVector4&& v);

		//DXVector4& operator*=(DXVector4& v);
		//DXVector4& operator*=(DXVector4&& v);

		//DXMatrix4 operator*(float scale);
		//DXMatrix4& operator*=(float scale);

		DXMatrix4 operator+(DXMatrix4& matrix);
		DXMatrix4 operator+(DXMatrix4&& m);

		//DXMatrix4& operator+=(DXMatrix4& m);
		//DXMatrix4& operator+=(DXMatrix4&& m);

		//DXMatrix4 operator-(DXMatrix4& matrix);
		//DXMatrix4 operator-(DXMatrix4&& m);

		//DXMatrix4& operator-=(DXMatrix4& m);
		//DXMatrix4& operator-=(DXMatrix4&& m);


		//DXMatrix4& operator+=(int increment);



		//DXMatrix4& invert();
		//DXMatrix4& transpose();

		//DXMatrix4 getInverse();
		//DXMatrix4 getTranspose();

		//DXVector4 determinant();


		DXMatrix4 identity() { return DXMatrix4(); }

		XMMATRIX getXMMatrix() { return XMLoadFloat4x4(this); }

	};

	inline DXMatrix4 operator*(float scale, DXMatrix4& m) {
		XMMATRIX xmmatrix = m.getXMMatrix();
		xmmatrix *= scale;
		return Matrix4(xmmatrix);

	}

	inline void operator*=(DXVector4& vector, DXMatrix4& matrix)
	{
		XMVECTOR xmvector = vector.getXMVector();
		XMMATRIX xmmatrix = matrix.getXMMatrix();

		xmvector = XMVector4Transform(xmvector, xmmatrix);
		vector = xmvector;
	}

	inline DXVector4 operator*(DXVector4 vector , DXMatrix4& matrix)
	{
		XMVECTOR xmvector = vector.getXMVector();
		XMMATRIX xmmatrix = matrix.getXMMatrix();

		xmvector = XMVector4Transform(xmvector, xmmatrix);
		return DXVector4(xmvector);
	}

	inline void outterProduct(DXMatrix4& matrix, const DXVector4& v1, const DXVector4& v2) {
		DXMatrix4 matrix;
		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {
				matrix(i, j) = v1[i] * v2[j];


			}

		}


	}

}
