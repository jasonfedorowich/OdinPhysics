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
		void setX(real x) { (*this)[0] = x; }
		real getY() { (*this)[1]; }
		void setY(real y) { (*this)[1] = y; }
		real getZ() { (*this)[2]; }
		void setZ(real z) { (*this)[2] = z; }
		void move(real mx, real my, real mz) { (*this) += OVector3(mx, my, mz); }

		


		OVector3 operator+(const OVector3& v1);
		OVector3 operator-(const OVector3& v1);
		void operator+= (const OVector3& v);
		void operator+= (OVector3&& v);
		void operator-=(const OVector3& v);
		real operator*(const OVector3& v) { return dot(v); }
		void operator/=(const OVector3& v);
		OVector3 operator/(const OVector3& v);
		bool operator== (const OVector3& v) const;
		bool operator!=(const OVector3& v) const { return !(*this == v); }
		OVector3& operator=(const OVector3& v);
		OVector3 operator>(OVector3& v);
		OVector3 operator>=(OVector3& v);
		OVector3 operator>(OVector3&& v);
		OVector3 operator>=(OVector3&& v);
		void operator/=(real c);
		void operator*=(real val);
		OVector3 operator*(real val);

		OVector3<real> operator^(real val);
		void operator^=(real val);

		OVector3<real> operator%(OVector3<real>& v);
		OVector3<real> operator%(OVector3<real>&& v);

		void operator%=(OVector3<real>& v);
		void operator%=(OVector3<real>&& v);

		OVector3<real> operator&(OVector3<real>& v);
		void operator&=(OVector3<real>& v);

		OVector3<real> operator|(OVector3<real>& v);
		void operator|=(OVector3<real>& v);

		template<int X, int Y, int Z>
		OVector3<real> swizzle();


		/*friend void operator*=(float val, DXVector4& vector);
		friend DXVector4 operator*(float val, DXVector4& vector);*/

		real distance(const OVector3& v);
		real length();

		real dot(const OVector3& v);
		OVector3 cross(const OVector3& v);

		OVector3 normal();
		void normalize();

		real getAngleBetweenVectors(OVector3& v);
		real getAngleToTarget(OVector3& v);

		static OVector3<real> zeros() { return OVector3<real>((real)0.f, (real)0.f, (real)0.f); }
		static OVector3<real> ones() { return OVector3<real>((real)1.f, (real)1.f, (real)1.f); }
		//todo
		bool empty() {
			return (*this) == OVector3<real>::zeros();
		}



		

	};


	template<typename real>
	const OVector3<real> factors[8] = { {(real)-1.f, (real)-1.f, (real)-1.f}, {(real)-1.f, (real)-1.f, (real)1.f}, {(real)-1.f, (real)1.f, (real)1.f}, {(real)1.f, (real)1.f, (real)1.f}, {(real)1.f, (real)-1.f, (real)-1.f}, {(real)1.f, (real)-1.f, (real)1.f}, {(real)1.f, (real)1.f, (real)-1.f},  {(real)-1.f, (real)1.f, (real)-1.f}};

	template<typename real>
	inline void max(OVector3<real>& m1, OVector3<real>& m2, OVector3<real>& res) {
#if defined(INTRINSICS)
		vMax<real, 3>(m1.data, m2.data, res.data);
#else
		res[0] = Math<rl>::odMax(m1[0], m2[0]);
		res[1] = Math<rl>::odMax(m1[1], m2[1]);
		res[2] = Math<rl>::odMax(m1[2], m2[2]);
#endif
	}

	template<typename real>
	inline void min(OVector3<real>& m1, OVector3<real>& m2, OVector3<real>& res) {
#if defined(INTRINSICS)
		vMin<real, 3>(m1.data, m2.data, res.data);
#else
		res[0] = Math<rl>::odMin(m1[0], m2[0]);
		res[1] = Math<rl>::odMin(m1[1], m2[1]);
		res[2] = Math<rl>::odMin(m1[2], m2[2]);
#endif
	}
	template<typename real>
	inline void vAbs(OVector3<real>& v) {
#if defined(INTRINSICS)
		abs4<real, 3>(v.data, v.data);
#else
		v.data[0] = Math<real>::odAbs(v.data[0]);
		v.data[1] = Math<real>::odAbs(v.data[1]);
		v.data[2] = Math<real>::odAbs(v.data[2]);
#endif // defined(INTRINSICS)
	}

	template<typename real>
	inline void operator*=(real c, OVector3<real>& v) {
#if defined(INTRINSICS)
		scalarMul4<real, 3>(v.data, c, v.data);
#else
		v[0] *= c;
		v[1] *= c;
		v[2] *= c;
#endif
	}
	template<typename real>
	inline OVector3<real> operator*(real c, OVector3<real>& v) {
		OVector3<real> res;
#if defined(INTRINSICS)
		scalarMul4<real, 3>(v.data, c, res.data);
#else
		res[0] = c * v[0];
		res[1] = c * v[1];
		res[2] = c * v[2];
#endif
		return res;
	}


	template<typename real>
	inline real OVector3<real>::distance(const OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)
		
		sub4<real, 3>(v.data, this->data, res.data);
		
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
		cross4<real, 3>(this->data, v.data, r.data);
		return r;
