#pragma once
#include "MassProperties.h"

template<typename real>
void OdinMath::computeProperties(std::vector<Vector4>& points, int tmax, std::vector<int>& indices, real& mass, Vector4& centerOfMass, Matrix4& inertia, bool bodyCoords)
{

	void subExpressions = [](real w0, real w1, real w2, real& f1, real& f2, real& f3, real& g0, real& g1, real& g2) {
		real temp0 = w0 + w1;
		real temp1 = w0 * w0;
		real temp2 = temp1 + w1 * temp0;

		f1 = temp0 + w2;
		f2 = temp2 + w2 * f1;
		f3 = w0 * temp1 + w1 * temp2 + w2 * f2;

		g0 = f2 + w0 * (f1 + w0);
		g1 = f2 + w1 * (f1 + w1);
		g2 = f2 + w2 * (f1 + w2);

	};

	real integral[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int i0, i1, i2;

	Vector4 v0, v1, v2;
	Vector4 e1, e2, N;

	int nIndices = indices.size();
	int nPoints = points.size();

	real fx1, fx2, fx3, gx0, gx1, gx2;
	real fy1, fy2, fy3, gy0, gy1, gy2;
	real fz1, fz2, fz3, gz0, gz1, gz2;

	real integral[10] = { (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0, (real)0.0 };
	
	for (int t = 0; t < tmax; t++) {
		
		i0 = indices[3 * t];
		i1 = indices[3 * t + 1];
		i2 = indices[3 * t + 2];

		v0 = indices[i0];
		v1 = indices[i1];
		v2 = indices[i2];

		e1 = v1 - v0;
		e2 = v2 - v0;

		N = e1.cross(e2);

		

		subExpressions(v0[0], v1[0], v2[0], fx1, fx2, fx3, gx0, gx1, gx2);
		subExpressions(v0[1], v1[1], v2[1], fy1, fy2, fy3, gy0, gy1, gy2);
		subExpressions(v0[2], v1[2], v2[2], fz1, fz2, fz3, gz0, gz1, gz2);

		integral[0] += N[0] * fx1;
		integral[1] += N[0] * fx2;
		integral[2] += N[1] * fy2;
		integral[3] += N[2] * fz2;
		integral[4] += N[0] * fx3;
		integral[5] += N[1] * fy3;
		integral[6] += N[2] * fz3;
		integral[7] += (N[0] * (v0[1] * gx0 + v1[1] * gx1 + v2[1] * gx2);
		integral[8] += (N[1] * (v0[2] * gy0 + v1[2] * gy1 + v2[2] * gy2);
		integral[9] += (N[2] * (v0[0] * gz0 + v1[0] * gz1 + v2[0] * gz2);




	}

	real oneDiv6 = ((real)1.0 / (real)6.0);
	real oneDiv24 = ((real)1.0 / (real)24.0);
	real oneDiv60 = ((real)1.0 / (real)60.0);
	real oneDiv120 = ((real)1.0 / (real)120.0);


	integral[0] *= oneDiv6;
	integral[1] *= oneDiv24;
	integral[2] *= oneDiv24;
	integral[3] *= oneDiv24;
	integral[4] *= oneDiv60;
	integral[5] *= oneDiv60;
	integral[6] *= oneDiv60;
	integral[7] *= oneDiv120;
	integral[8] *= oneDiv120;
	integral[9] *= oneDiv120;

	mass = integral[0];

	centerOfMass[0] = integral[1] / mass;
	centerOfMass[1] = integral[2] / mass;
	centerOfMass[2] = integral[3] / mass;

	inertia(0, 0) = integral[5] + integral[6];
	inertia(1, 1) = integral[4] + integral[6];
	inertia(2, 2) = integral[4] + integral[5];
	inertia(1, 0) = -integral[7];
	inertia(2, 1) = -integral[8];
	inertia(2, 0) = -integral[9];

	if (bodyCoords) {
		inertia(0, 0) -= mass * (centerOfMass[1] * centerOfMass[1] + centerOfMass[2] * centerOfMass[2]);
		inertia(1, 1) -= mass * (centerOfMass[0] * centerOfMass[0] + centerOfMass[2] * centerOfMass[2]);
		inertia(2, 2) -= mass * (centerOfMass[0] * centerOfMass[0] + centerOfMass[1] * centerOfMass[1]);
		inertia(1, 0) += mass * (centerOfMass[0] * centerOfMass[1]);
		inertia(2, 1) += mass * (centerOfMass[1] * centerOfMass[2]);
		inertia(2, 0) += mass * (centerOfMass[2] * centerOfMass[0]);

	}
	
		

		inertia(0, 1) = inertia(1, 0);
		inertia(1, 2) = inertia(2, 1);
		inertia(0, 2) = inertia(2, 0);

	
	


}

void OdinMath::computeProperties(std::vector<Vector4>& points, int tmax, std::vector<int>& indices, float& mass, Vector4& centerOfMass, Matrix4& inertia, bool bodyCoords);
void OdinMath::computeProperties(std::vector<Vector4>& points, int tmax, std::vector<int>& indices, double& mass, Vector4& centerOfMass, Matrix4& inertia, bool bodyCoords);
