#pragma once
#include "OdinMath.h"
#include <intrin.h>
#include <xmmintrin.h>

namespace OdinMath {

	

	template<int SIZE, typename real>
	class Vector;



	//todo build iterator for class

	template<int SIZE, typename real>
	class Vector {
	protected:
		real data[SIZE];

	public:
		Vector() { };
		Vector(const Vector& vector) { *this = vector; }
		Vector(std::initializer_list<real>&& list);

		bool operator==(Vector& vector);
		Vector& operator=(const Vector& vector);
		
		const real& operator[](int idx) const;
		real& operator[](int idx);
		real* getData() { return data; }



	};

	template<int SIZE, typename real>
	inline Vector<SIZE, real>::Vector(std::initializer_list<real>&& list)
	{
		assert(list.size() == SIZE);
		int i = 0;

		for (auto it = list.begin(); it != list.end(); it++) {
			data[i++] = *it;
		}
	}

	template<int SIZE, typename real>
	inline bool Vector<SIZE, real>::operator==(Vector& vector)
	{
		for (int i = 0; i < SIZE; i++) {
			if (vector[i] != (*this)[i])
				return false;

		}

		return true;
	}

	template<int SIZE, typename real>
	inline Vector<SIZE, real>& Vector<SIZE, real>::operator=(const Vector<SIZE, real>& vector)
	{
		if (this != &vector) {

			for (int i = 0; i < SIZE; i++) {
				(*this)[i] = vector[i];

			}
		}

		return *this;
	}

	template<int SIZE, typename real>
	inline const real& Vector<SIZE, real>::operator[](int idx) const
	{
		if (idx >= SIZE)
			throw std::invalid_argument("Invalid argument");
		return data[idx];
	}

	template<int SIZE, typename real>
	inline real& Vector<SIZE, real>::operator[](int idx)
	{
		if (idx >= SIZE)
			throw std::invalid_argument("Invalid argument");
		return data[idx];
	}


	typedef Vector<4, float> Vector4f;
	typedef Vector<2, float> Vector2f;
	typedef Vector<1, float> Vector1f;
	typedef Vector<3, float> Vector3f;

	typedef Vector<4, double> Vector4d;
	typedef Vector<2, double> Vector2d;
	typedef Vector<1, double> Vector1d;
	typedef Vector<3, double> Vector3d;



}