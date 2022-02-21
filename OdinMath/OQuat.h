#pragma once
#include "OdinMath.h"
namespace OdinMath {

	/*convention used is q = (x, y, z, w) where w is real and x, y, z are complex*/
	template<typename real>
	struct OQuat : public Vector<4, real> {
		OQuat(real x, real y, real z, real w) { this->data[0] = x; this->data[1] = y; this->data[2] = z; this->data[3] = w; }
		OQuat(real angle, OVector3<real>& axis);
		OQuat(real roll, real pitch, real yaw);

		OQuat(OQuat& q) { *this = q; }
		OQuat(OMatrix4<real>& m);
		OQuat(OMatrix3<real>& m);
		OQuat(OMatrix4<real>&& m);
		OQuat(OMatrix3<real>&& m);

		OQuat() : OQuat((real)0.0, (real)0.0, (real)0.0, (real)1.0) {};
		~OQuat() {};

		OQuat<real>& operator=(const OQuat<real>& q);
		OQuat<real> operator+(OQuat<real>& q);
		OQuat<real> operator*(OQuat<real>& q);
		OQuat<real> operator*(real s);
		OQuat<real> operator-(OQuat<real>& q);

		void operator*=(OQuat<real>& q);
		void operator+=(OQuat<real>& q);
		void operator*=(real s);

		void toRotation(OMatrix4<real>& m);
		void toRotation(OMatrix3<real>& m);

		real length();

		void rollPitchYaw(real* rpy);
		void axisRotation(Vector<3, real>& axis, real& rotation);


