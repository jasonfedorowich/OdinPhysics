#pragma once
#include "OdinMath.h"
namespace OdinMath {



	template<typename real>
	struct OVector4 : public Vector<4, real>
	{
		OVector4(real x, real y, real z, real w=(real)0.0f) { this->data[0] = x; this->data[1] = y; this->data[2] = z; this->data[3] = w; }
		OVector4() : OVector4((real)0.f, (real)0.f, (real)0.f, (real)0.f) {  }
		OVector4(int x, int y, int z, int w = 0) : OVector4((float)x, (float)y, (float)z, (float)w) {}
		OVector4(const OVector4<real>& v) { *this = v; }
		virtual ~OVector4() {}

		void set(real x, real y, real z, real w = 0.0f) { this->data[0] = x; this->data[1] = y; this->data[2] = z; this->data[3] = w; }
		void set(const OVector4& v) { *this = v; }
		real getX() { return (*this)[0]; }
		void setX(real x) { (*this)[0] = x; }
		real getY() { return (*this)[1]; }
		void setY(real y) { (*this)[1] = y; }
		real getZ() { return (*this)[2]; }
		void setZ(real z) { (*this)[2] = z; }
		real getW() { return (*this)[3]; }
		void setW(real w) { (*this)[3] = w; }
		void move(real mx, real my, real mz, real mw = 0.0f) { (*this) += OVector4<real>(mx, my, mz, mw); }

		real distance(const OVector4& v);
		real length3();
		real length();

		real dot(const OVector4& v);
		real dot3(const OVector4& v);
		OVector4 cross(const OVector4& v);

		OVector4 normal();
		void normalize3();
		void normalize();
		

		real norm();

		real getAngleBetweenVectors(OVector4<real>& v);
		real getAngleToTarget(OVector4<real>& v);


		OVector4 operator+(const OVector4& v1);
		OVector4 operator-(const OVector4& v1);
		void operator+= (const OVector4& v);
		void operator+= (OVector4&& v);
		void operator-=(const OVector4& v);
		real operator*(const OVector4& v) { return dot(v); }
		void operator/=(const OVector4& v);
		OVector4 operator/(const OVector4& v);
		bool operator== (const OVector4& v) const;
		bool operator!=(const OVector4& v) const { return !(*this == v); }
		OVector4& operator=(const OVector4& v);
		OVector4 operator>(OVector4& v);
		OVector4 operator>=(OVector4& v);
		void operator/=(real c);
		void operator*=(real val);
		OVector4 operator*(real val);

		OVector4<real> operator^(real val);
		void operator^=(real val);

		OVector4<real> operator&(OVector4<real>& v);
		void operator&=(OVector4<real>& v);

		OVector4<real> operator|(OVector4<real>& v);
		void operator|=(OVector4<real>& v);

		OVector4<real> operator%(OVector4<real>& v);
		void operator%=(OVector4<real>& v);
		

		/*friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);*/

		static OVector4<real> zeros() { return OVector4<real>((real)0.f, (real)0.f, (real)0.f, (real)0.f); }
		static OVector4<real> ones() { return OVector4<real>((real)1.f, (real)1.f, (real)1.f, (real)1.f); }

		//todo
		bool empty() {
			return (*this) == OVector4<real>::zeros();
		}

		
	};

	template<typename real>
	inline void vAbs(OVector4<real>& v) {
#if defined(INTRINSICS)
		scalarMul4<real, 4>(v.data, v.data);
#else
		v.data[0] = Math<real>::odAbs(v.data[0]);
		v.data[1] = Math<real>::odAbs(v.data[1]);
		v.data[2] = Math<real>::odAbs(v.data[2]);
		v.data[3] = Math<real>::odAbs(v.data[3]);

#endif // defined(INTRINSICS)

	}
	
	template<typename real>
	inline void operator*=(real c, OVector4<real>& v) {
#if defined(INTRINSICS)
		scalarMul4<real, 4>(v.data, c, v.data);
#else
		v[0] *= c;
		v[1] *= c;
		v[2] *= c;
		v[3] *= c;
#endif // defined(INTRINSICS)

	}

