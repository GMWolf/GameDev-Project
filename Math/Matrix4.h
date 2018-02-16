#pragma once
#include "Swizzle.h"
#include <cstring>

class Matrix4 {

public:
	
	Matrix4() {
	};

	Matrix4(float e[16]) {
		std::memcpy(items, e, 16 * sizeof(float));
	};

	Matrix4 operator*(const Matrix4& rhs) const {
		Matrix4 ret;
		ret.items[ 0] = rhs.c0 * r0;
		ret.items[ 1] = rhs.c0 * r1;
		ret.items[ 2] = rhs.c0 * r2;
		ret.items[ 3] = rhs.c0 * r3;
		ret.items[ 4] = rhs.c1 * r0;
		ret.items[ 5] = rhs.c1 * r1;
		ret.items[ 6] = rhs.c1 * r2;
		ret.items[ 7] = rhs.c1 * r3;
		ret.items[ 8] = rhs.c2 * r0;
		ret.items[ 9] = rhs.c2 * r1;
		ret.items[10] = rhs.c2 * r2;
		ret.items[11] = rhs.c2 * r3;
		ret.items[12] = rhs.c3 * r0;
		ret.items[13] = rhs.c3 * r1;
		ret.items[14] = rhs.c3 * r2;
		ret.items[15] = rhs.c3 * r3;
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