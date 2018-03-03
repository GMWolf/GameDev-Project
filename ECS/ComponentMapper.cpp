#include "ComponentMapper.h"
#include "Aspect.h"
std::vector<baseComponentMapper*>* baseComponentMapper::mappers()
{
	static std::vector<baseComponentMapper*>* m = new std::vector<baseComponentMapper*>(ASPECT_SIZE);
	return m;
}
