#pragma once
#include "OdinMath.h"

#define MAX_ITERATIONS 10
#define EIGEN_TOL 1e-5

namespace OdinMath {

	

	//compute the Eigenvalues and eigenvectors of Matrix 
	class QREigen4 {
	private:
		Vector4 E;
		Matrix4 V;
		bool computeEigenValues;

		void hessenbergMatrix( Matrix4& H);
		/*Takes identity matrix R and given the row i and column j makes a rotation matrix*/
		void rotation(Matrix4& A, Matrix4& R, Matrix4& RT, int i, int j);
		

	public:
		
		QREigen4(Matrix4& A, bool computeEigenValues = true, int iterations = MAX_ITERATIONS, bool sortEig=true);
		QREigen4(Matrix4&& A, bool computeEigenValues = true, int iterations = MAX_ITERATIONS, bool sortEig=true);
		void sortEigenvalues();
		Matrix4 getEigenVectors() { return V; }
		Vector4 getEigenValues() { return E; }
	};

	
}