#else
		return OVector3<real>{(*this)[1] * v[2] - (*this)[2] * v[1], (*this)[3] * v[0] - (*this)[0] * v[3], (*this)[0] * v[1] - (*this)[1] * v[0] };
#endif	
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::normal()
	{
#if defined(INTRINSICS)
		OVector3 res;
		normalize4<real, 3>(this->data, res.data);
		return res;
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
		normalize4<real, 3>(this->data, this->data);
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
	inline real OVector3<real>::getAngleToTarget(OVector3<real>& v)
	{
		OVector3<real> vv = (*this) - v;
		return Math<real>::odATan(vv.getY(), vv.getX());
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator+(const OVector3<real>& v)
	{
#if defined(INTRINSICS)
		OVector3<real> re;
		add4<real, 3>(this->data, v.data, re.data);
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
		sub4<real, 3>(this->data, v.data, re.data);
		return re;

#else
		return OVector3<real>{(*this)[0] - v[0], (*this)[1] - v[1], (*this)[2] - v[2]};
#endif	
	}

	template<typename real>
	inline void OVector3<real>::operator+=(const OVector3& v)
	{
#if defined(INTRINSICS)
		add4<real, 3>(this->data, v.data, this->data);

#else
		(*this)[0] = (*this)[0] + v[0];
		(*this)[1] = (*this)[1] + v[1];
		(*this)[2] = (*this)[2] + v[2];
#endif
	}

	template<typename real>
	inline void OVector3<real>::operator+=(OVector3&& v)
	{
#if defined(INTRINSICS)
		add4<real, 3>(this->data, v.data, this->data);

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
		sub4<real, 3>(this->data, v.data, this->data);

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
		div4<real, 3>(this->data, v.data, this->data);

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
		div4<real, 3>(this->data, v.data, re.data);
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
	inline OVector3<real> OVector3<real>::operator>(OVector3<real>&& v)
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
	inline OVector3<real> OVector3<real>::operator>=(OVector3<real>&& v)
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
		scalarDiv4<real, 3>(this->data, c, this->data);
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
		scalarMul4<real, 3>(this->data, c, this->data);
#else
		(*this)[0] *= c;
		(*this)[1] *= c;
		(*this)[2] *= c;
#endif
	}

	template<typename real>
	inline OVector3<real> OVector3<real>::operator*(real c)
	{
		OVector3<real> res;
#if defined(INTRINSICS)
		scalarMul4<real, 3>(this->data, c, res.data);
#else
		res[0] = this->data[0] * c;
		res[1] = this->data[1] * c;
		res[2] = this->data[2] * c;
#endif
		return res;
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator^(real val)
	{
		OVector3<real> res;
#if defined(INTRINSICS)

		pow4<real, 3>(this->data, val, res.data);

#else

		res[0] = Math<real>::odPow(this->data[0], val);
		res[1] = Math<real>::odPow(this->data[1], val);
		res[2] = Math<real>::odPow(this->data[2], val);

#endif
		return res;
	}
	template<typename real>
	inline void OVector3<real>::operator^=(real val)
	{
#if defined(INTRINSICS)

		pow4<real, 3>(this->data, val, this->data);

#else

		this->data[0] = Math<real>::odPow(this->data[0], val);
		this->data[1] = Math<real>::odPow(this->data[1], val);
		this->data[2] = Math<real>::odPow(this->data[2], val);

#endif
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator%(OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)

		mul4<real, 3>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] * v[0];
		res[1] = this->data[1] * v[1];
		res[2] = this->data[2] * v[2];

#endif
		return res;
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator%(OVector3<real>&& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)

		mul4<real, 3>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] * v[0];
		res[1] = this->data[1] * v[1];
		res[2] = this->data[2] * v[2];

#endif
		return res;
	}
	template<typename real>
	inline void OVector3<real>::operator%=(OVector3<real>& v)
	{
#if defined(INTRINSICS)

		mul4<real, 3>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] * v[0];
		this->data[1] = this->data[1] * v[1];
		this->data[2] = this->data[2] * v[2];

#endif
	}
	template<typename real>
	inline void OVector3<real>::operator%=(OVector3<real>&& v)
	{
#if defined(INTRINSICS)

		mul4<real, 3>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] * v[0];
		this->data[1] = this->data[1] * v[1];
		this->data[2] = this->data[2] * v[2];

