#include "ComponentMapper.h"
#include "Aspect.h"
//Construct On First Use (static init order fiasco)
std::vector<baseComponentMapper*>* baseComponentMapper::mappers()
{
	static std::vector<baseComponentMapper*>* m = new std::vector<baseComponentMapper*>(ASPECT_SIZE);
	return m;
}
