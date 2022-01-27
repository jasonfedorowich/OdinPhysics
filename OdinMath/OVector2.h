#pragma once
#include "OdinMath.h"

namespace OdinMath {

	template<typename real>
	struct OVector2 : public Vector<2, real> {
		OVector2(real x, real y) { this->data[0] = x; this->data[1] = y; }
		OVector2() { this->data[0] = (real)0.0; this->data[1] = (real)0.0; }
		OVector2(int x, int y) : OVector2<real>((real)x, (real)y) {}
		OVector2(const OVector2<real>& v) { *this = v; }
		virtual ~OVector2() {}

		void set(real x, real y) { this->data[0] = x; this->data[1] = y; }
		void set(const OVector2& v) { *this = v; }
		real getX() { (*this)[0]; }
		void setX(real x) { (*this)[0] = x; }
		real getY() { (*this)[1]; }
		void setY(real y) { (*this)[1] = y; }
		void move(real mx, real my) { (*this) += OVector2<real>(mx, my); }


		OVector2<real> operator+(const OVector2<real>& v1);
		OVector2<real> operator-(const OVector2<real>& v1);
		void operator+= (const OVector2<real>& v);
		void operator+= (OVector2<real>&& v);
		void operator-=(const OVector2<real>& v);
		real operator*(const OVector2<real>& v) { return dot(v); }
		void operator/=(const OVector2<real>& v);
		OVector2<real> operator/(const OVector2<real>& v);
		bool operator== (const OVector2<real>& v) const;
		bool operator!=(const OVector2<real>& v) const { return !(*this == v); }
		OVector2<real>& operator=(const OVector2<real>& v);
		OVector2<real> operator>(OVector2<real>& v);
		OVector2<real> operator>=(OVector2<real>& v);
		void operator/=(real c);
		void operator*=(real val);
		OVector2<real> operator*(real val);
		/*friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);*/

		real distance(const OVector2<real>& v);
		real length();

		real dot(const OVector2<real>& v);
		OVector3<real> cross(const OVector2<real>& v);

		OVector2<real> normal();
		void normalize();

		real getAngleBetweenVectors(OVector2<real>& v);
		real getAngleToTarget(OVector2<real>& v);

		//todo
		static OVector2<real> zeros() { return OVector2<real>((real)0.f, (real)0.f); }
		static OVector2<real> ones() { return OVector2<real>((real)1.f, (real)1.f); }
		bool empty() {
			return (*this) == OVector2<real>::zeros();
		}



		

	};




