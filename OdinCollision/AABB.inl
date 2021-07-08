#pragma once
#include "AABB.h"
template<int N>
inline AABB<N>::AABB(std::vector<ODVector>& points)
{
	using namespace OdinMath;

	for (int i = 0; i < N; i++) {
		this->maxi[i] = Math<rl>::REAL_MIN;
		this->mini[i] = Math<rl>::REAL_MAX;

	}

	for (int i = 0; i < points.size(); i++) {

		for (int j = 0; j < N; j++) {
			maxi[j] = Math<rl>::odMax(maxi[j], points[i][j]);
			mini[j] = Math<rl>::odMin(mini[j], points[i][j]);
		}
	}
}
template<int N>
inline AABB<N>::AABB(std::vector<ODVector>&& points)
{
	using namespace OdinMath;

	for (int i = 0; i < N; i++) {
		this->maxi[i] = Math<rl>::REAL_MIN;
		this->mini[i] = Math<rl>::REAL_MAX;

	}

	for (int i = 0; i < points.size(); i++) {

		for (int j = 0; j < N; j++) {
			maxi[j] = Math<rl>::odMax(maxi[j], points[i][j]);
			mini[j] = Math<rl>::odMin(mini[j], points[i][j]);
		}
	}
}
template<int N>
inline bool AABB<N>::overlaps(AABB& other)
{
	for (int i = 0; i < N; i++) {
		if (mini[i] > other.maxi[i] || other.mini[i] > maxi[i])
			return false;
	}
	return true;
}

template<int N>
inline AABB<N> AABB<N>::merge(AABB& other)
{
	using namespace OdinMath;
	AABB<N> aabb;

	for (int i = 0; i < N; i++) {
		aabb.maxi[i] = Math<rl>::max(this->maxi[i], other.maxi[i]);
		aabb.mini[i] = Math<rl>::min(this->mini[i], other.mini[i]);

	}
	return aabb;

}

template<int N>
inline void AABB<N>::makeUnion(AABB& other)
{
	using namespace OdinMath;

	for (int i = 0; i < N; i++) {
		this->maxi[i] = Math<rl>::max(this->maxi[i], other.maxi[i]);
		this->mini[i] = Math<rl>::min(this->mini[i], other.mini[i]);

	}

}

template<int N>
inline AABB<N>& AABB<N>::operator=(const AABB<N>& aabb)
{
	if (this != &aabb) {
		this->maxi = aabb.maxi;
		this->mini = aabb.mini;

	}
	return *this;
}

