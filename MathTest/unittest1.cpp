#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Math/Matrix4.h"
#include <iostream>
#include "../Math/Vector4.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestVector)
		{
			Vector3 vec(10, 20, 30);
			Vector3 sv(0,0,0);
			sv.xy = vec.yz;

			Assert::AreEqual(sv.x, vec.y);
			

			sv.zx = vec.xx;
			Assert::AreEqual(sv.z, vec.x);
			Assert::AreEqual(sv.x, vec.x);

			Vector2 v2;
			v2 = vec.xz;

			Assert::AreEqual(v2.x, vec.x);
			Assert::AreEqual(v2.y, vec.z);
		}

		TEST_METHOD(TestMatrix)
		{
			float a[16] = {
				5, 9, 88, 9,
				10, 25, 64, 1,
				50, 78, 2, 13,
				5, 1, 7, 5 };
			Matrix4 A(a);

			float b[16] = {
				1, 9, 8, 7,
				2, 10, 11, 57,
				5, 4, 3, 5,
				9, 8, 8, 0
			};
			Matrix4 B(b);

			float r[16] = {
				530, 865, 729, 157,
				945, 1183, 1237, 456,
				240, 384, 737, 113,
				525, 905, 1320, 193
			};
			Matrix4 R(r);

			Assert::IsTrue((A*B) == R);
		}

	};
}