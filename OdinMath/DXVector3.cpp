#include "OdinMath.h"
namespace OdinMath {


	DXVector3& DXVector3::operator=(const DXVector3& v)
	{
		if (this != &v) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}
		return *this;
	}

	DXVector3 DXVector3::operator+(DXVector3& v)
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	void DXVector3::operator+=(DXVector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void DXVector3::operator-=(DXVector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	DXVector3 DXVector3::operator-(DXVector3& v)
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	const float& DXVector3::operator[](int idx) const
	{
		switch (idx) {

		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::exception("Index out of bounds");
		}
	}

	float& DXVector3::operator[](int idx)
	{
		switch (idx) {

		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::exception("Index out of bounds");
		}
	}

	float DXVector3::dot(DXVector3& v)
	{
		return v.x * x + v.y + y + z * v.z;
		
	}

	DXVector3 DXVector3::cross(DXVector3& v)
	{
		XMVECTOR xmvector = XMVector3Cross(this->getXMVector(), v.getXMVector());
		return xmvector;
	}

	void DXVector3::normalize()
	{
		XMVECTOR xmvector = XMVector3Normalize(this->getXMVector());
		store(xmvector);
	}

	DXVector3 DXVector3::normal()
	{
		XMVECTOR xmvector = XMVector3Normalize(this->getXMVector());
		return xmvector;
	}

	float DXVector3::length()
	{
		XMVECTOR xmvector = XMVector3Length(this->getXMVector());
		XMFLOAT3 xmfloat3;
		XMStoreFloat3(&xmfloat3, xmvector);
		return xmfloat3.x;
	}
	
}