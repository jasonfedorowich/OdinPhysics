#include "OdinCollision.h"

namespace OdinCollision {
	void OBB3::getPoints(ODVector3 pts[8])
	{
		ODMatrix3 m;
		this->orientation.toRotation(m);
		ODVector3 ex = extents * m;

		for (int i = 0; i < 8; i++) {
			OdinMath::OVector3<rl> factor = OdinMath::factors<rl>[i];
			pts[i] = center + ex % factor;
		}

	}
	void OBB3::getPointsBodySpace(ODVector3 pts[8])
	{
		for (int i = 0; i < 8; i++) {
			OdinMath::OVector3<rl> factor = OdinMath::factors<rl>[i];
			pts[i] = center + extents % factor;
		}


	}
	void OBB3::make(std::vector<ODVector3>& points, OBB3& obb)
	{
		ODMatrix3 mat;
		ODVector3 mean;
		OdinMath::covariance3<rl>(points, mat, mean);
		//todo this eigen computation needs to be improved for symmetric matrices
		OdinMath::QREigen3 eig(mat, OdinMath::EigenMode::QR);

		
		ODVector3 maxi = points[0] - mean;
		ODVector3 mini = maxi;
		ODMatrix3 vectors = eig.getEigenVectors();
		for (int i = 1; i < points.size(); i++) {

			ODVector3 diff = points[i] - mean;

			diff *= vectors;
			
			OdinMath::max<rl>(diff, maxi, maxi);
			OdinMath::min<rl>(diff, mini, mini);

		}

		rl f = (rl)0.5;
		obb.center = mean;
		obb.center += (maxi + mini);
		obb.center *= f;

		obb.extents = maxi - mini;
		obb.extents *= f;
		
		obb.orientation = ODQuat(eig.getEigenVectors());
		
	}
	
	void OBB3::make(OBB3& a, OBB3& b, OBB3& out)
	{
		ODVector3 pts[16];
		a.getPoints(pts);
		b.getPoints(pts + 8);
		std::vector<ODVector3> ptsv(16);
		for (int i = 0; i < 16; i++) {
			ptsv[i] = pts[i];
		}
		make(ptsv, out);
	}

