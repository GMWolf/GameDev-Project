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

	inline float& operator[](const int i) const {
		return items[i];
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

	float items[size];
};