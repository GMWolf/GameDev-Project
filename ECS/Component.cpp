#include "Component.h"
namespace ECS {
	ComponentId::ComponentId() : id(nextId())
	{
	}
}