#include "OdinCollision.h"
namespace OdinCollision {



	Seg3::Seg3(ODVector3& p1, ODVector3& q1, bool direction)
	{
		if (!direction) {
			start = p1;
			end = q1;
			
		}
		else {
			start = p1;
			end = start + q1;
		}
	}

	Seg3::Seg3(ODVector3&& p1, ODVector3&& q1, bool direction)
	{
		if (!direction) {
			start = p1;
			end = q1;

		}
		else {
			start = p1;
			end = start + q1;
		}
	}

	Seg3::Seg3(std::vector<ODVector3>& points)
	{
		using namespace OdinMath;

		start = points[0];
		end = points[0];

		for (unsigned i = 0; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);
			end[2] = Math<rl>::odMax(end[2], points[i][2]);
			start[2] = Math<rl>::odMin(start[2], points[i][2]);


		}
	}

	Seg3::Seg3(std::vector<ODVector3>&& points)
	{
		using namespace OdinMath;

		start = points[0];
		end = points[0];

		for (unsigned i = 1; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);
			end[2] = Math<rl>::odMax(end[2], points[i][2]);
			start[2] = Math<rl>::odMin(start[2], points[i][2]);


		}
	}

	Seg3& Seg3::operator=(const Seg3& s)
	{
		if (this != &s) {
			start = s.start;
			end = s.end;
		}
		return *this;

	}

	bool Seg3::intersects(Seg3& other)
	{
		
		ODVector3 p1;
		ODVector3 p2;
		rl s;
		rl t;
		rl dist = closestPoints(other, s, t, p1, p2);
		if (dist == (0.f) || dist <= OdinMath::Math<rl>::eps) {
			return true;
		}
		return false;


	}

	bool Seg3::contains(Seg3& other)
	{
		return intersects(other);
	}

	bool Seg3::disjoint(Seg3& other)
	{
		return !intersects(other);
	}

	Seg3 Seg3::merge(Seg3& other)
	{
		Seg3 seg;
		ODVector3 mini = start > other.start;
		ODVector3 maxi = end > other.end;
		
		ODVector3 zeros = ODVector3::zeros();
		if (zeros == mini) {
			seg.start = start;
		}
		else {
			seg.start = other.start;
		}

		if (zeros == maxi) {
			seg.end = other.end;
		}
		else {
			seg.end = end;
		}
		
		return seg;



	}

	void Seg3::makeUnion(Seg3& other)
	{

		ODVector3 mini = start > other.start;
		ODVector3 maxi = end > other.end;

		ODVector3 zeros = ODVector3::zeros();
		if (zeros != mini) {
			start = other.start;
		}
		

		if (zeros == maxi) {
			end = other.end;
		}
		

	}

	Seg3 Seg3::merge(ODVector3& p)
	{
		Seg3 seg;
		ODVector3 mini = start > p;
		ODVector3 maxi = end > p;

		ODVector3 zeros = ODVector3::zeros();

		if (zeros == mini) {
			seg.start = start;
		}
		else
			seg.start = p;

		if (zeros == maxi) {
			seg.end = p;
		}
		else
			seg.end = end;

		return seg;

	}

	void Seg3::makeUnion(ODVector3& p)
	{
		ODVector3 mini = start > p;
		ODVector3 maxi = end > p;

		ODVector3 zeros = ODVector3::zeros();

		
		if(zeros != mini)
			start = p;

		if (zeros == maxi) {
			end = p;
		}
		
	}

	Seg3 Seg3::merge(ODVector3&& p)
	{
		Seg3 seg;
		ODVector3 mini = start > p;
		ODVector3 maxi = end > p;

		ODVector3 zeros = ODVector3::zeros();

		if (zeros == mini) {
			seg.start = start;
		}
		else
			seg.start = p;

		if (zeros == maxi) {
			seg.end = p;
		}
		else
			seg.end = end;

		return seg;
	}

	void Seg3::makeUnion(ODVector3&& p)
	{
		ODVector3 mini = start > p;
		ODVector3 maxi = end > p;

		ODVector3 zeros = ODVector3::zeros();


		if (zeros != mini)
			start = p;

		if (zeros == maxi) {
			end = p;
		}
	}

	rl Seg3::closestPoints(Seg3& other, rl& s, rl& t, ODVector3& p1, ODVector3& p2)
	{
		using namespace OdinMath;
		ODVector3 d1 = direction();
		ODVector3 d2 = other.direction();
		ODVector3 r = start - other.start;

		rl a = d1.dot(d1);
		rl e = d2.dot(d2);
		rl f = d2.dot(r);

		//segements are both points ie. start and end are the same
		if (a <= Math<rl>::eps && e <= Math<rl>::eps) {
			s = (rl)0.0;
			t = (rl)0.0;
			p1 = start;
			p2 = other.start;
			ODVector3 diff = p1 - p2;
			return diff.dot(diff);
		}
		//first segment is a point
		if (a <= Math<rl>::eps) {

			s = (rl)0.0;
			t = Math<rl>::odClamp(f / e, (rl)0.f, (rl)1.f);

		}
		
		else {
			
			rl c = d1.dot(r);
			//second segment is point
			if (e <= Math<rl>::eps) {

				t = (rl)0.f;
				s = Math<rl>::odClamp(-c / a, (rl)0.f, (rl)1.f);
			}
			else {


				//no segs are points

				rl b = d1.dot(d2);
				rl den = a * e - b * b;

				if (den != (rl)0.0) {
					s = Math<rl>::odClamp((b * f - c * e) / den, (rl)0.f, (rl)1.f);
				}
				else
					s = (rl)0.f;

				t = (b * s + f) / e;

				//clamp to t = [0, 1]
				if (t < (rl)0.f) {
					t = (rl)0.f;
					s = Math<rl>::odClamp(-c / a, (rl)0.f, (rl)1.f);
				}
				else if (t > (rl)1.f) {
					t = (rl)1.f;
					s = Math<rl>::odClamp((b - c) / a, (rl)0.f, (rl)1.f);
				}

			}

		}
		p1 = start + d1 * s;
		p2 = other.start + d2 * t;
		ODVector3 diff = p1 - p2;
		return diff.dot(diff);


	}

}

