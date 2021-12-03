#include "pch.h"
#include "CppUnitTest.h"
#include <chrono>
#include <sstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OdinMath;

namespace MathTests
{

	float dot_product(Vector<4, float> a, Vector<4, float> b) {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	}


	float deter2(float mm[][4]) {
		float a0 = mm[0][0] * mm[1][1] - mm[0][1] * mm[1][0];
		float a1 = mm[0][0] * mm[1][2] - mm[0][2] * mm[1][0];
		float a2 = mm[0][0] * mm[1][3] - mm[0][3] * mm[1][0];
		float a3 = mm[0][1] * mm[1][2] - mm[0][2] * mm[1][1];

		float a4 = mm[0][1] * mm[1][3] - mm[0][3] * mm[1][1];
		float a5 = mm[0][2] * mm[1][3] - mm[0][3] * mm[1][2];
		float b0 = mm[2][0] * mm[3][1] - mm[2][1] * mm[3][0];
		float b1 = mm[2][0] * mm[3][2] - mm[2][2] * mm[3][0];

		float b5 = mm[2][2] * mm[3][3] - mm[2][3] * mm[3][2];
		float b4 = mm[2][1] * mm[3][3] - mm[2][3] * mm[3][1];
		float b3 = mm[2][1] * mm[3][2] - mm[2][2] * mm[3][1];
		float b2 = mm[2][0] * mm[3][3] - mm[2][3] * mm[3][0];



		float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
		return det;
	}


	float trace(float m[][4]) {

		return m[0][0] + m[1][1] + m[2][2] + m[3][3];
	}

	TEST_CLASS(TestSIMDSpeed)
	{
	public:

		TEST_METHOD(testDotTime)
		{
			Vector<4, float> a{ 1.f, 2.f, 3.f, 5.f };
			Vector<4, float> b{ 2.f, 2.f, 3.f, 5.f };

			InVectf aa;
			InVectf bb;


			using std::chrono::high_resolution_clock;
			using std::chrono::duration_cast;
			using std::chrono::duration;
			using std::chrono::milliseconds;

			auto t1 = high_resolution_clock::now();
			for (int i = 0; i < 1000; i++) {
				dot4<float>(a.data, b.data);

			}


			auto t2 = high_resolution_clock::now();

			/* Getting number of milliseconds as an integer. */
			duration<double, std::milli> ms_double = t2 - t1;
			std::stringstream ss;
			ss << "time: " << ms_double.count() << "\n";
			Logger::WriteMessage(ss.str().c_str());


			t1 = high_resolution_clock::now();
			for (int i = 0; i < 1000; i++) {
				dot_product(a, b);
			}

			t2 = high_resolution_clock::now();
			ms_double = t2 - t1;
			std::stringstream _ss;
			_ss << "time: " << ms_double.count() << "\n";
			Logger::WriteMessage(_ss.str().c_str());

		}

		TEST_METHOD(testDXIntri) {
			DXMatrix4 A(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);

			using std::chrono::high_resolution_clock;
			using std::chrono::duration_cast;
			using std::chrono::duration;
			using std::chrono::milliseconds;

			auto t1 = high_resolution_clock::now();
			XMMATRIX mm = A.getXMMatrix();
			for (int i = 0; i < 10000; i++) {


				XMMatrixDeterminant(mm);
			}
			auto t2 = high_resolution_clock::now();
			/* Getting number of milliseconds as an integer. */
			duration<double, std::milli> ms_double = t2 - t1;
			std::stringstream ss;
			ss << "time: " << ms_double.count() << "\n";
			Logger::WriteMessage(ss.str().c_str());

			float P[4][4] = { {11.f,   9,   24,    2 },
	  {1,    5,   2,    6},
	  { 3,   17,   18,    1 },
	  { 2,    5,    7,    1 }


			};

			t1 = high_resolution_clock::now();
			for (int i = 0; i < 10000; i++) {


				deter2(P);
			}
			t2 = high_resolution_clock::now();
			/* Getting number of milliseconds as an integer. */
			duration<double, std::milli> ms_double2 = t2 - t1;
			std::stringstream ss2;
			ss2 << "time: " << ms_double2.count() << "\n";
			Logger::WriteMessage(ss2.str().c_str());


		}

		TEST_METHOD(testTrace) {

			OMatrix4<float> A(11.f, 9, 24, 2,
				1, 5, 2, 6,
				3, 17, 18, 1,
				2, 5, 7, 1);
			using std::chrono::high_resolution_clock;
			using std::chrono::duration_cast;
			using std::chrono::duration;
			using std::chrono::milliseconds;

			auto t1 = high_resolution_clock::now();
			
			for (int i = 0; i < 10000; i++) {


				A.trace();
			}
			auto t2 = high_resolution_clock::now();
			/* Getting number of milliseconds as an integer. */
			duration<double, std::milli> ms_double = t2 - t1;
			std::stringstream ss;
			ss << "time: " << ms_double.count() << "\n";
			Logger::WriteMessage(ss.str().c_str());

			float P[4][4] = { {11.f,   9,   24,    2 },
	  {1,    5,   2,    6},
	  { 3,   17,   18,    1 },
	  { 2,    5,    7,    1 }


			};

			t1 = high_resolution_clock::now();
			for (int i = 0; i < 10000; i++) {


				trace(P);
			}
			t2 = high_resolution_clock::now();
			/* Getting number of milliseconds as an integer. */
			duration<double, std::milli> ms_double2 = t2 - t1;
			std::stringstream ss2;
			ss2 << "time: " << ms_double2.count() << "\n";
			Logger::WriteMessage(ss2.str().c_str());

		}

		




	};
}