	template<typename real>
	inline OVector4<real> operator*(real c, OVector4<real>& v) {
		OVector4<real> res;
#if defined(INTRINSICS)
		scalarMul4<real, 4>(v.data, c, res.data);
#else
		res[0] = c * v[0];
		res[1] = c * v[1];
		res[2] = c * v[2];
		res[3] = c * v[3];
#endif // defined(INTRINSICS)
		return res;
	}

	template<typename real>
	inline real OVector4<real>::distance(const OVector4<real>& v)
	{
		OVector4<real> res;
#if defined(INTRINSICS)

		sub4<real, 4>(v.data, this->data, res.data);

#else
		res[0] = v[0] - (*this)[0];
		res[1] = v[1] - (*this)[1];
		res[2] = v[2] - (*this)[2];
		res[3] = v[3] - (*this)[3];
#endif
		return res.length();
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
		return dot4<real, 4>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2] + (*this)[3] * v[3];
#endif // INSTRINSICS

		
	}

	template<typename real>
	inline real OVector4<real>::dot3(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		return _dot3<real, 4>(this->data, v.data);

#else
		return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
#endif
		
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::cross(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> r;
		cross4<real, 4>(this->data, v.data, r.data);
		return r;
#else
		return OVector4<real>{(*this)[1] * v[2] - (*this)[2] * v[1], (*this)[3] * v[0] - (*this)[0] * v[3], (*this)[0] * v[1] - (*this)[1] * v[0] };
#endif
		
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::normal()
	{
#if defined(INTRINSICS)
		OVector4<real> res;
		normalize4<real, 3>(this->data, res.data);
		return res;
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
		normalize4<real, 3>(this->data, this->data);

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
		normalize4<real, 4>(this->data, this->data);
		
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
		real l1 = this->length();
		real l2 = v.length();

		real d3 = this->dot(v);
		l1 *= l2;
		d3 /= l1;

		return Math<real>::odAcos(d3);
#endif
		


	}

	template<typename real>
	inline real OVector4<real>::getAngleToTarget(OVector4<real>& v)
	{
		OVector4<real> vv = (*this) - v;
		return Math<real>::odATan(vv.getY(), vv.getX());
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator+(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> re;
		add4<real, 4>(this->data, v.data, re.data);
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
		sub4<real, 4>(this->data, v.data, re.data);
		return re;

#else
		return OVector4<real>{(*this)[0] - v[0], (*this)[1] - v[1], (*this)[2] - v[2], (*this)[3] - v[3]};
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator+=(const OVector4& v)
	{
#if defined(INTRINSICS)
		add4<real, 4>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] + v[0];
		(*this)[1] = (*this)[1] + v[1];
		(*this)[2] = (*this)[2] + v[2];
		(*this)[3] = (*this)[3] + v[3];
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator+=(OVector4&& v)
	{
#if defined(INTRINSICS)
		add4<real, 4>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] + v[0];
		(*this)[1] = (*this)[1] + v[1];
		(*this)[2] = (*this)[2] + v[2];
		(*this)[3] = (*this)[3] + v[3];
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator-=(const OVector4& v)
	{
#if defined(INTRINSICS)
		sub4<real, 4>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] - v[0];
		(*this)[1] = (*this)[1] - v[1];
		(*this)[2] = (*this)[2] - v[2];
		(*this)[3] = (*this)[3] - v[3];
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator/=(const OVector4& v)
	{
#if defined(INTRINSICS)
		div4<real, 4>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] / v[0];
		(*this)[1] = (*this)[1] / v[1];
		(*this)[2] = (*this)[2] / v[2];
		(*this)[3] = (*this)[3] / v[3];
#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator/(const OVector4<real>& v)
	{
#if defined(INTRINSICS)
		OVector4<real> re;
		div4<real, 4>(this->data, v.data, re.data);
		return re;

#else
		return OVector4<real>{(*this)[0] / v[0], (*this)[1] / v[1], (*this)[2] / v[2], (*this)[3] / v[3]};
#endif
	}

	template<typename real>
	inline bool OVector4<real>::operator==(const OVector4<real>& v) const
	{
#if defined(INTRINSICS)
		return equals4<real, 4>(this->data, v.data);
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
	inline OVector4<real> OVector4<real>::operator>(OVector4<real>& v)
	{
		OVector4<real> res;
#if defined(INTRINSICS)
		cmpgt<real, 4>(this->data, v.data, res.data);
#else
		res[0] = (*this) > v[0];
		res[1] = (*this) > v[1];
		res[2] = (*this) > v[2];
		res[3] = (*this) > v[3];
#endif
		return res;
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator>=(OVector4<real>& v)
	{
		OVector4<real> res;
#if defined(INTRINSICS)
		cmpgte<real, 4>(this->data, v.data, res.data);
		return res;
#else
		res[0] = (*this) >= v[0];
		res[1] = (*this) >= v[1];
		res[2] = (*this) >= v[2];
		res[3] = (*this) >= v[3];
#endif
	}

	template<typename real>
	inline void OVector4<real>::operator/=(real c)
	{
#if defined(INTRINSICS)
		scalarDiv4<real, 4>(this->data, c, this->data);
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
		scalarMul4<real, 4>(this->data, c, this->data);
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
		OVector4<real> res;
#if defined(INTRINSICS)
		
		scalarMul4<real, 4>(this->data, c, res.data);

#else
		
		res[0] = this->data[0] * c;
		res[1] = this->data[1] * c;
		res[2] = this->data[2] * c;
		res[3] = this->data[3] * c;
		

#endif
		return res;
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator^(real val)
	{
		OVector4<real> res;
#if defined(INTRINSICS)

		pow4<real, 4>(this->data, val, res.data);

#else

		res[0] = Math<real>::odPow(this->data[0], val);
		res[1] = Math<real>::odPow(this->data[1], val);
		res[2] = Math<real>::odPow(this->data[2], val);
		res[3] = Math<real>::odPow(this->data[3], val);

#endif
		return res;
	}

	template<typename real>
	inline void OVector4<real>::operator^=(real val)
	{
#if defined(INTRINSICS)

		pow4<real, 4>(this->data, val, this->data);

#else

		this->data[0] = Math<real>::odPow(this->data[0], val);
		this->data[1] = Math<real>::odPow(this->data[1], val);
		this->data[2] = Math<real>::odPow(this->data[2], val);
		this->data[3] = Math<real>::odPow(this->data[3], val);

#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator&(OVector4<real>& v)
	{
		OVector4<real> res;
#if defined(INTRINSICS)

		and4<real, 4>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] & v[0];
		res[1] = this->data[1] & v[1];
		res[2] = this->data[2] & v[2];
		res[3] = this->data[3] & v[3];

#endif
	}

	template<typename real>
	inline void OVector4<real>::operator&=(OVector4<real>& v)
	{
#if defined(INTRINSICS)

		and4<real, 4>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] & v[0];
		this->data[1] = this->data[1] & v[1];
		this->data[2] = this->data[2] & v[2];
		this->data[3] = this->data[3] & v[3];

#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator|(OVector4<real>& v)
	{
		OVector4<real> res;

#if defined(INTRINSICS)

		or4<real, 4>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] | v[0];
		res[1] = this->data[1] | v[1];
		res[2] = this->data[2] | v[2];
		res[3] = this->data[3] | v[3];

#endif
		return res;
	}

	template<typename real>
	inline void OVector4<real>::operator|=(OVector4<real>& v)
	{
#if defined(INTRINSICS)

		or4<real, 4>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] | v[0];
		this->data[1] = this->data[1] | v[1];
		this->data[2] = this->data[2] | v[2];
		this->data[3] = this->data[3] | v[3];

#endif
	}

	template<typename real>
	inline OVector4<real> OVector4<real>::operator%(OVector4<real>& v)
	{
		OVector4<real> res;
#if defined(INTRINSICS)

		mul4<real, 4>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] * v[0];
		res[1] = this->data[1] * v[1];
		res[2] = this->data[2] * v[2];
		res[3] = this->data[3] * v[3];

#endif
		return res;
	}

	template<typename real>
	inline void OVector4<real>::operator%=(OVector4<real>& v)
	{
#if defined(INTRINSICS)

		mul4<real, 4>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] * v[0];
		this->data[1] = this->data[1] * v[1];
		this->data[2] = this->data[2] * v[2];
		this->data[3] = this->data[3] * v[3];

#endif
	}




}
