#include "OdinCollision.h"
namespace OdinCollision {
	Seg2::Seg2(ODVector2& a1, ODVector2& a2, bool direction)
	{
		if (direction) {
			start = a1;
			end = a1 + a2;

		}
		else {

			start = a1;
			end = a2;
		}
	}
	Seg2::Seg2(ODVector2&& a1, ODVector2&& a2, bool direction)
	{
		if (direction) {
			start = a1;
			end = a1 + a2;

		}
		else {

			start = a1;
			end = a2;
		}
	}
	Seg2::Seg2(std::vector<ODVector2>& points)
	{
		using namespace OdinMath;
		start = points[0];
		end = points[0];

		for (unsigned i = 0; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);
			


		}
	}
	Seg2::Seg2(std::vector<ODVector2>&& points)
	{
		using namespace OdinMath;
		start = points[0];
		end = points[0];

		for (unsigned i = 0; i < points.size(); i++) {
			end[0] = Math<rl>::odMax(end[0], points[i][0]);
			start[0] = Math<rl>::odMin(start[0], points[i][0]);
			end[1] = Math<rl>::odMax(end[1], points[i][1]);
			start[1] = Math<rl>::odMin(start[1], points[i][1]);



		}
	}
	Seg2& Seg2::operator=(const Seg2& s)
	{
		if (this != &s) {

			start = s.start;
			end = s.end;
		}
		return *this;
	}
	bool Seg2::intersects(Seg2& other)
	{
		ODVector2 pt;
		rl mua, mub;
		if (!intersectionPoint(other, mua, mub, pt))
			return false;

		if (mua < 0 || mua > 1 || mub < 0 || mub > 1)
			return false;

		return true;



	}

	bool Seg2::contains(Seg2& other)
	{
		return intersects(other);
	}

	bool Seg2::disjoint(Seg2& other)
	{
		return !intersects(other);
	}

	Seg2 Seg2::merge(Seg2& other)
	{
		Seg2 seg;
		ODVector2 mini = start > other.start;
		ODVector2 maxi = end > other.end;

		ODVector2 zeros = ODVector2::zeros();
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

	void Seg2::makeUnion(Seg2& other)
	{
		ODVector2 mini = start > other.start;
		ODVector2 maxi = end > other.end;

		ODVector2 zeros = ODVector2::zeros();
		if (zeros != mini) {
			start = other.start;
		}


		if (zeros == maxi) {
			end = other.end;
		}

	}

	Seg2 Seg2::merge(ODVector2& p)
	{
		Seg2 seg;
		ODVector2 mini = start > p;
		ODVector2 maxi = end > p;

		ODVector2 zeros = ODVector2::zeros();

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

	void Seg2::makeUnion(ODVector2& p)
	{
		ODVector2 mini = start > p;
		ODVector2 maxi = end > p;

		ODVector2 zeros = ODVector2::zeros();


		if (zeros != mini)
			start = p;

		if (zeros == maxi) {
			end = p;
		}
	}

	Seg2 Seg2::merge(ODVector2&& p)
	{
		Seg2 seg;
		ODVector2 mini = start > p;
		ODVector2 maxi = end > p;

		ODVector2 zeros = ODVector2::zeros();

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

	void Seg2::makeUnion(ODVector2&& p)
	{
		ODVector2 mini = start > p;
		ODVector2 maxi = end > p;

		ODVector2 zeros = ODVector2::zeros();


		if (zeros != mini)
			start = p;

		if (zeros == maxi) {
			end = p;
		}
	}

	
	bool Seg2::intersectionPoint(Seg2& other, rl& mua, rl& mub, ODVector2& pt)
	{
		using namespace OdinMath;
		ODVector2 d1 = this->direction();
		ODVector2 d2 = other.direction();
		ODVector2 inv = { d2[1], d2[0] };


		ODVector2 prod = d1 % inv;
		rl denom = prod[0] - prod[1];
		if (Math<rl>::odAbs(denom) <= Math<rl>::eps || denom == (rl)0.f) {
			return false;
		}
		ODVector2 diff = this->start - other.start;
		inv = { diff[1], diff[0] };
		prod = d2 % inv;

		rl numa = prod[0] - prod[1];
		mua = numa / denom;

		prod = d1 % inv;
		rl numb = prod[0] - prod[1];
		mub = numb / denom;

		pt = start + (end * mua);
		return true;
	}

	rl Seg2::xIntercept()
	{
		using namespace OdinMath;
		//use y = m * x + b where b is the y intercept
		rl m = slope();
		if (Math<rl>::odAbs(m) <= Math<rl>::eps || m == 0.f)
			return Math<rl>::REAL_MAX;

		rl b = start[1] - m * start[0];
		//plug y = 0 in
		rl x = -b / m;
		return x;
		


	}

	rl Seg2::yIntercept()
	{
		//use y = m * x + b where b is the y intercept
		rl m = slope();
		//x = 0
		rl y = start[1] - m * start[0];
		return y;
	}

}