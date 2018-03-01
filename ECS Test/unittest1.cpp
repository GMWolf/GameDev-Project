#include "stdafx.h"
#include "CppUnitTest.h"
#include <Entity.h>
#include <ComponentManager.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ECSTest
{		

	class component1 {
		COMPONENT(64, component1);
	};

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
		}

	};
}