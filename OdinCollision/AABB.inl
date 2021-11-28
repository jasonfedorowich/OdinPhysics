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

	for (unsigned i = 0; i < points.size(); i++) {

		for (unsigned j = 0; j < N; j++) {
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

	for (unsigned i = 0; i < points.size(); i++) {

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
		aabb.maxi[i] = Math<rl>::odMax(this->maxi[i], other.maxi[i]);
		aabb.mini[i] = Math<rl>::odMin(this->mini[i], other.mini[i]);

	}
	return aabb;

}

template<int N>
inline void AABB<N>::makeUnion(AABB& other)
{
	using namespace OdinMath;

	for (int i = 0; i < N; i++) {
		this->maxi[i] = Math<rl>::odMax(this->maxi[i], other.maxi[i]);
		this->mini[i] = Math<rl>::odMin(this->mini[i], other.mini[i]);

	}

}

template<int N>
inline AABB<N> OdinCollision::AABB<N>::merge(ODVector& p)
{
	using namespace OdinMath;

	ODVector mi = this->mini;
	ODVector ma = this->maxi;
	for (int i = 0; i < 3; i++) {
		ma = Math<rl>::odMin(ma, p[i]);
		mi = Math<rl>::odMax(mi, p[i]);

	}

	return AABB<N>(mi, ma);

}

template<int N>
inline void OdinCollision::AABB<N>::makeUnion(ODVector& p)
{
	using namespace OdinMath;
	for (int i = 0; i < 3; i++) {
		maxi[i] = Math<rl>::odMax(this->maxi[i], p[i]);
		mini[i] = Math<rl>::odMin(this->mini[i], p[i]);
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

