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

	TEST_CLASS(TestDot4)
	{
	public:

		TEST_METHOD(TestDotTime)
		{
			/*Vector<4, float> a{ 1.f, 2.f, 3.f, 5.f };
			Vector<4, float> b{ 2.f, 2.f, 3.f, 5.f };

			InVectf aa;
			InVectf bb;
			loadVector4(aa, a);
			loadVector4(bb, b);

			float r = dot4(aa, bb);
			using std::chrono::high_resolution_clock;
			using std::chrono::duration_cast;
			using std::chrono::duration;
			using std::chrono::milliseconds;

			auto t1 = high_resolution_clock::now();
			for (int i = 0; i < 1000; i++) {
				dot4(aa, bb);

			}*/


			//auto t2 = high_resolution_clock::now();

			///* Getting number of milliseconds as an integer. */
			//duration<double, std::milli> ms_double = t2 - t1;
			//std::stringstream ss;
			//ss << "time: " << ms_double.count() << "\n";
			//Logger::WriteMessage(ss.str().c_str());


			//t1 = high_resolution_clock::now();
			//for (int i = 0; i < 1000; i++) {
			//	dot_product(a, b);
			//}

			//t2 = high_resolution_clock::now();
			//ms_double = t2 - t1;
			//std::stringstream _ss;
			//_ss << "time: " << ms_double.count() << "\n";
			//Logger::WriteMessage(_ss.str().c_str());

			//todo rewrite with pointers
		}

		




	};
}