		void normalize();
		OQuat normal();

	};


#include "OQuat.inl"
	
	
	template<typename real>
	inline OQuat<real>::OQuat(real angle, OVector3<real>& axis)
	{
#if defined(INTRINSICS)
		tquatfRotAxis<real>(angle, axis.data, this->data);
#else
		axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(real roll, real pitch, real yaw)
	{
#if defined(INTRINSICS)
		tquatfEuler<real>(roll, pitch, yaw, this->data);
#else
		//todo
		axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(OMatrix4<real>& m)
	{
#if defined(INTRINSICS)
		tquatfRotMat<real, 4>(m.m, this->data);
#else
		quatRotMatrix<real, 4>(m, *this);
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(OMatrix3<real>& m)
	{
#if defined(INTRINSICS)
		tquatfRotMat<real, 3>(m.m, this->data);
#else
		quatRotMatrix<real, 3>(m, *this);
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(OMatrix4<real>&& m)
	{
#if defined(INTRINSICS)
		tquatfRotMat<real, 4>(m.m, this->data);
#else
		quatRotMatrix<real, 4>(m, *this);
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(OMatrix3<real>&& m)
	{
#if defined(INTRINSICS)
		tquatfRotMat<real, 3>(m.m, this->data);
#else
		quatRotMatrix<real, 3>(m, *this);
#endif
	}
	template<typename real>
	inline OQuat<real> OQuat<real>::operator*(OQuat<real>& q)
	{
		OQuat<real> res;
#if defined(INTRINSICS)
		
		multQuat<real>(this->data, q.data, res.data);
		
#else
		real q1x = this->data[0];
		real q1y = this->data[1];
		real q1z = this->data[2];
		real q1w = this->data[3];

		real q2x = q[0];
		real q2y = q[1];
		real q2z = q[2];
		real q2w = q[3];

		res[0] = (q1w * q2x) + (q1x * q2w) + (q1y * q2z) - (q1z * q2y);
		res[1] = (q1w * q2y) - (q1x * q2z) + (q1y * q2w) + (q1z * q2x);
		res[2] = (q1w * q2z) + (q1x * q2y) - (q1y * q2x) + (q1z * q2w);
		res[3] = (q1w * q2w) - (q1x * q2x) - (q1y * q2y) - (q1z * q2z);
		


#endif
		return res;
	}
	template<typename real>
	inline OQuat<real> OQuat<real>::operator*(real s)
	{
		OQuat<real> res;
#if defined(INTRINSICS)
		
		scalarMul4<real>(res.data, s);
		return res;
#else
		res.data[0] *= s;
		res.data[1] *= s;
		res.data[2] *= s;
		res.data[3] *= s;
#endif
		return res;
	}
	template<typename real>
	inline OQuat<real> OQuat<real>::operator-(OQuat<real>& q)
	{
		OQuat<real> res;
#if defined(INTRINSICS)
		sub4<real>(this->data, q.data, res.data);
#else
		res[0] = (*this)[0] - q[0];
		res[1] = (*this)[1] - q[1];
		res[2] = (*this)[2] - q[2];
		res[3] = (*this)[3] - q[3];
#endif
		return res;

	}
	template<typename real>
	inline void OQuat<real>::operator*=(OQuat<real>& q)
	{
#if defined(INTRINSICS)
		multQuat<real>(this->data, q.data, this->data);

#else
		real q1x = this->data[0];
		real q1y = this->data[1];
		real q1z = this->data[2];
		real q1w = this->data[3];

		real q2x = q[0];
		real q2y = q[1];
		real q2z = q[2];
		real q2w = q[3];

		this->data[0] = (q1w * q2x) + (q1x * q2w) + (q1y * q2z) - (q1z * q2y);
		this->data[1] = (q1w * q2y) - (q1x * q2z) + (q1y * q2w) + (q1z * q2x);
		this->data[2] = (q1w * q2z) + (q1x * q2y) - (q1y * q2x) + (q1z * q2w);
		this->data[3] = (q1w * q2w) - (q1x * q2x) - (q1y * q2y) - (q1z * q2z);
#endif
	}
	template<typename real>
	inline void OQuat<real>::operator+=(OQuat<real>& q)
	{
#if defined(INTRINSICS)
		add4<real>(this->data, q.data, this->data);
#else
		(*this)[0] = (*this)[0] + q[0];
		(*this)[1] = (*this)[1] + q[1];
		(*this)[2] = (*this)[2] + q[2];
		(*this)[3] = (*this)[3] + q[3];
#endif
	}
	template<typename real>
	inline void OQuat<real>::operator*=(real s)
	{
#if defined(INTRINSICS)
		scalarMul4<real>(this.data, s);
#else
		(*this)[0] *= s;
		(*this)[1] *= s;
		(*this)[2] *= s;
		(*this)[3] *= s;
#endif

	}
	template<typename real>
	inline void OQuat<real>::toRotation(OMatrix4<real>& m)
	{
#if defined(INTRINSICS)
		trotMatfQuat<real, 4>(this->data, m.m);
#else
		rotMatrixQuat<real, 4>(*this, m);
#endif
	}
	template<typename real>
	inline void OQuat<real>::toRotation(OMatrix3<real>& m)
	{
#if defined(INTRINSICS)
		trotMatfQuat<real, 3>(this->data, m.m);
#else
		rotMatrixQuat<real, 3>(*this, m);
#endif
	}
	template<typename real>
	inline real OQuat<real>::length()
	{
#if defined(INTRINSICS)
		return Math<real>::odSqrt(dot4<real>(this->data, this->data));
#else
		real xx = this->data[0] * this->data[0];
		real yy = this->data[1] * this->data[1];
		real zz = this->data[2] * this->data[2];
		real ww = this->data[3] * this->data[3];

		return Math<real>::odSqrt(xx + yy + zz + ww);
#endif
	}
	template<typename real>
	inline void OQuat<real>::rollPitchYaw(real* rpy)
	{

#if defined(INTRINSICS)
		tEulerfQuat<real>(this->data, rpy);
#else
		real sinr_cosp = (real)2.0 * ((this)[3] * (*this)[0] + (*this)[1] * (*this)[2]);
		real cosr_cosp = (real)1.0 - (real)2.0 * ((*this)[0] * (*this)[0] + (*this)[1] * (*this)[1]);
		rpy[0] = Math<real>::odAtan2(sinr_cosp, cosr_cosp);

		real sinp = (real)2.0 * ((this)[3] * (*this)[1] - (*this)[2] * (*this)[0]);
		
		rpy[1] = Math<real>::odAsin(sinp);

		real siny_cosp = (real)2.0 * ((this)[3] * (this)[2] + (this)[0] * (this)[1]);
		real cosy_cosp = (real)1.0 - (real)2.0 * ((this)[1] * (this)[1] + (this)[2] * (this)[2]);
		rpy[2] = Math<real>::odAtan2(siny_cosp, cosy_cosp);
#endif
	}
	template<typename real>
	inline void OQuat<real>::axisRotation(Vector<3, real>& axis, real& rotation)
	{
#if defined(INTRINSICS)
		taxisfQuat<real>(this->data, axis.data, &rotation);
#else
		real qq = this->data[3] * this->data[3];
		if (qq < (real)1.0) {
			rotation = (real)2.0 * Math<real>::odAcos(this->data[3]);
			real sqq = (real)1.0 / Math<real>::odSqrt((real)1.0 - qq);
			axis[0] = this->data[0] * sqq;
			axis[1] = this->data[1] * sqq;
			axis[2] = this->data[2] * sqq;

	}
		else {
			rotation = (real)0.0;
			axis[0] = (real)1.0;
			axis[1] = (real)0.0;
			axis[2] = (real)0.0;

		}

#endif

	}
	template<typename real>
	inline void OQuat<real>::normalize()
	{
#if defined(INTRINSICS)
		normalize4<real>(this->data);
#else
		real lngth2 = this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2] + this->data[3] * this->data[3];
		real invSqr = Math<real>::odSqrt(lngth2);
		this->data[0] *= invSqr;
		this->data[1] *= invSqr;
		this->data[2] *= invSqr;
		this->data[3] *= invSqr;
#endif
	}
	template<typename real>
	inline OQuat<real> OQuat<real>::normal()
	{
		OQuat<real> copy(*this);
#if defined(INTRINSICS)

		normalize4<real>(copy.data);
#else
		real lngth2 = this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2] + this->data[3] * this->data[3];
		real invSqr = Math<real>::odSqrt(lngth2);
		copy.data[0] *= invSqr;
		copy.data[1] *= invSqr;
		copy.data[2] *= invSqr;
		copy.data[3] *= invSqr;
#endif

		return copy;
	}

	template<typename real>
	inline OQuat<real>& OdinMath::OQuat<real>::operator=(const OQuat<real>& q)
	{
		if (this != &q) {
#if defined(INTRINSICS)
			store4<real>(this->data, q.data);
#else
			(*this)[0] = q[0];
			(*this)[1] = q[1];
			(*this)[2] = q[2];
			(*this)[3] = q[3];
#endif
			
		}
		return *this;
	}
	template<typename real>
	inline OQuat<real> OQuat<real>::operator+(OQuat<real>& q)
	{
		OQuat<real> o;
#if defined(INTRINSICS)
		
		add4<real>(this->data, q.data, o.data);
#else
		o[0] = this->data[0] + q.data[0];
		o[1] = this->data[1] + q.data[1];
		o[2] = this->data[2] + q.data[2];
		o[3] = this->data[3] + q.data[3];

#endif
		return o;
	}
}
