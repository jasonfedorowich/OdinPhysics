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

	DXMatrix4 DXMatrix4::operator*(DXMatrix4& matrix)
	{
		return XMMatrixMultiply(this->getXMMatrix(), matrix.getXMMatrix());
	}

	DXMatrix4 DXMatrix4::operator*(DXMatrix4&& matrix)
	{
		return XMMatrixMultiply(this->getXMMatrix(), matrix.getXMMatrix());
	}

	void DXMatrix4::operator*=(DXMatrix4& m)
	{
		XMMATRIX xmmatrix = XMMatrixMultiply(this->getXMMatrix(), m.getXMMatrix());
		XMStoreFloat4x4(this, xmmatrix);

	}

	void DXMatrix4::operator*=(DXMatrix4&& m)
	{
		XMMATRIX xmmatrix = XMMatrixMultiply(this->getXMMatrix(), m.getXMMatrix());
		XMStoreFloat4x4(this, xmmatrix);

	}

	void DXMatrix4::operator%=(DXMatrix4& m)
	{
		XMMATRIX xmmatrix = XMMatrixMultiply(m.getXMMatrix(), this->getXMMatrix());
		XMStoreFloat4x4(this, xmmatrix);
	}

	void DXMatrix4::operator%=(DXMatrix4&& M)
	{
		XMMATRIX xmmatrix = XMMatrixMultiply(M.getXMMatrix(), this->getXMMatrix());
		XMStoreFloat4x4(this, xmmatrix);
	}

	DXVector4 DXMatrix4::operator*(DXVector4& v)
	{
		DXMatrix4 trans = getTranspose();
		return v * trans;
	}

	DXVector4 DXMatrix4::operator*(DXVector4&& v)
	{
		return DXVector4();
	}

	DXMatrix4 DXMatrix4::operator+(DXMatrix4& matrix)
	{
		XMMATRIX xmmatrix1 = this->getXMMatrix();
		XMMATRIX xmmatrix2 = matrix.getXMMatrix();
		return xmmatrix1 + xmmatrix2;
	}

	DXMatrix4 DXMatrix4::operator+(DXMatrix4&& matrix)
	{
		XMMATRIX xmmatrix1 = this->getXMMatrix();
		XMMATRIX xmmatrix2 = matrix.getXMMatrix();
		return xmmatrix1 + xmmatrix2;
	}

	void DXMatrix4::transpose()
	{
		XMMATRIX xm = XMMatrixTranspose(this->getXMMatrix());
		store(xm);

	}

	DXMatrix4 DXMatrix4::getTranspose()
	{
		return XMMatrixTranspose(this->getXMMatrix());
	}

	DXVector4 DXMatrix4::getCol(int c)
	{
		return DXVector4((*this)(0, c), (*this)(1, c), (*this)(2, c), (*this)(3, c));
	}

	DXVector4 DXMatrix4::getRow(int r)
	{
		return DXVector4((*this)(r, 0), (*this)(r, 1), (*this)(r, 2), (*this)(r, 3));
	}

	void DXMatrix4::setCol(int c, const DXVector4& v)
	{
		(*this)(0, c) = v[0];
		(*this)(1, c) = v[1];
		(*this)(2, c) = v[2];
		(*this)(3, c) = v[3];
	}

	void DXMatrix4::setCol(int c, DXVector4&& v)
	{
		(*this)(0, c) = v[0];
		(*this)(1, c) = v[1];
		(*this)(2, c) = v[2];
		(*this)(3, c) = v[3];
	}

	void DXMatrix4::setRow(int r, const DXVector4& v)
	{
		(*this)(r, 0) = v[0];
		(*this)(r, 1) = v[1];
		(*this)(r, 2) = v[2];
		(*this)(r, 3) = v[3];
	}

	void DXMatrix4::setRow(int r, DXVector4&& v)
	{
		(*this)(r, 0) = v[0];
		(*this)(r, 1) = v[1];
		(*this)(r, 2) = v[2];
		(*this)(r, 3) = v[3];
	}

	void DXMatrix4::swapRows(int i, int j)
	{
		for (int k = 0; k < 4; k++) {
			
			std::swap((*this)(i, k), (*this)(j, k));

		}
	}


}


