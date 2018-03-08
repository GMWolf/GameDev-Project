#include "stdafx.h"
#include "CameraTransformSystem.h"
#include "SubscriptionManager.h"
#include "Camera.h"
#include "Transform.h"


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
		camera.view = camera.invView.inverse();
	}
}

void CameraTransformSystem::end()
{
}
