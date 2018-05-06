#include "EntityMotionState.h"
#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>


EntityMotionState::EntityMotionState(const ECS::Entity& e) : entity(e)
{
}


EntityMotionState::~EntityMotionState()
{
}

void EntityMotionState::getWorldTransform(btTransform& worldTrans) const
{
	Transform& t = entity.get<Transform>();
	worldTrans.setFromOpenGLMatrix(glm::value_ptr(glm::translate(glm::mat4(1), t.position) * t.rotation));
}

void EntityMotionState::setWorldTransform(const btTransform& worldTrans)
{
	Transform& t = entity.get<Transform>();

	const btVector3& pos = worldTrans.getOrigin();
	const btMatrix3x3& basis = worldTrans.getBasis();
	t.position = glm::vec3(pos.x(), pos.y(), pos.z());
	basis.getOpenGLSubMatrix(glm::value_ptr(t.rotation));
}
