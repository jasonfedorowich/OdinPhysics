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

	DXVector3 DXMatrix3::operator*(DXVector3& v)
	{
		DXMatrix3 trans = this->getTranspose();
		return v * trans;
	}

	DXVector3 DXMatrix3::operator*(DXVector3&& v)
	{
		DXMatrix3 trans = this->getTranspose();
		return v * trans;
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

	void DXMatrix3::operator%=(const DXMatrix3& m)
	{
		XMMATRIX matrix = XMMatrixMultiply(m.getXMMatrix(), this->getXMMatrix());
		store(matrix);
	}

	void DXMatrix3::operator-=(const DXMatrix3& m)
	{
		XMMATRIX mat1 = this->getXMMatrix();
		XMMATRIX mat2 = m.getXMMatrix();
		mat1 -= mat2;
		store(mat1);

	}

	void DXMatrix3::operator-=(const DXMatrix3&& m)
	{
		XMMATRIX mat1 = this->getXMMatrix();
		XMMATRIX mat2 = m.getXMMatrix();
		mat1 -= mat2;
		store(mat1);
	}

	void DXMatrix3::operator*=(float scale)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				(*this)(i, j) *= scale;
			}
		}
	}

	DXVector3 DXMatrix3::getRow(int r)
	{
		return DXVector3((*this)(r, 0), (*this)(r, 1), (*this)(r, 2));
	}

	DXVector3 DXMatrix3::getCol(int c)
	{
		return DXVector3((*this)(0, c), (*this)(1, c), (*this)(2, c));
	}

	void DXMatrix3::setRow(int r, const DXVector3& v)
	{
		(*this)(r, 0) = v[0];
		(*this)(r, 1) = v[1];
		(*this)(r, 2) = v[2];
	}

	void DXMatrix3::setRow(int r, const DXVector3&& v)
	{
		(*this)(r, 0) = v[0];
		(*this)(r, 1) = v[1];
		(*this)(r, 2) = v[2];
	}

	void DXMatrix3::setCol(int c, const DXVector3& v)
	{
		(*this)(0, c) = v[0];
		(*this)(1, c) = v[1];
		(*this)(2, c) = v[2];
	}

	void DXMatrix3::setCol(int c, const DXVector3&& v)
	{
		(*this)(0, c) = v[0];
		(*this)(1, c) = v[1];
		(*this)(2, c) = v[2];
	}

	void DXMatrix3::swapRows(int i, int j)
	{
		for (int k = 0; k < 3; k++) {
			std::swap((*this)(i, k), (*this)(j, k));
		}
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

	float DXMatrix3::determinant()
	{
		XMMATRIX xmmatrix = this->getXMMatrix();
		XMVECTOR xmvector = XMMatrixDeterminant(xmmatrix);
		DXVector3 dxvec(xmvector);
		return dxvec[0];
	}

	DXMatrix3 DXMatrix3::getTranspose()
	{
		Matrix3 copy(*this);
		copy.transpose();
		return copy;
	}

	void DXMatrix3::transpose()
	{
		XMMATRIX matrix = XMMatrixTranspose(this->getXMMatrix());
		store(matrix);
	}

}