#pragma once
#include "Swizzle.h"
class Vector3 {

public:

	Vector3() {
	}

	Vector3(float x, float y, float z): x(x), y(y), z(z) {
	}


#pragma region arithmetic operators
	inline Vector3 operator+(const Vector3 &rhs) const {
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	inline Vector3 operator+(const float rhs) const {
		return Vector3(x + rhs, y + rhs, z + rhs);
	}

	inline Vector3 operator-(const Vector3 &rhs) const {
		return Vector3(x - rhs.y, y - rhs.y, z - rhs.z);
	}

	inline Vector3 operator-(const float rhs) const {
		return Vector3(x - rhs, y - rhs, z - rhs);
	}

	inline Vector3 operator*(const float rhs) const {
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	inline Vector3 operator/(const float rhs) const {
		float s = 1 / rhs;
		return operator*(rhs);
	}

	inline Vector3 operator*(const Vector3 &rhs) const {
		return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	inline Vector3 operator/(const Vector3 &rhs) const{
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	inline Vector3& operator+=(const Vector3 &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	inline Vector3& operator+=(const float rhs) {
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	inline Vector3& operator-=(const Vector3 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	inline Vector3& operator-=(const float rhs) {
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	inline Vector3& operator*=(const Vector3& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	inline Vector3& operator*=(const float rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	inline Vector3& operator/=(const Vector3& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	inline Vector3& operator/=(const float rhs) {
		float s = 1 / rhs;
		return operator*=(s);
	}
#pragma endregion

	bool operator==(const Vector3& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
	void operator=(const Vector3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

#pragma region SwizzleOperations

#pragma endregion


	union {
		struct {
			float x;
			float y;
			float z;
		};

		Swizzle2<4, 0, 0> xx;
		Swizzle2<4, 0, 1> xy;
		Swizzle2<4, 0, 2> xz;
		Swizzle2<4, 1, 0> yx;
		Swizzle2<4, 1, 1> yy;
		Swizzle2<4, 1, 2> yz;
		Swizzle2<4, 2, 0> zx;
		Swizzle2<4, 2, 1> zy;
		Swizzle2<4, 2, 2> zz;

		float items[4];
	};

};