#pragma once
#include "OdinMath.h"
namespace OdinMath {



	template<typename real>
	struct OVector4 : public Vector<4, real>
	{
		OVector4(real x, real y, real z, real w=(real)0.0f) { this->data[0] = x; this->data[1] = y; this->data[2] = z; this->data[3] = w; }
		OVector4() { OVector4((real)0.f, (real)0.f, (real)0.f, (real)0.f); }
		OVector4(int x, int y, int z, int w = 0) : OVector4((float)x, (float)y, (float)z, (float)w) {}

		virtual ~OVector4() {}

		void set(real x, real y, real z, real w = 0.0f) { this->data[0] = x; this->data[1] = y; this->data[2] = z; this->data[3] = w; }
		void set(const OVector4& v) { *this = v; }
		real getX() { (*this)[0]; }
		void setX(float x) { (*this)[0] = x; }
		real getY() { (*this)[1]; }
		void setY(float y) { (*this)[1] = y; }
		real getZ() { (*this)[2]; }
		void setZ(float z) { (*this)[2] = z; }
		real getW() { (*this)[3]; }
		void setW(float w) { (*this)[3] = w; }
		void move(float mx, float my, float mz, float mw = 0.0f) { (*this)[0] += mx; (*this)[1] += my; (*this)[2] += mz; (*this)[3] += mw; }

		real distance(const OVector4& v);
		real length3();
		real length();

		real dot(const OVector4& v);
		real dot3(const OVector4& v);
		OVector4 cross(const OVector4& v);

		OVector4 normal();
		void normalize3();
		void normalize();

		real getAngleBetweenVectors(OVector4& v);
		float getAngleToTarget(DXVector4& v);


		OVector4 operator+(const OVector4& v1);
		OVector4 operator-(const OVector4& v1);
		void operator+= (const OVector4& v) { *this = *this + v; }
		void operator-=(const OVector4& v) { *this = *this - v; }
		float operator*(const OVector4& v) { return dot(v); }
		void operator/=(const OVector4& v) { *this = *this / v; }
		OVector4 operator/(const OVector4& v);
		bool operator== (const OVector4& v) const;
		bool operator!=(const OVector4& v) const { return !(*this == v); }
		OVector4& operator=(const OVector4& v);
		
		void operator/=(real c);
		void operator*=(real val);
		OVector4 operator*(real val);
		/*friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);*/


		//todo
		bool empty() {
			return this->data[0] == (real)0.0 && this->data[1] == (real)0.0 && this->data[2] == (real)0.0;
		}



	};


	template<typename real>
	inline real OVector4<real>::distance(const OVector4& v)
	{
		OVector4 d = v - *this;
		return d.length3();
	}

	template<typename real>
	inline real OVector4<real>::length3()
	{
		return Math<real>::odSqrt(this->dot3(*this));
	}

	template<typename real>
	inline real OVector4<real>::length()
	{
		return Math<real>::odSqrt(this->dot(*this));
	}

	template<typename real>
	inline real OVector4<real>::dot(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		return dot4<real>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2] + (*this)[3] * v[3];
#endif // INSTRINSICS

		
	}

	template<typename real>
	inline real OVector4<real>::dot3(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		return _dot3<real>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
#endif
		
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::cross(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> r;
		cross4<real>(this->data, v.data, r.data);
		return r;
#else
		return OVector4<real>{(*this)[1] * v[2] - (*this)[2] * v[1], (*this)[3] * v[0] - (*this)[0] * v[3], (*this)[0] * v[1] - (*this)[1] * v[0] };
#endif
		
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::normal()
	{
#if defined(INTRINSICS)
		OVector4 copy(*this);
		normalize43(copy.data);
		return copy;
#else
		real l = length3();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		return OVector4<real>{(*this)[0] * l, (*this)[1] * l, (*this)[2] * l};
#endif // defined(INTRINSICS)

		
	}

	template<typename real>
	inline void OVector4<real>::normalize3()
	{
#if defined(INTRINSICS)
		normalize43<real>(this->data);

#else
		real l = length3();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		(*this)[0] *= l;
		(*this)[1] *= l;
		(*this)[2] *= l;
#endif
		
	}

	template<typename real>
	inline void OVector4<real>::normalize()
	{
#if defined(INTRINSICS)
		normalize4<real>(this->data);
		
#else
		real l = length3();
		if (l > (real)0.0) {
			l = (real)1.0 / l;
		}
		(*this)[0] *= l;
		(*this)[1] *= l;
		(*this)[2] *= l;
		(*this)[3] *= l;
#endif
		
	}

	template<typename real>
	inline real OVector4<real>::getAngleBetweenVectors(OVector4<real>& v)
	{

#if defined(INTRINSICS)
		real l1 = this->length3();
		real l2 = v.length3();

		real d3 = this->dot3(v);
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
	inline float OVector4<real>::getAngleToTarget(DXVector4& v)
	{
		OVector4<real> vv = (*this) - v;
		return Math<real>::odATan(vv.getY(), vv.getX());
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator+(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> re;
		add4<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector4<real>{(*this)[0] + v[0], (*this)[1] + v[1], (*this)[2] + v[2], (*this)[3] + v[3]};
#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator-(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> re;
		sub4<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector4<real>{(*this)[0] - v[0], (*this)[1] - v[1], (*this)[2] - v[2], (*this)[3] - v[3]};
#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator/(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> re;
		div4<real>(this->data, v.data, re.data);
		return re;

#else
		return OVector4<real>{(*this)[0] - v[0], (*this)[1] - v[1], (*this)[2] - v[2], (*this)[3] - v[3]};
#endif
	}

	template<typename real>
	inline bool OVector4<real>::operator==(const OVector4<real>& v) const
	{
#if defined(INTRINSICS)
		return equals4<real>(this->data, v.data);
#else
		return (*this)[0] == v[0] && (*this)[1] == v[1] && (*this)[2] == v[2] && (*this)[3] == v[3];
#endif

		return false;
	}

	template<typename real>
	inline OVector4<real>& OVector4<real>::operator=(const OVector4<real>& v)
	{
		if (this != &v) {
#if defined(INTRINSICS)
			store4<real>(this->data, v.data);
			
#else
			(*this)[0] = v[0];
			(*this)[1] = v[1];
			(*this)[2] = v[2];
			(*this)[3] = v[3];
#endif // INTRINSICS

		}
		return *this;
	}

	template<typename real>
	inline void OVector4<real>::operator/=(real c)
	{
#if defined(INTRINSICS)
		scalarDiv4<real>(this->data, c);
#else
		(*this)[0] /= c;
		(*this)[1] /= c;
		(*this)[2] /= c;
		(*this)[3] /= c;
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator*=(real c)
	{
#if defined(INTRINSICS)
		scalarMul4<real>(this->data, c);
#else
		(*this)[0] *= c;
		(*this)[1] *= c;
		(*this)[2] *= c;
		(*this)[3] *= c;
#endif // defined(INTRINSICS)

	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator*(real c)
	{
#if defined(INTRINSICS)
		OVector4<real> copy(*this);
		scalarMul4<real>(copy.data, c);

#else
		OVector4<real> copy(*this);
		copy[0] *= c;
		copy[1] *= c;
		copy[2] *= c;
		copy[3] *= c;
		return copy;

#endif
	}


}
