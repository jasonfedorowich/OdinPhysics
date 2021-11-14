#include "OdinMath.h"
#include <stdexcept>

namespace OdinMath {
	DXVector4::DXVector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float DXVector4::distance(const DXVector4& v)
	{
		XMVECTOR xmvector1 = XMLoadFloat4(this);
		XMVECTOR xmvector2 = XMLoadFloat4(&v);
		XMVECTOR xmvector3 = xmvector1 - xmvector2;
		XMVECTOR length = XMVector3Length(xmvector3);

		XMFLOAT3 dest;
		XMStoreFloat3(&dest, length);

		return dest.x;
	}

	float DXVector4::length3()
	{
		XMVECTOR xmvector = XMLoadFloat4(this);
		xmvector = XMVector3Length(xmvector);
		XMFLOAT4 temp;
		XMStoreFloat4(&temp, xmvector);
		return temp.x;
	}

	float DXVector4::length()
	{
		XMVECTOR xmvector = XMLoadFloat4(this);
		xmvector = XMVector4Length(xmvector);
		XMFLOAT4 temp;
		XMStoreFloat4(&temp, xmvector);
		return temp.x;
	}

	float DXVector4::dot(const DXVector4& v)
	{
		XMVECTOR xmvectorA = XMLoadFloat4(this);
		XMVECTOR xmvectorB = XMLoadFloat4(&v);
		xmvectorA = XMVector4Dot(xmvectorA, xmvectorB);
		XMFLOAT4 temp;
		XMStoreFloat4(&temp, xmvectorA);
		return temp.x;


	}

	DXVector4 DXVector4::cross(const DXVector4& v)
	{
		XMVECTOR xmvectorA = XMLoadFloat4(this);
		XMVECTOR xmvectorB = XMLoadFloat4(&v);
		xmvectorA = XMVector3Cross(xmvectorA, xmvectorB);
		return DXVector4(xmvectorA);
	}

	DXVector4 DXVector4::normal()
	{
		XMVECTOR xmvector = XMLoadFloat4(this);
		xmvector = XMVector3Normalize(xmvector);

		XMFLOAT4 dest;
		XMStoreFloat4(&dest, xmvector);
		return DXVector4(dest);
	}

	void DXVector4::normalize3()
	{
		XMVECTOR xmvector = XMLoadFloat4(this);
		xmvector = XMVector3Normalize(xmvector);
		XMStoreFloat4(this, xmvector);

	}

	void DXVector4::normalize()
	{
		XMVECTOR xmvector = XMLoadFloat4(this);
		xmvector = XMVector4Normalize(xmvector);
		XMStoreFloat4(this, xmvector);
	}

	DXVector4 DXVector4::getAngleBetweenVectors(DXVector4& v)
	{
		XMVECTOR xmvector1 = XMLoadFloat4(this);
		XMVECTOR xmvector2 = XMLoadFloat4(&v);
		XMVECTOR result = XMVector3AngleBetweenVectors(xmvector1, xmvector2);
		return DXVector4(result);
	}

	float DXVector4::getAngleToTarget(DXVector4& v)
	{
		XMVECTOR xmvector1 = XMLoadFloat4(this);
		XMVECTOR xmvector2 = XMLoadFloat4(&v);

		XMVECTOR result = xmvector1 - xmvector2;
		DXVector4 vector3(result);
		return atan2(vector3.getY(), vector3.getX());
	}

	DXVector4 DXVector4::operator+(const DXVector4& v)
	{
		XMVECTOR xmvectorA = XMLoadFloat4(this);
		XMVECTOR xmvectorB = XMLoadFloat4(&v);

		xmvectorA += xmvectorB;
		return DXVector4(xmvectorA);
	}

	DXVector4 DXVector4::operator-(const DXVector4& v)
	{
		XMVECTOR xmvectorA = XMLoadFloat4(this);
		XMVECTOR xmvectorB = XMLoadFloat4(&v);

		xmvectorA -= xmvectorB;
		return DXVector4(xmvectorA);
	}

	DXVector4 DXVector4::operator/(const DXVector4& v)
	{
		XMVECTOR xmvectorA = XMLoadFloat4(this);
		XMVECTOR xmvectorB = XMLoadFloat4(&v);

		xmvectorA /= xmvectorB;
		return DXVector4(xmvectorA);
	}

	bool DXVector4::operator==(const DXVector4& v) const
	{
		
		return x == v.x && y == v.y && z == v.z && w == v.w;

	}

	DXVector4& DXVector4::operator=(const DXVector4& v)
	{
		if (this != &v) {
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		return *this;
	}

	float& DXVector4::operator[](int index)
	{
		switch (index) {

		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw std::invalid_argument("Index out of range");
		}
	}

	const float& DXVector4::operator[](int index) const
	{
		switch (index) {

		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw std::invalid_argument("Index out of range");
		}
	}

	void DXVector4::operator/=(float c)
	{
		x /= c;
		y /= c;
		z /= c;
		w /= c;
	}

	void DXVector4::operator*=(float c)
	{
		x *= c;
		y *= c;
		z *= c;
		w *= c;
	}

	DXVector4 DXVector4::operator*(float val)
	{
		return DXVector4(x * val, y * val, z * val, w * val);
	}


}
