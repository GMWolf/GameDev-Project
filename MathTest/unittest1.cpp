#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math/Vector3.h"

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
		}

	};
}