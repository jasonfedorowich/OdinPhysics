#pragma once
#include "OdinCollision.h"

namespace OdinCollision {
	AABB2 AABB2::make(ODVector2& mini, ODVector2& maxi)
	{
		AABB2 aabb;
		aabb.center = maxi + mini;
		aabb.center *= (rl)0.5;
		aabb.extents = maxi - aabb.center;
		return aabb;
	}

	AABB2::AABB2(std::vector<ODVector2>& points)
	{
		using namespace OdinMath;
		ODVector2 maxi(Math<rl>::REAL_MIN, Math<rl>::REAL_MIN);
		ODVector2 mini(Math<rl>::REAL_MAX, Math<rl>::REAL_MAX);



		for (unsigned i = 0; i < points.size(); i++) {
			maxi[0] = Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = Math<rl>::odMin(mini[0], points[i][0]);
			maxi[1] = Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = Math<rl>::odMin(mini[1], points[i][1]);
		}

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;
	}
	AABB2::AABB2(std::vector<ODVector2>&& points)
	{
		using namespace OdinMath;
		ODVector2 maxi(Math<rl>::REAL_MIN, Math<rl>::REAL_MIN);
		ODVector2 mini(Math<rl>::REAL_MAX, Math<rl>::REAL_MAX);



		for (unsigned i = 0; i < points.size(); i++) {
			maxi[0] = Math<rl>::odMax(maxi[0], points[i][0]);
			mini[0] = Math<rl>::odMin(mini[0], points[i][0]);
			maxi[1] = Math<rl>::odMax(maxi[1], points[i][1]);
			mini[1] = Math<rl>::odMin(mini[1], points[i][1]);
		}

		center = maxi + mini;
		center /= (rl)2.0;
		extents = maxi - center;
	}
	AABB2& AABB2::operator=(const AABB2& aabb)
	{
		if (this != &aabb) {
			this->extents = aabb.extents;
			this->center = aabb.center;

		}
		return *this;
	}
	bool AABB2::intersects(AABB2& other)
	{
		ODVector2 maxia = this->maximum();
		ODVector2 minia = this->minimum();

		ODVector2 maxib = this->maximum();
		ODVector2 minib = this->minimum();

		ODVector2 gt = minia > maxib;
		ODVector2 ogt = minib > maxia;
		ODVector2 zeroes = ODVector2::zeros();

		return !(gt != zeroes || ogt != zeroes);


	}
	bool AABB2::contains(AABB2& other)
	{
		ODVector2 maxi = maximum();
		ODVector2 mini = minimum();
		ODVector2 omaxi = other.maximum();
		ODVector2 omini = other.minimum();

		ODVector2 gt = mini > omaxi;
		ODVector2 ogt = omini > maxi;
		ODVector2 zeroes = ODVector2::zeros();

		bool inter = (gt != zeroes || ogt != zeroes);
		if (inter) {
			return false;
		}

		gt = omini >= mini;
		ogt = maxi >= omaxi;
		ODVector2 ones = ODVector2::ones();
		return ones == gt && ones == ogt;

	}
	bool AABB2::disjoint(AABB2& other)
	{
		return !intersects(other);
	}
	AABB2 AABB2::merge(AABB2& other)
	{
		using namespace OdinMath;
		ODVector2 omaxi = other.maximum();
		ODVector2 omini = other.minimum();

		ODVector2 maxi = this->maximum();
		ODVector2 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], omaxi[0]);
		maxi[1] = Math<rl>::odMin(maxi[1], omaxi[1]);

		mini[0] = Math<rl>::odMax(mini[0], omini[0]);
		mini[1] = Math<rl>::odMax(mini[1], omini[1]);

		return make(mini, maxi);


	}
	void AABB2::makeUnion(AABB2& other)
	{
		using namespace OdinMath;
		ODVector2 omaxi = other.maximum();
		ODVector2 omini = other.minimum();

		ODVector2 maxi = this->maximum();
		ODVector2 mini = this->minimum();

		maxi[0] = Math<rl>::odMax(maxi[0], omaxi[0]);
		maxi[1] = Math<rl>::odMin(maxi[1], omaxi[1]);

		mini[0] = Math<rl>::odMax(mini[0], omini[0]);
		mini[1] = Math<rl>::odMax(mini[1], omini[1]);

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;
	}
	AABB2 AABB2::merge(ODVector2& p)
	{
		using namespace OdinMath;
		ODVector2 maxi = maximum();
		ODVector2 mini = minimum();
		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		maxi[1] = Math<rl>::odMin(mini[1], p[1]);

		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);

		return make(mini, maxi);
	}
	void AABB2::makeUnion(ODVector2& p)
	{
		using namespace OdinMath;
		ODVector2 maxi = maximum();
		ODVector2 mini = minimum();
		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		maxi[1] = Math<rl>::odMin(mini[1], p[1]);

		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;

	}
	AABB2 AABB2::merge(ODVector2&& p)
	{
		using namespace OdinMath;
		ODVector2 maxi = maximum();
		ODVector2 mini = minimum();
		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		maxi[1] = Math<rl>::odMin(mini[1], p[1]);

		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);

		return make(mini, maxi);
	}
	void AABB2::makeUnion(ODVector2&& p)
	{
		using namespace OdinMath;
		ODVector2 maxi = maximum();
		ODVector2 mini = minimum();
		maxi[0] = Math<rl>::odMax(maxi[0], p[0]);
		maxi[1] = Math<rl>::odMin(mini[1], p[1]);

		mini[0] = Math<rl>::odMin(mini[0], p[0]);
		mini[1] = Math<rl>::odMin(mini[1], p[1]);

		center = maxi + mini;
		center *= (rl)0.5;
		extents = maxi - center;
	}
	ODVector2 AABB2::minimum()
	{
		return extents - center;
	}
	ODVector2 AABB2::maximum()
	{
		return center + extents;
	}

}