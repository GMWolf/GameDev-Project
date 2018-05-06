#include "stdafx.h"
#include "CameraTransformSystem.h"
#include "SubscriptionManager.h"
#include "Camera.h"
#include "Transform.h"
#include <glm/glm.hpp>


CameraTransformSystem::CameraTransformSystem(): 
	cameras(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Camera, Transform>()))
{
}


CameraTransformSystem::~CameraTransformSystem()
{
}

void CameraTransformSystem::init()
{
}

void CameraTransformSystem::update()
{
	for(ECS::Entity camEntity : cameras)
	{
		Camera& camera = camEntity.get<Camera>();
		Transform& transform = camEntity.get<Transform>();


		glm::vec3 pos = transform.getPosition();
		glm::mat4 rot = transform.getRotation();
		glm::vec3 lookat = pos + glm::vec3(rot[2]);
		glm::vec3 up = glm::vec3(rot[1]);

		camera.view = glm::lookAt(pos, lookat, up);
		camera.invView = glm::inverse(camera.view);

		
		//camera.view = camera.invView.inverse();
		/*camera.view.forward = (-Vector3(camera.invView.forward)).xyz;
		camera.view.up = (-Vector3(camera.invView.up)).xyz;
		camera.view.left = (-Vector3(camera.invView.left)).xyz;
		camera.view.position = (-Vector3(camera.invView.position)).xyz;*/
		/*glm::vec3 f = camera.invView[2];
		std::cout << "    face " << f.x << " " << f.y << " " << f.z << std::endl;
		f = camera.view[2];
		std::cout << "inv face " << f.x << " " << f.y << " " << f.z << std::endl;*/
	}
}

void CameraTransformSystem::end()
{
}
