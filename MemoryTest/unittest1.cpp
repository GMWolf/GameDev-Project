#include "stdafx.h"
#include "CppUnitTest.h"
#include <DynBitset.h>
#include "HashedArrayTree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MemoryTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestDynBitset)
		{
			DynBitset bs;

			bs.set(0);

			Assert::IsTrue(bs[0]);

			bs.set(65);

			Assert::IsTrue(bs[65]);
		}


		TEST_METHOD(TestArrayTree)
		{
			HashedArrayTree<16, int> ints;

			ints.emplace(5, 4);

			Assert::IsTrue(ints[5] == 4);
		}
	};
}