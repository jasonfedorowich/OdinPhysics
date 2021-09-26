#pragma once
#include "OdinMath.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

namespace OdinMath {

	using namespace DirectX;
	using namespace DirectX::PackedVector;

	struct DXVector3 : XMFLOAT3 {


		DXVector3() { x = 0.f; y = 0.f; z = 0.f; }
		DXVector3(float x, float y, float z) {
			this->x = x; this->y = y; this->z = z;
		}
		DXVector3(XMVECTOR& vector) { XMStoreFloat3(this, vector); }
		DXVector3(const DXVector3& v) { *this = v; }

		~DXVector3() {}

		DXVector3& operator=(const DXVector3& v);
		float operator*(DXVector3& v) { return dot(v); }
		DXVector3 operator+(DXVector3& v);
		void operator+=(DXVector3& v);
		void operator-=(DXVector3& v);
		DXVector3 operator-(DXVector3& v);
		const float& operator[](int idx) const;
		float& operator[](int idx);

		float dot(DXVector3& v);
		DXVector3 cross(DXVector3& v);
		void normalize();
		DXVector3 normal();
		float length();



		void store(XMVECTOR& vector) { XMStoreFloat3(this, vector); }
		void store(XMVECTOR&& vector) { XMStoreFloat3(this, vector); }

		XMVECTOR getXMVector() { return XMLoadFloat3(this); }

	};


}
