#include "OdinMath.h"
#include <stdexcept>

namespace OdinMath {



	DXMatrix4::DXMatrix4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33)
	{
		XMMATRIX matrix(_00, _01, _02, _03,
			_10, _11, _12, _13,
			_20, _21, _22, _23,
			_30, _31, _32, _33);
		XMStoreFloat4x4(this, matrix);
	}

	DXMatrix4::DXMatrix4(XMFLOAT4X4& xmfloat4x4)
	{
		XMMATRIX matrix = XMLoadFloat4x4(&xmfloat4x4);
		XMStoreFloat4x4(this, matrix);
	}

	DXMatrix4& DXMatrix4::operator=(const DXMatrix4& matrix)
	{
		if (this != &matrix) {
			XMMATRIX xmmatrix = XMLoadFloat4x4(&matrix);
			XMStoreFloat4x4(this, xmmatrix);
		}
		return *this;
	}

	float& DXMatrix4::operator()(int row, int col)
	{
		if (row >= 4 || col >= 4 || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return m[row][col];
	}

	const float& DXMatrix4::operator()(int row, int col) const
	{
		if (row >= 4 || col >= 4 || row < 0 || col < 0)
			throw std::invalid_argument("Invalid argument");
		return m[row][col];
	}


}


