#pragma once
#include "OdinMath.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

namespace OdinMath {


	using namespace DirectX;
	using namespace DirectX::PackedVector;

	/*Wrapper class for DirectX XMFLOAT4*/
	class DXVector4 : XMFLOAT4 {


	public:
		DXVector4() : DXVector4(0.0f, 0.0f, 0.0f) {}
		DXVector4(const DXVector4& v) { *this = v; }
		DXVector4(float x, float y, float z, float w = 0.0f);
		DXVector4(int x, int y, int z, int w = 0) : DXVector4((float)x, (float)y, (float)z, (float) w) {}
		DXVector4(XMVECTOR& xmvector) { XMStoreFloat4(this, xmvector); }
		DXVector4(XMFLOAT4& xmfloat4) { x = xmfloat4.x; y = xmfloat4.y; z = xmfloat4.z; w = xmfloat4.w; }
		virtual ~DXVector4() {};
		void store(XMVECTOR& vector) { XMStoreFloat4(this, vector); }

		void set(float x, float y, float z, float w = 0.0f) { this->x = x; this->y = y; this->z = z; this->w = w; }
		void set(const DXVector4& v) { *this = v; }
		float getX() { return x; }
		void setX(float x) { (*this)[0] = x; }
		float getY() { return y; }
		void setY(float y) { (*this)[1] = y; }
		float getZ() { return z; }
		void setZ(float z) { (*this)[2] = z; }
		float getW() { return w; }
		void setW(float w) { (*this)[3] = w; }
		void move(float mx, float my, float mz, float mw = 0.0f) { x += mx; y += my; z += mz; w += mw; }
		
		float distance(const DXVector4& v);
		float length();
		float length4();

		float dot(const DXVector4& v);
		DXVector4 cross(const DXVector4& v);

		DXVector4 normal();
		void normalize();
		void normalize4();

		DXVector4 getAngleBetweenVectors(DXVector4& v);
		float getAngleToTarget(DXVector4& v);


		DXVector4 operator+(const DXVector4& v1);
		DXVector4 operator-(const DXVector4& v1);
		void operator+= (const DXVector4& v) { *this = *this + v; }
		void operator-=(const DXVector4& v) { *this = *this - v; }
		float operator*(const DXVector4& v) { return dot(v); }
		void operator/=(const DXVector4& v) { *this = *this / v; }
		DXVector4 operator/(const DXVector4& v);
		bool operator== (const DXVector4& v) const;
		bool operator!=(const DXVector4& v) const { return !(*this == v); }
		DXVector4& operator=(const DXVector4& v);
		float& operator[](int index);
		const float& operator[](int index) const;
		DXVector4& operator=(XMVECTOR& xmvector) { store(xmvector); return *this; }
		void operator/=(float c);
		void operator*=(float val);
		DXVector4 operator*(float val);
		friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);

		

		XMVECTOR getXMVector() { return XMLoadFloat4(this); }
		

		bool empty() { return x == 0 && y == 0 && z == 0; }

	};


}