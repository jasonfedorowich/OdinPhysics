#pragma once
#include "OdinMath.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>


namespace OdinMath {
	using namespace DirectX;
	using namespace DirectX::PackedVector;

	/*uses format: x + yi + zj + wk*/
	struct DXQuat : XMFLOAT4
	{
		DXQuat(float angle);
		DXQuat() { x = 0.f; y = 0.f; z = 0.f; w = 1.f; }
		DXQuat(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
		DXQuat(DXMatrix4& m);
		~DXQuat() {}

		DXQuat(const DXQuat& q) { *this = q; }

		void toRotation(DXMatrix4& matrix);
		void toRotation(DXMatrix3& matrix);

		const float& operator[](int i) const;
		float& operator[](int i);
		DXQuat& operator=(const DXQuat& q);
		DXQuat operator+(DXQuat& q);
		DXQuat operator*(DXQuat& q);
		DXQuat operator*(float s);
		
		void operator*=(DXQuat& q);
		void operator+=(DXQuat& q);
		void operator*=(float s);

		DXQuat getConjugate();
		void conjugate();

		float length() { return Math<float>::odSqrt(x * x + y * y + z * z + w * w); }

		void normalize();
		bool isNormal() { return (x* x + y * y + z * z + w * w - 1.f) <= Math<float>::eps; }
		DXQuat getNormal();
		float dot();




	};


}