#endif
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator&(OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)

		and4<real, 3>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] & v[0];
		res[1] = this->data[1] & v[1];
		res[2] = this->data[2] & v[2];

#endif
		return res;
	}
	template<typename real>
	inline void OVector3<real>::operator&=(OVector3<real>& v)
	{
#if defined(INTRINSICS)

		and4<real, 3>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] & v[0];
		this->data[1] = this->data[1] & v[1];
		this->data[2] = this->data[2] & v[2];

#endif
	}
	template<typename real>
	inline OVector3<real> OVector3<real>::operator|(OVector3<real>& v)
	{
		OVector3<real> res;
#if defined(INTRINSICS)

		or4<real, 3>(this->data, v.data, res.data);

#else

		res[0] = this->data[0] | v[0];
		res[1] = this->data[1] | v[1];
		res[2] = this->data[2] | v[2];

#endif
		return res;
	}
	template<typename real>
	inline void OVector3<real>::operator|=(OVector3<real>& v)
	{
#if defined(INTRINSICS)

		or4<real, 3>(this->data, v.data, this->data);

#else

		this->data[0] = this->data[0] | v[0];
		this->data[1] = this->data[1] | v[1];
		this->data[2] = this->data[2] | v[2];

#endif
	}

	template<typename real>
	template<int X, int Y, int Z>
	inline OVector3<real> OVector3<real>::swizzle() {
		return;
	}

	template<>
	template<int X, int Y, int Z>
	inline OVector3<float> OVector3<float>::swizzle() {
		assert((X < 4) && (Y < 4) && (Z < 4));
		assert((X >= 0) && (Y >= 0) && (Z >= 0));
#if defined(INTRINSICS)
		OVector3<float> res;
		InVectf v = loadVector3(this->data);
		v = PERMUTE_PS(v, _MM_SHUFFLE(Z, Z, Y, X));
		storeVector3(res.data, v);
		return res;
#else
		return OVector3<real>(this->data[X], this->data[Y], this->data[Z]);
#endif

	}
	template<>
	template<int X, int Y, int Z>
	inline OVector3<double> OVector3 <double>::swizzle() {
		assert((X < 4) && (Y < 4) && (Z < 4));
		assert((X >= 0) && (Y >= 0) && (Z >= 0));
#if defined(INTRINSICS)
		OVector3<double> res;
		InVectd v = loadVector3(this->data);
		v = _mm256_permutex_pd(v, _MM_SHUFFLE(Z, Z, Y, X));
		storeVector3(res.data, v);
		return res;
#else
		return OVector3<real>(this->data[X], this->data[Y], this->data[Z]);
#endif
	}


	




}