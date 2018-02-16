#pragma once
template<int size, int A, int B>
class Swizzle2 {
public:
	
	template<int rs, int rA, int rB>
	void operator=(Swizzle2<rs, rA, rB> rhs) {
		items[A] = rhs.items[rA];
		items[B] = rhs.items[rB];
	}

	float items[size];
};

template<int size, int A, int B, int C>
class Swizzle3 {
public:

	template<int rs, int rA, int rB, int rC>
	void operator=(Swizzle3<rs, rA, rB> rhs) {
		items[A] = rhs.items[rA];
		items[B] = rhs.items[rB];
		items[C] = rhs.items[rC];
	}

	float items[size];
};