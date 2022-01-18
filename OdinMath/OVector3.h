#pragma once
#include "OdinMath.h"

namespace OdinMath {

	template<typename real>
	struct OVector3 : public Vector<3, real> {
		OVector3(real x, real y, real z) { this->data[0] = x; this->data[1] = y; this->data[2] = z; }
		OVector3() { this->data[0] = (real)0.0; this->data[1] = (real)0.0; this->data[2] = (real)0.0; }
		OVector3(int x, int y, int z) : OVector3((real)x, (real)y, (real)z) {}
		OVector3(const OVector3<real>& v) { *this = v; }
		virtual ~OVector3() {}

		void set(real x, real y, real z) { this->data[0] = x; this->data[1] = y; this->data[2] = z; }
		void set(const OVector3& v) { *this = v; }
		real getX() { (*this)[0]; }
		void setX(float x) { (*this)[0] = x; }
		real getY() { (*this)[1]; }
		void setY(float y) { (*this)[1] = y; }
		real getZ() { (*this)[2]; }
		void setZ(float z) { (*this)[2] = z; }
		void move(float mx, float my, float mz) { (*this)[0] += mx; (*this)[1] += my; (*this)[2] += mz; }

		


		OVector3 operator+(const OVector3& v1);
		OVector3 operator-(const OVector3& v1);
		void operator+= (const OVector3& v);
		void operator-=(const OVector3& v);
		float operator*(const OVector3& v) { return dot(v); }
		void operator/=(const OVector3& v);
		OVector3 operator/(const OVector3& v);
		bool operator== (const OVector3& v) const;
		bool operator!=(const OVector3& v) const { return !(*this == v); }
		OVector3& operator=(const OVector3& v);
		OVector3 operator>(OVector3& v);
		OVector3 operator>=(OVector3& v);
		void operator/=(real c);
		void operator*=(real val);
		OVector3 operator*(real val);
		/*friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);*/

		real distance(const OVector3& v);
		real length();

		real dot(const OVector3& v);
		OVector3 cross(const OVector3& v);

		OVector3 normal();
		void normalize();

		real getAngleBetweenVectors(OVector3& v);
		float getAngleToTarget(OVector3& v);

		//todo
		bool empty() {
			return this->data[0] == (real)0.0 && this->data[1] == (real)0.0 && this->data[2] == (real)0.0;
		}



		static OVector3<real> zeros() { return OVector3<real>((real)0.f, (real)0.f, (real)0.f); }
		static OVector3<real> ones() { return OVector3<real>((real)1.f, (real)1.f, (real)1.f); }

	};
	template<typename real>
	inline void operator*=(real c, OVector3<real>& v) {
#if defined(INTRINSICS)
		scalarMul3<real>(v.data, c);
#else
		v[0] *= c;
		v[1] *= c;
		v[2] *= c;
#endif
	}
	template<typename real>
	inline OVector3<real> operator*(real c, OVector3<real>& v) {
		OVector3<real> copy(v);
#if defined(INTRINSICS)
		scalarMul3<real>(copy.data, c);
#else
		copy[0] *= c;
		copy[1] *= c;
		copy[2] *= c;
#endif
		return copy;
	}


	template<typename real>
	inline real OVector3<real>::distance(const OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)
		
