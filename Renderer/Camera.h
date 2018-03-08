#pragma once
#include <Vector3.h>
#include <Matrix4.h>
#include <Component.h>

COMPONENT(Camera, 1)
{
	Matrix4 view;
	Matrix4 invView;
};