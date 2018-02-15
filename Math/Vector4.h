#pragma once
#pragma once
#include "Swizzle.h"
class Vector4 {

public:

	Vector4() {
	}

	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z) {
	}


#pragma region arithmetic operators
	inline Vector4 operator+(const Vector4 &rhs) const {
		return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	inline Vector4 operator+(const float rhs) const {
		return Vector4(x + rhs, y + rhs, z + rhs, w + rhs);
	}

	inline Vector4 operator-(const Vector4 &rhs) const {
		return Vector4(x - rhs.y, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	inline Vector4 operator-(const float rhs) const {
		return Vector4(x - rhs, y - rhs, z - rhs, w - rhs);
	}

	inline Vector4 operator*(const float rhs) const {
		return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	inline Vector4 operator/(const float rhs) const {
		float s = 1 / rhs;
		return operator*(rhs);
	}

	inline Vector4 operator*(const Vector4 &rhs) const {
		return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	inline Vector4 operator/(const Vector4 &rhs) const {
		return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	inline Vector4& operator+=(const Vector4 &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	inline Vector4& operator+=(const float rhs) {
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return *this;
	}

	inline Vector4& operator-=(const Vector4 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	inline Vector4& operator-=(const float rhs) {
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return *this;
	}

	inline Vector4& operator*=(const Vector4& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	inline Vector4& operator*=(const float rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	inline Vector4& operator/=(const Vector4& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	inline Vector4& operator/=(const float rhs) {
		float s = 1 / rhs;
		return operator*=(s);
	}
#pragma endregion

	bool operator==(const Vector4& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}
	void operator=(const Vector4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}

#pragma region SwizzleOperations

#pragma endregion


	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};

		Swizzle2<4, 0, 0> xx;
		Swizzle2<4, 0, 1> xy;
		Swizzle2<4, 0, 2> xz;
		Swizzle2<4, 0, 3> xw;
		Swizzle2<4, 1, 0> yx;
		Swizzle2<4, 1, 1> yy;
		Swizzle2<4, 1, 2> yz;
		Swizzle2<4, 1, 3> yw;
		Swizzle2<4, 2, 0> zx;
		Swizzle2<4, 2, 1> zy;
		Swizzle2<4, 2, 2> zz;
		Swizzle2<4, 2, 3> zw;
		Swizzle2<4, 3, 0> wx;
		Swizzle2<4, 3, 1> wy;
		Swizzle2<4, 3, 2> wz;
		Swizzle2<4, 3, 3> ww;
		

		float items[4];
	};

};