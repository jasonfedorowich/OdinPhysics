#pragma once
#include "OdinCollision.h"

namespace OdinCollision{

	AABB3 AABB3::make(ODVector3& mini, ODVector3& maxi)
	{
		AABB3 aabb;
		aabb.center = maxi + mini;
		aabb.center *= (rl)0.5;
		aabb.extents = maxi - aabb.center;
		return aabb;
	}

	AABB3& AABB3::operator=(const AABB3& aabb)
	{
		if (this != &aabb) {
			this->center = aabb.center;
			this->extents = aabb.extents;
		}
		return *this;
	}

	bool AABB3::intersects(AABB3& other)
	{
		ODVector3 maxi = maximum();
		ODVector3 mini = minimum();
		ODVector3 omaxi = other.maximum();
		ODVector3 omini = other.minimum();

		ODVector3 gt = mini > omaxi;
		ODVector3 ogt = omini > maxi;
		ODVector3 zeroes = ODVector3::zeros();
		
		return !(gt != zeroes || ogt != zeroes);

	}

	bool AABB3::contains(AABB3& other)
	{
		ODVector3 maxi = maximum();
		ODVector3 mini = minimum();
		ODVector3 omaxi = other.maximum();
		ODVector3 omini = other.minimum();

		ODVector3 gt = mini > omaxi;
		ODVector3 ogt = omini > maxi;
		ODVector3 zeroes = ODVector3::zeros();

		bool inter = (gt != zeroes || ogt != zeroes);
		if (inter) {
			return false;
		}

		gt = omini >= mini;
		ogt = maxi >= omaxi;
		ODVector3 ones = ODVector3::ones();
		return ones == gt && ones == ogt;


	}

	bool AABB3::disjoint(AABB3& other)
	{
		return !intersects(other);
	}
	
	AABB3::AABB3(std::vector<ODVector3>& points)
	{
		using namespace OdinMath;
		ODVector3 maxi(Math<rl>::REAL_MIN, Math<rl>::REAL_MIN, Math<rl>::REAL_MIN);
		ODVector3 mini(Math<rl>::REAL_MAX, Math<rl>::REAL_MAX, Math<rl>::REAL_MAX);



		for (unsigned i = 0; i < points.size(); i++) {
			maxi[0] = Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = Math<rl>::odMin(mini[0], points[i][0]);
			maxi[1] = Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = Math<rl>::odMin(mini[1], points[i][1]);
			maxi[2] = Math<rl>::odMax(maxi[2], points[i][2]);
			mini[2] = Math<rl>::odMin(mini[2], points[i][2]);

			
		}

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;
	}

	AABB3::AABB3(std::vector<ODVector3>&& points)
	{
		using namespace OdinMath;
		ODVector3 maxi(Math<rl>::REAL_MIN, Math<rl>::REAL_MIN, Math<rl>::REAL_MIN);
		ODVector3 mini(Math<rl>::REAL_MAX, Math<rl>::REAL_MAX, Math<rl>::REAL_MAX);



		for (unsigned i = 0; i < points.size(); i++) {
			maxi[0] = Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = Math<rl>::odMin(mini[0], points[i][0]);
			maxi[1] = Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = Math<rl>::odMin(mini[1], points[i][1]);
			maxi[2] = Math<rl>::odMax(maxi[2], points[i][2]);
			mini[2] = Math<rl>::odMin(mini[2], points[i][2]);


		}

		center = maxi + mini;
		center /= (rl)2.0;
		extents = maxi - center;
	}

	
	AABB3 AABB3::merge(AABB3& other)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();
		ODVector3 omaxi = other.maximum();
		ODVector3 omini = other.minimum();

		
		maxi[0] = Math<rl>::odMax(maxi[0], omaxi[0]);
		mini[0] = Math<rl>::odMin(mini[0], omini[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], omaxi[1]);
		mini[1] = Math<rl>::odMin(mini[1], omini[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], omaxi[2]);
		mini[2] = Math<rl>::odMin(mini[2], omini[2]);

		return AABB3::make(mini, maxi);

	}

	
	inline void AABB3::makeUnion(AABB3& other)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();
		ODVector3 omaxi = other.maximum();
		ODVector3 omini = other.minimum();


		maxi[0] = Math<rl>::odMax(maxi[0], omaxi[0]);
		mini[0] = Math<rl>::odMin(mini[0], omini[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], omaxi[1]);
		mini[1] = Math<rl>::odMin(mini[1], omini[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], omaxi[2]);
		mini[2] = Math<rl>::odMin(mini[2], omini[2]);

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;


	}

	AABB3 AABB3::merge(ODVector3& p)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], p[1]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], p[2]);
		mini[2] = Math<rl>::odMin(mini[2], p[2]);
		return AABB3::make(mini, maxi);

	}

	void AABB3::makeUnion(ODVector3& p)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], p[1]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], p[2]);
		mini[2] = Math<rl>::odMin(mini[2], p[2]);
		
		center = maxi + mini;
		center /= (rl)2.0;
		extents = maxi - center;

	}

	AABB3 AABB3::merge(ODVector3&& p)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], p[1]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], p[2]);
		mini[2] = Math<rl>::odMin(mini[2], p[2]);

		return AABB3::make(mini, maxi);
	}

	void AABB3::makeUnion(ODVector3&& p)
	{
		using namespace OdinMath;
		ODVector3 maxi = this->maximum();
		ODVector3 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		maxi[1] = Math<rl>::odMax(maxi[1], p[1]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);
		maxi[2] = Math<rl>::odMax(maxi[2], p[2]);
		mini[2] = Math<rl>::odMin(mini[2], p[2]);

		center = maxi + mini;
		center /= (rl)2.0;
		extents = maxi - center;
	}

	
	ODVector3 AABB3::minimum()
	{
		return center - extents;
	}

	ODVector3 AABB3::maximum()
	{
		return center + extents;
	}





}

