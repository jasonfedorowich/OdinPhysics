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

		OQuat() : OQuat((real)0.0, (real)0.0, (real)0.0, (real)1.0) {};
		~OQuat() {};

		void toRotation(OMatrix4<real>& m);
		void toRotation(OMatrix3<real>& m);

		void rollPitchYaw(real* rpy);
		void axisRotation(Vector<3, real>& axis, real& rotation);
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
		/*axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;*/
#endif
	}
	template<typename real>
	inline OQuat<real>::OQuat(OMatrix3<real>& m)
	{
#if defined(INTRINSICS)
		tquatfRotMat<real, 3>(m.m, this->data);
#else
		/*axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;*/
#endif
	}
	template<typename real>
	inline void OQuat<real>::toRotation(OMatrix4<real>& m)
	{
#if defined(INTRINSICS)
		trotMatfQuat<real, 4>(this->data, m.m);
#else
		/*axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;*/
#endif
	}
	template<typename real>
	inline void OQuat<real>::rollPitchYaw(real* rpy)
	{

#if defined(INTRINSICS)
		tEulerfQuat<real>(this->data, rpy);
#else
		/*axis.normalize();
		angle /= (real)2.0;
		real si = Math<real>::odSin(angle);
		this->data[0] = Math<real>::odCos(angle);
		this->data[1] = axis[0] * si;
		this->data[2] = axis[1] * si;
		this->data[3] = axis[2] * si;*/
#endif
	}
}
