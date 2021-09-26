#include "OdinMath.h"

namespace OdinMath {



	DXMatrix3::DXMatrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
	{
		this->_11 = _00;
		this->_12 = _01;
		this->_13 = _02;

		this->_21 = _10;
		this->_22 = _11;
		this->_23 = _12;

		this->_31 = _20;
		this->_32 = _21;
		this->_33 = _22;

	}

	DXMatrix3::DXMatrix3(XMFLOAT3X3& m)
	{
		XMMATRIX xmmatrix = XMLoadFloat3x3(&m);
		store(xmmatrix);
	}

	const float& DXMatrix3::operator()(int r, int c) const
	{
		if (r >= 3 || r < 0 || c >= 3 || c < 0)
			throw std::exception("Bad argument");
		return m[r][c];
	}

	float& DXMatrix3::operator()(int r, int c)
	{
		if (r >= 3 || r < 0 || c >= 3 || c < 0)
			throw std::exception("Bad argument");
		return m[r][c];
	}

	DXMatrix3& DXMatrix3::operator=(const DXMatrix3& m)
	{
		if (this != &m) {
			XMMATRIX xmmatrix = XMLoadFloat3x3(&m);
			XMStoreFloat3x3(this, xmmatrix);
		}
		return *this;
	}

	DXMatrix3 DXMatrix3::operator+(const DXMatrix3& m)
	{
		XMMATRIX mat1 = this->getXMMatrix();
		XMMATRIX mat2 = m.getXMMatrix();
		return mat1 + mat2;
	}

	DXMatrix3 DXMatrix3::operator*(const DXMatrix3& m)
	{
		XMMATRIX matrix = XMMatrixMultiply(this->getXMMatrix(), m.getXMMatrix());
		return matrix;

	}

	void DXMatrix3::operator*=(const DXMatrix3& m)
	{
		XMMATRIX matrix = XMMatrixMultiply(this->getXMMatrix(), m.getXMMatrix());
		store(matrix);
	}

	void DXMatrix3::operator+=(const DXMatrix3& m)
	{
		XMMATRIX mat1 = this->getXMMatrix();
		XMMATRIX mat2 = m.getXMMatrix();
		store(mat1 + mat2);
	}

	DXMatrix3 DXMatrix3::getInverse()
	{
		XMVECTOR v;
		XMMATRIX matrix = XMMatrixInverse(&v, this->getXMMatrix());
		return matrix;
	}

	void DXMatrix3::invert()
	{
		XMVECTOR v;
		XMMATRIX matrix = XMMatrixInverse(&v, this->getXMMatrix());
		store(matrix);
	}

	DXMatrix3 DXMatrix3::getTranspose()
	{
		return DXMatrix3();
	}

	void DXMatrix3::transpose()
	{
		XMMATRIX matrix = XMMatrixTranspose(this->getXMMatrix());
		store(matrix);
	}

}