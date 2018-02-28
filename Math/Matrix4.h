#pragma once
#include "Swizzle.h"
#include "Vector3.h"
#include <cstring>
#include <iostream>
class Matrix4 {

public:
	
	Matrix4() {
		for (int i = 0; i < 16; i++) {
			items[i] = 0;
		}
	};

	Matrix4(float e[16]) {
		std::memcpy(items, e, 16 * sizeof(float));
	};

	Matrix4 operator*(const Matrix4& rhs) const {
		Matrix4 ret;
		ret.items[0]  = r0 * rhs.c0;
		ret.items[1]  = r1 * rhs.c0;
		ret.items[2]  = r2 * rhs.c0;
		ret.items[3]  = r3 * rhs.c0;
		ret.items[4]  = r0 * rhs.c1;
		ret.items[5]  = r1 * rhs.c1;
		ret.items[6]  = r2 * rhs.c1;
		ret.items[7]  = r3 * rhs.c1;
		ret.items[8]  = r0 * rhs.c2;
		ret.items[9]  = r1 * rhs.c2;
		ret.items[10] = r2 * rhs.c2;
		ret.items[11] = r3 * rhs.c2;
		ret.items[12] = r0 * rhs.c3;
		ret.items[13] = r1 * rhs.c3;
		ret.items[14] = r2 * rhs.c3;
		ret.items[15] = r3 * rhs.c3;
		return ret;
	}

	bool operator==(const Matrix4& rhs) const {
		for (int i = 0; i < 16; i++) {
			if (items[i] != rhs.items[i]){
				return false;
			}
		}
		return true;
	}

	Matrix4& operator=(const Matrix4& rhs) {
		for (int i = 0; i < 16; i++) {
			items[i] = rhs.items[i];
		}
		return *this;
	}

	static Matrix4 Perspective(float znear, float zfar, float aspect, float fov) {
		/*Matrix4 matrix = Matrix4::Identity();
		float h = 1.0f / tan(fov*3.14159f / 360.f);
		float n = znear - zfar;
		matrix.items[0] = h / aspect;
		matrix.items[5] = h;
		matrix.items[10] = (zfar + znear) / n;
		matrix.items[11] = -1.0f;
		matrix.items[14] = (2.0f*znear*zfar) / n;
		matrix.items[15] = 0.0f;
		return matrix;*/
		
		float tan = tanf(fov * (3.14159f / 360));
		float h = znear * tan;
		float w = h * aspect;
		return Frustrum(-w, w, -h, h, znear, zfar);
	}

	static Matrix4 Frustrum(float left, float right, float bottom, float top, float zNear, float zFar) {
		Matrix4 matrix = Identity();
		matrix.items[0] = 2 * zNear / (right - left);
		matrix.items[5] = 2 * zNear / (top - bottom);
		matrix.items[8] = (right + left) / (right - left);
		matrix.items[9] = (top + bottom) / (top - bottom);
		matrix.items[10] = -(zFar + zNear) / (zFar - zNear);
		matrix.items[11] = -1;
		matrix.items[14] = -(2 * zFar*zNear) / (zFar - zNear);
		matrix.items[15] = 0;
		return matrix;
	}

	static Matrix4 ViewMatrix(const Vector3& eye, const Vector3& target, const Vector3& up) {
		Matrix4 view = Matrix4::Identity();
		
		view.position = (-eye).xyz;
		
		Vector3 forward = target - eye;
		forward.Normalize();

		Vector3 left = Vector3::Cross(up, forward);
		left.Normalize();

		/*view.r0.xyz = left.xyz;
		view.r1.xyz = up.xyz;
		view.r2.xyz = forward.xyz;*/
		view.left = (left).xyz;
		view.up = (-up).xyz;
		view.forward = (-forward).xyz;
		return view;
	}

	static Matrix4 Identity() {
		Matrix4 m;
		m.items[0] = 1.0f;
		m.items[5] = 1.0f;
		m.items[10] = 1.0f;
		m.items[15] = 1.0f;
		return m;
	}

	union {
		float items[16];

		Swizzle4<16, 0,  1,   2,  3> c0;
		Swizzle4<16, 4,  5,   6,  7> c1;
		Swizzle4<16, 8,  9,  10, 11> c2;
		Swizzle4<16, 12, 13, 14, 15> c3;

		Swizzle4<16, 0, 4, 8, 12> r0;
		Swizzle4<16, 1, 5, 9, 13> r1;
		Swizzle4<16, 2, 6, 10,14> r2;
		Swizzle4<16, 3, 7, 11, 15> r3;

		Swizzle3<16, 0, 1, 2> left;
		Swizzle3<16, 4, 5, 6> up;
		Swizzle3<16, 8, 9, 10> forward;
		Swizzle3<16, 12, 13, 14> position;
	};
};