		sub3<real>(v.data, this->data, res.data);
		
#else
		res[0] = v[0] - (*this)[0];
		res[1] = v[1] - (*this)[1];
		res[2] = v[2] - (*this)[2];

#endif
		return res.length();
	}

	template<typename real>
	inline real OVector3<real>::length()
	{
		return Math<real>::odSqrt(this->dot(*this));
	}

	template<typename real>
	inline real OVector3<real>::dot(const OVector3& v)
	{
#if defined(INTRINSICS)
		return _dot3<real, 3>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
#endif
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::cross(const OVector3& v)
	{
#if defined(INTRINSICS)
		OVector3<real> r;
		cross3<real>(this->data, v.data, r.data);
		return r;
#else
		return OVector3<real>{(*this)[1] * v[2] - (*this)[2] * v[1], (*this)[3] * v[0] - (*this)[0] * v[3], (*this)[0] * v[1] - (*this)[1] * v[0] };
#endif	
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::normal()
	{
#if defined(INTRINSICS)
		OVector3 copy(*this);
		normalize33<real>(copy.data);
		return copy;
#else
		real l = length();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		return OVector3<real>{(*this)[0] * l, (*this)[1] * l, (*this)[2] * l};
#endif

	}
	template<typename real>
	inline void OVector3<real>::normalize()
	{
#if defined(INTRINSICS)
		normalize33<real>(this->data);
#else
		real l = length();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		(*this)[0] *= l;
		(*this)[1] *= l;
		(*this)[2] *= l;

#endif
	}
	template<typename real>
	inline real OVector3<real>::getAngleBetweenVectors(OVector3& v)
	{
#if defined(INTRINSICS)
		real l1 = this->length();
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
	inline float OVector3<real>::getAngleToTarget(OVector3<real>& v)
	{
		OVector3<real> vv = (*this) - v;
		return Math<real>::odATan(vv.getY(), vv.getX());
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator+(const OVector3<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> re;
		add3<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector3<real>{(*this)[0] + v[0], (*this)[1] + v[1], (*this)[2] + v[2]};
#endif
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator-(const OVector3<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> re;
		sub3<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector3<real>{(*this)[0] - v[0], (*this)[1] - v[1], (*this)[2] - v[2]};
#endif	
	}

	template<typename real>
	inline void OVector3<real>::operator+=(const OVector3& v)
	{
#if defined(INTRINSICS)
		add3<real>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] + v[0];
		(*this)[1] = (*this)[1] + v[1];
		(*this)[2] = (*this)[2] + v[2];
#endif
	}

	template<typename real>
	inline void OVector3<real>::operator-=(const OVector3& v)
	{
#if defined(INTRINSICS)
		sub3<real>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] - v[0];
		(*this)[1] = (*this)[1] - v[1];
		(*this)[2] = (*this)[2] - v[2];
#endif
	}


	template<typename real>
	inline void OVector3<real>::operator/=(const OVector3& v)
	{
#if defined(INTRINSICS)
		div3<real>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] / v[0];
		(*this)[1] = (*this)[1] / v[1];
		(*this)[2] = (*this)[2] / v[2];
#endif
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::operator/(const OVector3<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> re;
		div3<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector3<real>{(*this)[0] / v[0], (*this)[1] / v[1], (*this)[2] / v[2], (*this)[3] / v[3]};
#endif
	}

	template<typename real>
	inline bool OVector3<real>::operator==(const OVector3& v) const
	{
#if defined(INTRINSICS)
		return equals4<real, 3>(this->data, v.data);

#else
		return (*this)[0] == v[0] && (*this)[1] == v[1] && (*this)[2] == v[2];
#endif
	}

	template<typename real>
	inline OVector3<real>& OVector3<real>::operator=(const OVector3& v)
	{
		if (this != &v) {
#if defined(INTRINSICS)
			store3<real>(this->data, v.data);

#else
			(*this)[0] = v[0];
			(*this)[1] = v[1];
			(*this)[2] = v[2];
#endif 

		}
		return *this;
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::operator>(OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)
		cmpgt<real, 3>(this->data, v.data, res.data);
#else
		res[0] = (*this) > v[0];
		res[1] = (*this) > v[1];
		res[2] = (*this) > v[2];
#endif
		return res;
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::operator>=(OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)
		cmpgte<real, 3>(this->data, v.data, res.data);
#else
		res[0] = (*this) >= v[0];
		res[1] = (*this) >= v[1];
		res[2] = (*this) >= v[2];
#endif
		return res;
	}

	template<typename real>
	inline void OVector3<real>::operator/=(real c)
	{
#if defined(INTRINSICS)
		scalarDiv3<real>(this->data, c);
#else
		(*this)[0] /= c;
		(*this)[1] /= c;
		(*this)[2] /= c;
#endif
	}

	template<typename real>
	inline void OVector3<real>::operator*=(real c)
	{
#if defined(INTRINSICS)
		scalarMul3<real>(this->data, c);
#else
		(*this)[0] *= c;
		(*this)[1] *= c;
		(*this)[2] *= c;
#endif
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::operator*(real c)
	{
#if defined(INTRINSICS)
		OVector3<real> copy(*this);
		scalarMul3<real>(copy.data, c);
#else
		OVector3<real> copy(*this);
		copy[0] *= c;
		copy[1] *= c;
		copy[2] *= c;
#endif
		return copy;
	}
}