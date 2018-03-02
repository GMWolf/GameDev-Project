#pragma once
#include <array>
class Aspect {

public:

	Aspect();
	
	template<class... components>
	static Aspect getAspect();

	bool subAspect(const Aspect& rhs) const;
	bool intersects(const Aspect& rhs) const;

	void set(const unsigned int i);
	void unset(const unsigned int i);

	unsigned int bits;
};

template<class ...components>
inline Aspect Aspect::getAspect()
{
	/*auto ids = {
		components
	}*/
	return Aspect();
}
