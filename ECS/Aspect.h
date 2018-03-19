#pragma once

#define ASPECT_SIZE 32

class Aspect {

public:

	Aspect();
	Aspect(unsigned int bits);
	
	template<class... components>
	static Aspect getAspect();

	template<class component>
	static Aspect compAspect();

	Aspect operator&(const Aspect& rhs) const;

	bool operator<(const Aspect& rhs) const;


	bool subAspect(const Aspect& rhs) const;
	bool intersects(const Aspect& rhs) const;

	void set(const unsigned int i);

	void set(const Aspect& rhs);
	
	template<class component>
	void set();

	void unset(const unsigned int i);

	template<class component>
	void unset();

	template<class component>
	bool has() const;

	bool has(const int i) const;

	unsigned int bits;
};

template<class ...components>
inline Aspect Aspect::getAspect()
{
	unsigned int bits = 0;
	
	//Unpack and sum
	auto unpacker = {
		bits |= (1 << components::componentId)...
	};

	return Aspect(bits);
}

template<class component>
inline  Aspect Aspect::compAspect() {
	return Aspect(1 << component::componentId);
}

template<class component>
inline void Aspect::set()
{
	bits |= 1 << component::componentId;
}

template<class component>
inline void Aspect::unset()
{
	bits &= ~(1 << component::componentId);
}

template<class component>
inline bool Aspect::has() const
{
	return (bits & (1 << component::componentId));
}
