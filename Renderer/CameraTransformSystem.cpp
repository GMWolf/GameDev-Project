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

		glm::mat4 m;
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
			{
				m[i][j] = camera.invView.items[j + (i * 4)];
			}
		m = glm::inverse(m);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				camera.view.items[j + (i * 4)] = m[i][j];
			}

		//camera.view = camera.invView.inverse();
		/*camera.view.forward = (-Vector3(camera.invView.forward)).xyz;
		camera.view.up = (-Vector3(camera.invView.up)).xyz;
		camera.view.left = (-Vector3(camera.invView.left)).xyz;
		camera.view.position = (-Vector3(camera.invView.position)).xyz;*/
		Vector3 f = camera.invView.forward;
		std::cout << "face " << f.x << " " << f.y << " " << f.z << std::endl;
		f = camera.view.forward;
		std::cout << "inv face " << f.x << " " << f.y << " " << f.z << std::endl;
	}
}

void CameraTransformSystem::end()
{
}
