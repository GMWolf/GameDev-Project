#pragma once
#include "Swizzle.h"
class Vector2 {

public:

	Vector2() {
	}

	Vector2(float x, float y) : x(x), y(y) {
	}

	template<int S, int A, int B>
	Vector2(Swizzle2<S, A, B> sw) : x(sw.items[A]), y(sw.items[B]) {
	}


#pragma region arithmetic operators
	inline Vector2 operator+(const Vector2 &rhs) const {
		return Vector2(x + rhs.x, y + rhs.y);
	}

	inline Vector2 operator+(const float rhs) const {
		return Vector2(x + rhs, y + rhs);
	}

	inline Vector2 operator-(const Vector2 &rhs) const {
		return Vector2(x - rhs.y, y - rhs.y);
	}

	inline Vector2 operator-(const float rhs) const {
		return Vector2(x - rhs, y - rhs);
	}

	inline Vector2 operator*(const float rhs) const {
		return Vector2(x * rhs, y * rhs);
	}

	inline Vector2 operator/(const float rhs) const {
		float s = 1 / rhs;
		return operator*(rhs);
	}

	inline Vector2 operator*(const Vector2 &rhs) const {
		return Vector2(x * rhs.x, y * rhs.y);
	}

	inline Vector2 operator/(const Vector2 &rhs) const {
		return Vector2(x / rhs.x, y / rhs.y);
	}

	inline Vector2& operator+=(const Vector2 &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	inline Vector2& operator+=(const float rhs) {
		x += rhs;
		y += rhs;
		return *this;
	}

	inline Vector2& operator-=(const Vector2 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	inline Vector2& operator-=(const float rhs) {
		x -= rhs;
		y -= rhs;
		return *this;
	}

	inline Vector2& operator*=(const Vector2& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	inline Vector2& operator*=(const float rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	inline Vector2& operator/=(const Vector2& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	inline Vector2& operator/=(const float rhs) {
		float s = 1 / rhs;
		return operator*=(s);
	}
#pragma endregion

	bool operator==(const Vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	void operator=(const Vector2& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	template<int S, int A, int B>
	void operator=(const Swizzle2<S, A, B>& rhs) {
		x = rhs.items[A];
		y = rhs.items[B];
	}

#pragma region SwizzleOperations

#pragma endregion


	union {
		struct {
			float x;
			float y;
		};

		Swizzle2<2, 0, 0> xx;
		Swizzle2<2, 0, 1> xy;
		Swizzle2<2, 1, 0> yx;
		Swizzle2<2, 1, 1> yy;

		float items[2];
	};

};