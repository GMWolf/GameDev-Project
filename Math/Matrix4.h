#pragma once
#include "Swizzle.h"
#include "Vector3.h"
#include <cstring>
class Matrix4 {

public:
	
	Matrix4() {
		for (int i = 0; i < 16; i++) {
			items[i] = 0;
		}
	};

	Matrix4(const Matrix4& rhs) {
		for (int i = 0; i < 16; i++) {
			items[i] = rhs.items[i];
		}
	}

	Matrix4& operator=(const Matrix4& rhs) {
		for (int i = 0; i < 16; i++) {
			items[i] = rhs.items[i];
		}
		return *this;
	}

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

	//taken from Software rasterizer, in turn Yoinked from the Open Source Doom 3 release - all credit goes to id software!
	Matrix4 inverse() {
		float det, invDet;

		Matrix4 mat(*this);

		//mat.items[0];

		// 2x2 sub-determinants required to calculate 4x4 determinant
		float det2_01_01 = mat.items[0] * mat.items[5] - mat.items[1] * mat.items[4];
		float det2_01_02 = mat.items[0] * mat.items[6] - mat.items[2] * mat.items[4];
		float det2_01_03 = mat.items[0] * mat.items[7] - mat.items[3] * mat.items[4];
		float det2_01_12 = mat.items[1] * mat.items[6] - mat.items[2] * mat.items[5];
		float det2_01_13 = mat.items[1] * mat.items[7] - mat.items[3] * mat.items[5];
		float det2_01_23 = mat.items[2] * mat.items[7] - mat.items[3] * mat.items[6];

		// 3x3 sub-determinants required to calculate 4x4 determinant
		float det3_201_012 = mat.items[8] * det2_01_12 - mat.items[9] * det2_01_02 + mat.items[10] * det2_01_01;
		float det3_201_013 = mat.items[8] * det2_01_13 - mat.items[9] * det2_01_03 + mat.items[11] * det2_01_01;
		float det3_201_023 = mat.items[8] * det2_01_23 - mat.items[10] * det2_01_03 + mat.items[11] * det2_01_02;
		float det3_201_123 = mat.items[9] * det2_01_23 - mat.items[10] * det2_01_13 + mat.items[11] * det2_01_12;

		det = (-det3_201_123 * mat.items[12] + det3_201_023 * mat.items[13] - det3_201_013 * mat.items[14] + det3_201_012 * mat.items[15]);


		invDet = 1.0f / det;

		// remaining 2x2 sub-determinants
		float det2_03_01 = mat.items[0] * mat.items[13] - mat.items[1] * mat.items[12];
		float det2_03_02 = mat.items[0] * mat.items[14] - mat.items[2] * mat.items[12];
		float det2_03_03 = mat.items[0] * mat.items[15] - mat.items[3] * mat.items[12];
		float det2_03_12 = mat.items[1] * mat.items[14] - mat.items[2] * mat.items[13];
		float det2_03_13 = mat.items[1] * mat.items[15] - mat.items[3] * mat.items[13];
		float det2_03_23 = mat.items[2] * mat.items[15] - mat.items[3] * mat.items[14];

		float det2_13_01 = mat.items[4] * mat.items[13] - mat.items[5] * mat.items[12];
		float det2_13_02 = mat.items[4] * mat.items[14] - mat.items[6] * mat.items[12];
		float det2_13_03 = mat.items[4] * mat.items[15] - mat.items[7] * mat.items[12];
		float det2_13_12 = mat.items[5] * mat.items[14] - mat.items[6] * mat.items[13];
		float det2_13_13 = mat.items[5] * mat.items[15] - mat.items[7] * mat.items[13];
		float det2_13_23 = mat.items[6] * mat.items[15] - mat.items[7] * mat.items[14];

		// remaining 3x3 sub-determinants
		float det3_203_012 = mat.items[8] * det2_03_12 - mat.items[9] * det2_03_02 + mat.items[10] * det2_03_01;
		float det3_203_013 = mat.items[8] * det2_03_13 - mat.items[9] * det2_03_03 + mat.items[11] * det2_03_01;
		float det3_203_023 = mat.items[8] * det2_03_23 - mat.items[10] * det2_03_03 + mat.items[11] * det2_03_02;
		float det3_203_123 = mat.items[9] * det2_03_23 - mat.items[10] * det2_03_13 + mat.items[11] * det2_03_12;

		float det3_213_012 = mat.items[8] * det2_13_12 - mat.items[9] * det2_13_02 + mat.items[10] * det2_13_01;
		float det3_213_013 = mat.items[8] * det2_13_13 - mat.items[9] * det2_13_03 + mat.items[11] * det2_13_01;
		float det3_213_023 = mat.items[8] * det2_13_23 - mat.items[10] * det2_13_03 + mat.items[11] * det2_13_02;
		float det3_213_123 = mat.items[9] * det2_13_23 - mat.items[10] * det2_13_13 + mat.items[11] * det2_13_12;

		float det3_301_012 = mat.items[12] * det2_01_12 - mat.items[13] * det2_01_02 + mat.items[14] * det2_01_01;
		float det3_301_013 = mat.items[12] * det2_01_13 - mat.items[13] * det2_01_03 + mat.items[15] * det2_01_01;
		float det3_301_023 = mat.items[12] * det2_01_23 - mat.items[14] * det2_01_03 + mat.items[15] * det2_01_02;
		float det3_301_123 = mat.items[13] * det2_01_23 - mat.items[14] * det2_01_13 + mat.items[15] * det2_01_12;

		mat.items[0] = -det3_213_123 * invDet;
		mat.items[4] = +det3_213_023 * invDet;
		mat.items[8] = -det3_213_013 * invDet;
		mat.items[12] = +det3_213_012 * invDet;

		mat.items[1] = +det3_203_123 * invDet;
		mat.items[5] = -det3_203_023 * invDet;
		mat.items[9] = +det3_203_013 * invDet;
		mat.items[13] = -det3_203_012 * invDet;

		mat.items[2] = +det3_301_123 * invDet;
		mat.items[6] = -det3_301_023 * invDet;
		mat.items[10] = +det3_301_013 * invDet;
		mat.items[14] = -det3_301_012 * invDet;

		mat.items[3] = -det3_201_123 * invDet;
		mat.items[7] = +det3_201_023 * invDet;
		mat.items[11] = -det3_201_013 * invDet;
		mat.items[15] = +det3_201_012 * invDet;

		return mat;
	}

	bool operator==(const Matrix4& rhs) const {
		for (int i = 0; i < 16; i++) {
			if (items[i] != rhs.items[i]){
				return false;
			}
		}
		return true;
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
		view.left = (-left).xyz;
		view.up = (up).xyz;
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