	OBB3::OBB3(std::vector<ODVector3>& points)
	{
		make(points, *this);
	}
	OBB3::OBB3(std::vector<ODVector3>&& points)
	{
		make(points, *this);
	}
	OBB3& OBB3::operator=(const OBB3& obb)
	{
		if (this != &obb) {
			this->center = obb.center;
			this->extents = obb.extents;
			this->orientation = obb.orientation;
		}
		return *this;
	}
	bool OBB3::intersects(OBB3& other)
	{
		ODMatrix3 m1, m2;

		this->orientation.toRotation(m1);
		other.orientation.toRotation(m2);

		ODMatrix3 R = m1.multTrans(m2);

		ODVector3 T = other.center - center;
		R.absM();

		ODMatrix3 e(OdinMath::Math<rl>::eps);
		R += e;

		//T * A
		ODVector3 TT1 = T * m1;
		OdinMath::vAbs(TT1);

		ODVector3 r1 = R.getRow(0);
		rl a = r1 * other.extents + extents[0];
		
		OdinMath::vAbs(extents);
		OdinMath::vAbs(other.extents);


		if (TT1[0] > a)
			return false;

		ODVector3 r2 = R.getRow(1);
		a = r2 * other.extents + extents[1];
		if (TT1[1] > a)
			return false;


		ODVector3 r3 = R.getRow(2);
		a = r3 * other.extents + extents[2];
		if (TT1[2] > a)
			return false;

		//T * B
		ODVector3 TT2 = T * m2;
		OdinMath::vAbs(TT2);

		a = r1 * extents + other.extents[0];

		if (TT2[0] > a)
			return false;

		a = r2 * extents + other.extents[1];
		if (TT2[1] > a)
			return false;

		a = r3 * extents + other.extents[2];
		if (TT2[2] > a)
			return false;

		//L = Ax X Bx
		OdinMath::Math<rl>::odAbs(TT1[2] * R(1, 0) - TT1[1] * R(2, 0)) > (extents[1] * R(2, 0) + extents[2] * R(1, 0) + other.extents[1] * R(0, 2) + other.extents[2] * R(0, 1));

		// L = Ax X By
		OdinMath::Math<rl>::odAbs(TT1[2] * R(1, 1) - TT1[1] * R(2, 1)) > (extents[1] * R(2, 1) + extents[2] * R(1, 1) + other.extents[0] * R(0, 2) + other.extents[2] * R(1, 1));


		// L = Ax X Bz
		OdinMath::Math<rl>::odAbs(TT1[2] * R(1, 2) - TT1[1] * R(2, 2)) > (extents[1] * R(2, 2) + extents[2] * R(1, 2) + other.extents[0] * R(0, 1) + other.extents[1] * R(0, 0));

		// L = Ay X Bx
		OdinMath::Math<rl>::odAbs(TT1[0] * R(2, 0) - TT1[2] * R(0, 0)) > (extents[0] * R(2, 0) + extents[2] * R(0, 0) + other.extents[1] * R(1, 2) + other.extents[2] * R(1, 1));

		// L = Ay X By
		OdinMath::Math<rl>::odAbs(TT1[0] * R(2, 1) - TT1[2] * R(0, 1)) > (extents[0] * R(2, 1) + extents[2] * R(0, 1) + other.extents[0] * R(1, 2) + other.extents[2] * R(1, 0));

		// L = Ay X Bz
		OdinMath::Math<rl>::odAbs(TT1[0] * R(2, 2) - TT1[2] * R(0, 2)) > (extents[0] * R(2, 2) + extents[2] * R(0, 2) + other.extents[0] * R(1, 1) + other.extents[1] * R(1, 0));

		// L = Az X Bx
		OdinMath::Math<rl>::odAbs(TT1[1] * R(0, 0) - TT1[0] * R(1, 0)) > (extents[0] * R(1, 0) + extents[1] * R(0, 0) + other.extents[1] * R(2, 2) + other.extents[2] * R(2, 1));

		// L = Az X By
		OdinMath::Math<rl>::odAbs(TT1[1] * R(0, 1) - TT1[0] * R(1, 1)) > (extents[0] * R(1, 1) + extents[1] * R(0, 1) + other.extents[0] * R(2, 2) + other.extents[2] * R(2, 0));

		// L = Az X Bz
		OdinMath::Math<rl>::odAbs(TT1[1] * R(0, 2) - TT1[0] * R(1, 2)) > (extents[0] * R(1, 2) + extents[1] * R(0, 2) + other.extents[0] * R(2, 1) + other.extents[1] * R(2, 0));

		return true;
	}
	bool OBB3::contains(OBB3& other)
	{
		ODVector3 points[8];
		other.getPoints(points);
		ODMatrix3 m;
		orientation.toRotation(m);


		for (int i = 0; i < 8; i++) {

			points[i] -= center;
			points[i] = m * points[i];
			if (!contains(points[i], m))
				return false;

		}
		return true;


	}
	bool OBB3::disjoint(OBB3& other)
	{
		return !intersects(other);
	}
	bool OBB3::contains(ODVector3& pt)
	{
		ODMatrix3 m;
		orientation.toRotation(m);
		return contains(pt, m);

	}
	bool OBB3::contains(ODVector3&& pt)
	{
		ODMatrix3 m;
		orientation.toRotation(m);
		return contains(pt, m);
	}
	bool OBB3::contains(ODVector3& pt, ODMatrix3& rot)
	{
		ODVector3 tmp = rot * pt;

		ODVector3 gt = tmp >= extents;
		ODVector3 f = OdinMath::factors<rl>[0];
		ODVector3 lt = extents % f >= tmp;
		f = lt | gt;
		return f == ODVector3::zeros();
	}
	bool OBB3::contains(ODVector3&& pt, ODMatrix3& rot)
	{
		return contains(pt, rot);
	}
	OBB3 OBB3::merge(OBB3& other)
	{
		if (contains(other))
			return *this;
		if (other.contains(*this))
			return other;

		OBB3 res;
		make(*this, other, res);
		return res;
	}
	void OBB3::makeUnion(OBB3& other)
	{
		if (contains(other))
			return;
		if (!other.contains(*this))
			return;

		make(*this, other, *this);
	}
	OBB3 OBB3::merge(ODVector3& p)
	{
		if (contains(p))
			return *this;

		ODVector3 pts[8];
		getPoints(pts);
		std::vector<ODVector3> vpts(9);
		for (int i = 0; i < 8; i++) {
			vpts[i] = pts[i];
		}
		vpts[8] = p;
		OBB3 r;
		make(vpts, r);
		return r;
	}
	void OBB3::makeUnion(ODVector3& p)
	{
		if (contains(p))
			return;
		ODVector3 pts[8];
		getPoints(pts);
		std::vector<ODVector3> vpts(9);
		for (int i = 0; i < 8; i++) {
			vpts[i] = pts[i];
		}
		vpts[8] = p;
		
		make(vpts, *this);
		
	}
	OBB3 OBB3::merge(ODVector3&& p)
	{
		return merge(p);
	}
	void OBB3::makeUnion(ODVector3&& p)
	{
		makeUnion(p);
	}
}