	template<typename real>
	inline OVector2<real> OVector2<real>::operator+(const OVector2<real>& v1)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		add4<real, 2>(this->data, v1.data, res.data);
#else
		res[0] = this->data[0] + v1[0];
		res[1] = this->data[1] + v1[1];
#endif
		return res;
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::operator-(const OVector2<real>& v1)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		sub4<real, 2>(this->data, v1.data, res.data);
#else
		res[0] = this->data[0] - v1[0];
		res[1] = this->data[1] - v1[1];
#endif
		return res;
	}

	template<typename real>
	inline void OVector2<real>::operator+=(const OVector2<real>& v1)
	{
#if defined(INTRINSICS)
		add4<real, 2>(this->data, v1.data, this->data);
#else
		this->data[0] = this->data[0] + v1[0];
		this->data[1] = this->data[1] + v1[1];
#endif
	}

	template<typename real>
	inline void OVector2<real>::operator+=(OVector2<real>&& v1)
	{
#if defined(INTRINSICS)
		add4<real, 2>(this->data, v1.data, this->data);
#else
		this->data[0] = this->data[0] + v1[0];
		this->data[1] = this->data[1] + v1[1];
#endif
	}

	template<typename real>
	inline void OVector2<real>::operator-=(const OVector2<real>& v1)
	{
#if defined(INTRINSICS)
		sub4<real, 2>(this->data, v1.data, this->data);
#else
		this->data[0] = this->data[0] - v1[0];
		this->data[1] = this->data[1] - v1[1];
#endif
	}

	template<typename real>
	inline void OVector2<real>::operator/=(const OVector2<real>& v1)
	{
#if defined(INTRINSICS)
		div4<real, 2>(this->data, v1.data, this->data);
#else
		this->data[0] = this->data[0] / v1[0];
		this->data[1] = this->data[1] / v1[1];
#endif
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::operator/(const OVector2<real>& v1)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		div4<real, 2>(this->data, v1.data, res.data);
#else
		this->data[0] = this->data[0] / v1[0];
		this->data[1] = this->data[1] / v1[1];
#endif
		return res;
	}

	template<typename real>
	inline bool OVector2<real>::operator==(const OVector2<real>& v1) const
	{
#if defined(INTRINSICS)
		return equals4<real, 2>(this->data, v1.data);
#else
		return this->data[0] == v[0] && this->data[1] == v[1];
#endif
	}

	template<typename real>
	inline OVector2<real>& OVector2<real>::operator=(const OVector2<real>& v)
	{
		if (this != &v) {
#if defined(INTRINSICS)
			store2<real>(this->data, v.data);
#else
			this->data[0] = v[0];
			this->data[1] = v[1];
#endif
		
		}
		return *this;
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::operator>(OVector2<real>& v)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		cmpgt<real, 2>(this->data, v.data, res.data);
#else
		res[0] = (*this) > v[0];
		res[1] = (*this) > v[1];
#endif
		return res;
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::operator>=(OVector2<real>& v)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		cmpgte<real, 2>(this->data, v.data, res.data);
#else
		res[0] = (*this) >= v[0];
		res[1] = (*this) >= v[1];
#endif
		return res;
	}

	template<typename real>
	inline void OVector2<real>::operator/=(real c)
	{
#if defined(INTRINSICS)
		scalarDiv4<real, 2>(this->data, c, this->data);
#else
		(*this)[0] /= c;
		(*this)[1] /= c;
#endif
	}

	template<typename real>
	inline void OVector2<real>::operator*=(real c)
	{
#if defined(INTRINSICS)
		scalarMul4<real, 2>(this->data, c, this->data);
#else
		(*this)[0] *= c;
		(*this)[1] *= c;
#endif
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::operator*(real val)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		scalarMul4<real, 2>(this->data, val, res.data);
#else
		res[0] = this->data[0] * val;
		res[1] = this->data[1] * val;
#endif
		return res;
	}

	template<typename real>
	inline real OVector2<real>::distance(const OVector2<real>& v)
	{
		OVector2<real> res;
#if defined(INTRINSICS)
		sub4<real, 2>(v.data, this->data, res.data);
#else
		res[0] = v.data[0] - this->data[0];
		res[1] = v.data[1] - this->data[1];
#endif
		return res.length();
	}

	template<typename real>
	inline real OVector2<real>::length()
	{
		return Math<real>::odSqrt(this->dot(*this));
	}

	template<typename real>
	inline real OVector2<real>::dot(const OVector2<real>& v)
	{
#if defined(INTRINSICS)
		return dot4<real, 2>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1];
#endif
	}

	template<typename real>
	inline OVector3<real> OVector2<real>::cross(const OVector2<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> r;
		cross4<real, 2>(this->data, v.data, r.data);
		return r;
#else
		return OVector3<real>{(*this)[1] * v[2] - (*this)[2] * v[1], (*this)[3] * v[0] - (*this)[0] * v[3], (*this)[0] * v[1] - (*this)[1] * v[0] };
#endif
	}

	template<typename real>
	inline OVector2<real> OVector2<real>::normal()
	{
#if defined(INTRINSICS)
		OVector2<real> res;
		normalize4<real, 2>(this->data, res.data);
		return res;
#else
		real l = length();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		return OVector2<real>{(*this)[0] * l, (*this)[1] * l};
#endif
	}

	template<typename real>
	inline void OVector2<real>::normalize()
	{
#if defined(INTRINSICS)
		normalize4<real, 2>(this->data, this->data);
#else
		real l = length();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		(*this)[0] *= l;
		(*this)[1] *= l;
#endif
	}

	template<typename real>
	inline real OVector2<real>::getAngleBetweenVectors(OVector2<real>& v)
	{
#if defined(INTRINSICS)
		real l1 = length();
		real l2 = v.length();

		real d3 = this->dot(v);
		l1 = scalarMul<real>(l1, l2);
		d3 = scalarDiv<real>(d3, l1);

		return Math<real>::odAcos(d3);
#else
		real l1 = this->length3();
		real l2 = v.length3();

		real d3 = this->dot3(v);
		l1 *= l2;
		d3 /= l1;

		return Math<real>::odAcos(d3);
#endif
	}

	template<typename real>
	inline real OVector2<real>::getAngleToTarget(OVector2<real>& v)
	{
		OVector2<real> vv = (*this) - v;
		return Math<real>::odATan(vv.getY(), vv.getX());
	}

}