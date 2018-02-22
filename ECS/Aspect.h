#pragma once
class Aspect {

public:

	Aspect();

	bool subAspect(const Aspect& rhs) const;
	bool intersects(const Aspect& rhs) const;

	void set(const unsigned int i);
	void unset(const unsigned int i);

	unsigned int bits;
};