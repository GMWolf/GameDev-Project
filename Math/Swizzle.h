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