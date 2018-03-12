#pragma once
#include "Event.h"
#include "Entity.h"

template<class... components>
struct EntityInserted : Event<EntityInserted<components>>
{

	EntityInserted(Entity entity) : entity(entity)
	{
	}

	Entity entity;

	
};
