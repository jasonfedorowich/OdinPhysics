#pragma once
#include "OdinMath.h"

#define MAX_ITERATIONS 50
namespace OdinMath {

	

	//compute the Eigenvalues and eigenvectors of Matrix 
	class QREigen4 {
	private:
		Matrix4 E;
		Matrix4 V;
		bool computeEigenValues;

		void hessenbergMatrix( Matrix4& H);
		

	public:
		
		QREigen4(Matrix4& A, bool computeEigenValues = true);
		QREigen4(Matrix4&& A, bool computeEigenValues = true);

		Matrix4 getEigenVectors();
		Matrix4 getEigenValues();
	};

	
}

