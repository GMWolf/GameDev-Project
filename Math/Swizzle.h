#pragma once

template<int size, int A, int B>
class Swizzle2 {
public:
	
	template<int rs, int rA, int rB>
	void operator=(Swizzle2<rs, rA, rB> rhs) {
		items[A] = rhs.items[rA];
		items[B] = rhs.items[rB];
	};

	float items[size];
};

template<int size, int A, int B, int C>
class Swizzle3 {
public:

	template<int rs, int rA, int rB, int rC>
	Swizzle3<size, A, B, C>& operator=(const Swizzle3<rs, rA, rB, rC>& rhs) {
		items[A] = rhs.items[rA];
		items[B] = rhs.items[rB];
		items[C] = rhs.items[rC];
		return *this;
	};

	inline float& operator[](const int i){
		return items[i];
	};
	
	inline const float& operator[](const int i) const {
		return items[i];
	};

	template<int rs, int rA, int rB, int rC>
	Swizzle3<size, A, B, C>& operator+=(const Swizzle3<rs, rA, rB, rC>& rhs) {
		items[A] += rhs[rA];
		items[B] += rhs[rB];
		items[C] += rhs[rC];
		return *this;
	};

		float items[size];
	
};

template<int size, int A, int B, int C, int D>
class Swizzle4 {
public:


	inline float& operator[](const int i){
		return items[i];
	};


	inline float operator[](const int i) const{
		return items[i];
	};

	template<int rs, int rA, int rB, int rC, int rD>
	void operator=(const Swizzle4<rs, rA, rB, rC, rD>& rhs) {
		items[A] = rhs[rA];
		items[B] = rhs[rB];
		items[C] = rhs[rC];
		items[D] = rhs[rD];
	};

	template<int rA, int rB, int rC, int rD>
	inline float operator*(const Swizzle4 <size, rA, rB, rC, rD>& rhs) const {
		return (items[A] * rhs[rA]) +
			(items[B] * rhs[rB]) +
			(items[C] * rhs[rC]) +
			(items[D] * rhs[rD]);
	};

	union
	{
		float items[size];
		Swizzle3<size, A, A, A> xxx;
		Swizzle3<size, A, A, B> xxy;
		Swizzle3<size, A, A, C> xxz;
		Swizzle3<size, A, B, A> xyx;
		Swizzle3<size, A, B, B> xyy;
		Swizzle3<size, A, B, C> xyz;
		Swizzle3<size, A, C, A> xzx;
		Swizzle3<size, A, C, B> xzy;
		Swizzle3<size, A, C, C> xzz;
		Swizzle3<size, B, A, A> yxx;
		Swizzle3<size, B, A, B> yxy;
		Swizzle3<size, B, A, C> yxz;
		Swizzle3<size, B, B, A> yyx;
		Swizzle3<size, B, B, B> yyy;
		Swizzle3<size, B, B, C> yyz;
		Swizzle3<size, B, C, A> yzx;
		Swizzle3<size, B, C, B> yzy;
		Swizzle3<size, B, C, C> yzz;
		Swizzle3<size, C, A, A> zxx;
		Swizzle3<size, C, A, B> zxy;
		Swizzle3<size, C, A, C> zxz;
		Swizzle3<size, C, B, A> zyx;
		Swizzle3<size, C, B, B> zyy;
		Swizzle3<size, C, B, C> zyz;
		Swizzle3<size, C, C, A> zzx;
		Swizzle3<size, C, C, B> zzy;
		Swizzle3<size, C, C, C> zzz;
	};
	
};