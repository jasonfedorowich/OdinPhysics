#pragma once
#include "OdinMath.h"
namespace OdinMath {

	template<typename real, int N>
	real dot(Vector<N, real>& v1, Vector<N, real>& v2) {
		real result = (real)0.0;
		for (int i = 0; i < N; i++) {
			result += (v1[i] * v2[i]);

		}
		return result;

	}

	template<typename real>
	void cross(Vector<3, real>& v1, Vector<3, real>& v2, Vector<3, real>& cp) {
		cp[0] = v1[1] * v2[2] - v1[2] * v2[1];
		cp[1] = v1[0] * v2[2] - v1[2] * v2[0];
		cp[2] = v1[0] * v2[1] - v1[1] * v2[0];

	}

	template<typename real>
	void cross(Vector<4, real>& v1, Vector<4, real>& v2, Vector<4, real>& cp) {
		cp[0] = v1[1] * v2[2] - v1[2] * v2[1];
		cp[1] = v1[0] * v2[2] - v1[2] * v2[0];
		cp[2] = v1[0] * v2[1] - v1[1] * v2[0];
		cp[3] = (real)0.0;

	}


}
