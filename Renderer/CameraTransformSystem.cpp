#include "stdafx.h"
#include "CameraTransformSystem.h"
#include "SubscriptionManager.h"
#include "Camera.h"
#include "Transform.h"
#include <glm/glm.hpp>


CameraTransformSystem::CameraTransformSystem(): 
	cameras(SubscriptionManager::getSubscription(Aspect::getAspect<Camera, Transform>()))
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
	for(Entity camEntity : cameras)
	{
		Camera& camera = camEntity.get<Camera>();
		Transform& transform = camEntity.get<Transform>();

		camera.invView = transform.getMatrix();
		camera.view = glm::inverse(camera.invView);

		
		//camera.view = camera.invView.inverse();
		/*camera.view.forward = (-Vector3(camera.invView.forward)).xyz;
		camera.view.up = (-Vector3(camera.invView.up)).xyz;
		camera.view.left = (-Vector3(camera.invView.left)).xyz;
		camera.view.position = (-Vector3(camera.invView.position)).xyz;*/
		glm::vec3 f = camera.invView[2];
		std::cout << "    face " << f.x << " " << f.y << " " << f.z << std::endl;
		f = camera.view[2];
		std::cout << "inv face " << f.x << " " << f.y << " " << f.z << std::endl;
	}
}

void CameraTransformSystem::end()
{
}
