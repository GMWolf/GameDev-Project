#include "stdafx.h"
#include "Camera.h"


Camera::Camera() : position(*this)
{
}


Camera::~Camera()
{
}

void Camera::setProjection(const Matrix4 & matrix)
{
	projMat = matrix;
}

inline Matrix4 & Camera::combined() {
	if (dirty) {
		invViewMat = viewMat.inverse();
		MVP = projMat * invViewMat;
	}
	return MVP;
}
