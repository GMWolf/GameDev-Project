#include "SystemProfiler.h"
#include "Transform.h"
#include "TextComponent.h"


SystemProfiler::SystemProfiler()
{
}


SystemProfiler::~SystemProfiler()
{
}

void SystemProfiler::init()
{
	entity = Entity::create();
	entity.add(Transform());
}

void SystemProfiler::update()
{
}

void SystemProfiler::end()
{
}
