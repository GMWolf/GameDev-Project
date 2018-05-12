#include "Component.h"
namespace ECS {
	/*int* getCompCounter()
	{
		static int* result = new int(0);
		return result;
	}*/
	int compCounter = 0;

	int* getCompCounter()
	{
		return nullptr;
	}

	int nextId()
	{
		return compCounter++;
	}

	UniqueId::UniqueId()
	{
		id = nextId();
	}

}