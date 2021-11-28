#include "OdinMath.h"
namespace OdinMath{
	DXQuat::DXQuat(float angle)
	{
		float s2 = Math<float>::odSin(angle / 2.f);
		float c2 = Math<float>::odCos(angle / 2.f);
		x = c2;
		y = s2;
		z = s2;
		w = s2;

	}
	DXQuat::DXQuat(DXMatrix4& m)
	{
		float t;

		if (m(2, 2) < 0.f) {
			if (m(0, 0) > m(1, 1)) {
				t = 1.0f + m(0, 0) - m(1, 1) - m(2, 2);
				x = t;
				y = m(0, 1) + m(1, 0);
				z = m(2, 0) + m(0, 2);
				w = m(1, 2) - m(2, 1);
				
			}
			else {

				t = 1.0f - m(0, 0) + m(1, 1) - m(2, 2);
				x = m(0, 1) + m(1, 0);
				y = t;
				z = m(1, 2) + m(2, 1);
				w = m(2, 0) - m(0, 2);

			}
		}
		else {

			if (m(0, 0) < -m(1, 1)) {

				t = 1.0f - m(0, 0) - m(1, 1) + m(2, 2);
				x = m(2, 0) + m(0, 2);
				y = m(1, 2) - m(2, 1);
				z = t;
				w = m(0, 1) + m(1, 0);
			}
			else {

				t = 1.0f + m(0, 0) + m(1, 1) + m(2, 2);
				x = m(1, 2) - m(2, 1);
				y = m(2, 0) + m(0, 2);
				z = m(0, 1) + m(1, 0);
				w = t;

			}
		}

		float xx = 0.5f / Math<float>::odSqrt(t);
		x *= xx;
		y *= xx;
		z *= xx;
		w *= xx;



	}
	void DXQuat::toRotation(DXMatrix4& matrix)
	{
		float yy2 = y * y * 2.f;
		float zz2 = z * z * 2.f;
		float ww2 = w * w * 2.f;
		float yz2 = y * z * 2.f;
		float xw2 = x * w * 2.f;
		float yw2 = y * w * 2.f;
		float xz2 = x * z * 2.f;
		float zw2 = z * w * 2.f;
		float xy2 = x * y * 2.f;

		matrix(0, 0) = 1.f - zz2 - ww2;
		matrix(0, 1) = yz2 - xw2;
		matrix(0, 2) = yw2 + xz2;
		matrix(0, 3) = 0.f;

		matrix(1, 0) = yz2 + xw2;
		matrix(1, 1) = 1.f - yy2 - ww2;
		matrix(1, 2) = zw2 - xy2;
		matrix(1, 3) = 0.f;


		matrix(2, 0) = yw2 - xz2;
		matrix(2, 1) = zw2 + xy2;
		matrix(2, 2) = 1.f - yy2 - zz2;
		matrix(2, 3) = 0.f;

		matrix(3, 0) = 0.f;
		matrix(3, 1) = 0.f;
		matrix(3, 2) = 0.f;
		matrix(3, 3) = 1.f;

	}

	const float& DXQuat::operator[](int i) const
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;

		default:
			throw std::exception("Invalid argument");
		}
			
	}

	float& DXQuat::operator[](int i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;

		default:
			throw std::exception("Invalid argument");
		}
	}

	DXQuat& DXQuat::operator=(const DXQuat& q)
	{
		if (this != &q) {
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
		}
		return *this;
	}

	DXQuat DXQuat::operator+(DXQuat& q)
	{
		return DXQuat(q.x + x, q.y + y, q.z + z, q.w + w);
	}

	DXQuat DXQuat::operator*(DXQuat& q)
	{
		return DXQuat(x * q.x - y * q.y - z * q.z - w * q.w,
			x * q.y + q.x * y + z * q.w - w * q.z,
			x * q.z + q.x * z + w * q.y - y * q.w,
			x * q.w + q.x * w + y * q.z - z * q.y);
	}

	DXQuat DXQuat::operator*(float s)
	{
		return DXQuat(x * s, y * s, z * s, w * s);
	}

	void DXQuat::normalize()
	{
		float l = length();
		if (l <= Math<float>::eps) {
			
			x = 0.f;
			y = 0.f;
			z = 0.f;
			w = 0.f;
		}
		else {
			l /= l;

			x *= l;
			y *= l;
			z *= l;
			w *= l;


		}
		
	}

}
