#pragma once
#include "Component.h"
#include "Entity.h"
COMPONENT(GuiItem, 16, 12)
{
	ECS::Entity parent;
};