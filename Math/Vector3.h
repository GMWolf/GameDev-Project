#pragma once
#include "Swizzle2.h"
class Vector3 {

public:

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


#pragma region Swizzles
	Swizzle2 xx() {
		return Swizzle2(x, x);
	}
	Swizzle2 xy() {
		return Swizzle2(x, y);
	}
	Swizzle2 yy() {
		return Swizzle2(y, y);
	}

#pragma endregion

	union {
		struct {
			float x;
			float y;
			float z;
		};

		float items[4];
	};

};