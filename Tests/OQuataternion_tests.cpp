#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

void convertMatToQuat(float m[][4], float* f) {

	float r22 = m[2][2];
	if (r22 <= 0.f)  // x^2 + y^2 >= z^2 + w^2
	{
		float dif10 = m[1][1] - m[0][0];
		float omr22 = 1.f - r22;
		if (dif10 <= 0.f)  // x^2 >= y^2
		{
			float fourXSqr = omr22 - dif10;
			float inv4x = 0.5f / sqrtf(fourXSqr);
			f[0] = fourXSqr * inv4x;
			f[1] = (m[0][1] + m[1][0]) * inv4x;
			f[2] = (m[0][2] + m[2][0]) * inv4x;
			f[3] = (m[1][2] - m[2][1]) * inv4x;
		}
		else  // y^2 >= x^2
		{
			float fourYSqr = omr22 + dif10;
			float inv4y = 0.5f / sqrtf(fourYSqr);
			f[0] = (m[0][1] + m[1][0]) * inv4y;
			f[1] = fourYSqr * inv4y;
			f[2] = (m[1][2] + m[2][1]) * inv4y;
			f[3] = (m[2][0] - m[0][2]) * inv4y;
		}
	}
	else  // z^2 + w^2 >= x^2 + y^2
	{
		float sum10 = m[1][1] + m[0][0];
		float opr22 = 1.f + r22;
		if (sum10 <= 0.f)  // z^2 >= w^2
		{
			float fourZSqr = opr22 - sum10;
			float inv4z = 0.5f / sqrtf(fourZSqr);
			f[0] = (m[0][2] + m[2][0]) * inv4z;
			f[1] = (m[1][2] + m[2][1]) * inv4z;
			f[2] = fourZSqr * inv4z;
			f[3] = (m[0][1] - m[1][0]) * inv4z;
		}
		else  // w^2 >= z^2
		{
			float fourWSqr = opr22 + sum10;
			float inv4w = 0.5f / sqrtf(fourWSqr);
			f[0] = (m[1][2] - m[2][1]) * inv4w;
			f[1] = (m[2][0] - m[0][2]) * inv4w;
			f[2] = (m[0][1] - m[1][0]) * inv4w;
			f[3] = fourWSqr * inv4w;
		}
	}
	
}

namespace Tests
{
	TEST_CLASS(OQuatTests)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			OQuat<float> q(1.0, 0.0, 0.0, 0.0);
			Assert::AreEqual(q[0], 1.0f);
		}

		TEST_METHOD(TestRotToQuat) {
			OMatrix4<float> m1;
			OQuat<float> q1(m1);


			Assert::AreEqual(q1[3], 1.0f);
			OMatrix4<float> m2(1.f, 5.f, 0.f, 0.f,
				2.f, 2.f, -1.f, 0.f,
				1.f, 1.f, 6.f, 0.f,
				0.f, 0.f, 0.f, 0.f);

			OQuat<float> q2(m2);
			Assert::AreEqual(q1[3], 1.0f);
			Assert::AreEqual(std::roundf(q2[3]), 1.f);


			/*DXMatrix4 mat(1.f, 5.f, 0.f, 0.f,
				2.f, 2.f, -1.f, 0.f,
				1.f, 1.f, 6.f, 0.f,
				0.f, 0.f, 0.f, 0.f);

			XMVECTOR vector = XMQuaternionRotationMatrix(mat.getXMMatrix());*/




		}
		TEST_METHOD(TestRotToQuatDouble) {
			OMatrix4<double> m1;
			OQuat<double> q1(m1);


			Assert::AreEqual(q1[3], 1.00);
			OMatrix4<double> m2(1.f, 5.f, 0.f, 0.f,
				2.f, 2.f, -1.f, 0.f,
				1.f, 1.f, 6.f, 0.f,
				0.f, 0.f, 0.f, 0.f);
			OQuat<double> q3;
			quatRotMatrix<double, 4>(m2, q3);

			float data[4];
			OMatrix4<float> m3(1.f, 5.f, 0.f, 0.f,
				2.f, 2.f, -1.f, 0.f,
				1.f, 1.f, 6.f, 0.f,
				0.f, 0.f, 0.f, 0.f);
			convertMatToQuat(m3.m, data);

			OQuat<double> q2(m2);
			Assert::AreEqual(q1[3], 1.0);
			Assert::AreEqual(std::round(q2[3]), 1.0);


			DXMatrix4 mat(1.f, 5.f, 0.f, 0.f,
				2.f, 2.f, -1.f, 0.f,
				1.f, 1.f, 6.f, 0.f,
				0.f, 0.f, 0.f, 0.f);

			XMVECTOR vector = XMQuaternionRotationMatrix(mat.getXMMatrix());




		}
		TEST_METHOD(testQuattoRotf) {
			OQuat<float> q(1.f, 100.f, 200.f, 9.f);
			OMatrix4<float> m;
			q.toRotation(m);
			Assert::AreEqual(m(0, 0), -99999.f);

			DXQuat q2(1.f, 100.f, 200.f, 9.f);
			XMMATRIX matrix = XMMatrixRotationQuaternion(q2.getXMVector());

		}

		TEST_METHOD(testQuattoRotd) {
			OQuat<double> q(1.f, 100.f, 200.f, 9.f);
			OMatrix4<double> m;
			q.toRotation(m);
			Assert::AreEqual(m(0, 0), -99999.0);

			DXQuat q2(1.f, 100.f, 200.f, 9.f);
			XMMATRIX matrix = XMMatrixRotationQuaternion(q2.getXMVector());
			

		}
		TEST_METHOD(testEuler1) {
			OQuat<float> q(100.f, 3.f, 9.f);
			XMVECTOR vector = XMQuaternionRotationRollPitchYaw(3.f, 9.f, 100.f);
			Assert::AreEqual(roundf(q[3]), 0.f);

		}

		TEST_METHOD(testEuler2) {
			OQuat<float> q(100.f, 3.f, 9.f);
			float rpy[3];
			q.rollPitchYaw(rpy);
			Assert::AreEqual(round(rpy[0]), 3.f);
		}

		TEST_METHOD(testMult) {
			OVector3<float> a1(1.f, 2.f, 3.f);
			OVector3<float> a2(2.f, 3.f, 5.f);

			OQuat<float> q1(3.f, a1);
			OQuat<float> q2(1.f, a2);
			XMVECTOR qq1 = XMQuaternionRotationAxis({ 1.f, 2.f, 3.f }, 3.f);
			XMVECTOR qq2 = XMQuaternionRotationAxis({ 2.f, 3.f, 5.f }, 1.f);

			OQuat<float> q3 = q1 * q2;

			XMVECTOR qq3 = XMQuaternionMultiply(qq2, qq1);

			Assert::AreEqual(roundf(XMVectorGetW(qq3)), roundf(q3[3]));
			int u = 0xFFFFFFFF;
			
//#include <DirectXCollision.h>



		}
		


	};
}