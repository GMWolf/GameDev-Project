#pragma once
#include <Vector3.h>
#include <Matrix4.h>
class Camera 
{
public:

	class positionComponent {
	public:
		positionComponent(Camera& parent) : parent(parent) {
		}
		void operator=(Vector3& rhs) {
			parent.viewMat.position = rhs.xyz;
			parent.dirty = true;
		}
		void operator+=(Vector3& rhs) {
			parent.viewMat.position += rhs.xyz;
			parent.dirty = true;
		}
	private:
		Camera & parent;
	};


	Camera();
	~Camera();

	void setProjection(const Matrix4& matrix);

	Matrix4& combined();

private:

	positionComponent position;

	Matrix4 viewMat;
	Matrix4 invViewMat;
	Matrix4 projMat;
	Matrix4 MVP;

	bool dirty;
};

