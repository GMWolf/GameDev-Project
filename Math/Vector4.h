#pragma once
#pragma once
#include "Swizzle.h"
class Vector4 {

public:

	Vector4() {
	}

	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z) {
	}

	template<int A, int B, int C, int D>
	Vector4(Swizzle4<4, A, B, C, D> sz)
		: x(sz.items[A]), y(sz.items[B]), z(sz.items[C]), w(sz.items[D]) {
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

#define GENERATE_SWIZZLE_3_0(id0, id1, pre) \
		Swizzle3<4, id0, id1, 0> pre##x; \
		Swizzle3<4, id0, id1, 1> pre##y; \
		Swizzle3<4, id0, id1, 2> pre##z; \
		Swizzle3<4, id0, id1, 3> pre##w;

#define GENERATE_SWIZZLE_3_1(id0, pre) \
		GENERATE_SWIZZLE_3_0(id0, 0, pre##x) \
		GENERATE_SWIZZLE_3_0(id0, 1, pre##y) \
		GENERATE_SWIZZLE_3_0(id0, 2, pre##z) \
		GENERATE_SWIZZLE_3_0(id0, 3, pre##w)

		GENERATE_SWIZZLE_3_1(0, x);
		GENERATE_SWIZZLE_3_1(1, y);
		GENERATE_SWIZZLE_3_1(2, z);
		GENERATE_SWIZZLE_3_1(3, w);

		//Generating 256 members!
#define GENERATE_SWIZZLE_4_0(id0, id1, id2, pre) \
		Swizzle4<4, id0, id1, id2, 0> pre##x; \
		Swizzle4<4, id0, id1, id2, 1> pre##y; \
		Swizzle4<4, id0, id1, id2, 2> pre##z; \
		Swizzle4<4, id0, id1, id2, 3> pre##w;

#define GENERATE_SWIZZLE_4_1(id0, id1, pre) \
		GENERATE_SWIZZLE_4_0(id0, id1, 0, pre##x) \
		GENERATE_SWIZZLE_4_0(id0, id1, 1, pre##y) \
		GENERATE_SWIZZLE_4_0(id0, id1, 2, pre##z) \
		GENERATE_SWIZZLE_4_0(id0, id1, 3, pre##w)

#define GENERATE_SWIZZLE_4_2(id0, pre) \
		GENERATE_SWIZZLE_4_1(id0, 0, pre##x) \
		GENERATE_SWIZZLE_4_1(id0, 1, pre##y) \
		GENERATE_SWIZZLE_4_1(id0, 2, pre##z) \
		GENERATE_SWIZZLE_4_1(id0, 3, pre##w)

		GENERATE_SWIZZLE_4_2(0, x);
		GENERATE_SWIZZLE_4_2(1, y);
		GENERATE_SWIZZLE_4_2(2, z);
		GENERATE_SWIZZLE_4_2(3, w);

		float items[4];
	};


};