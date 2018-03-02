#pragma once
class Aspect {

public:

	Aspect();
	Aspect(unsigned int bits);
	
	template<class... components>
	static Aspect getAspect();

	template<class component>
	static Aspect compAspect();

	Aspect operator&(const Aspect& rhs) const;


	bool subAspect(const Aspect& rhs) const;
	bool intersects(const Aspect& rhs) const;

	void set(const unsigned int i);
	
	template<class component>
	void set();

	void unset(const unsigned int i);

	template<class component>
	void unset();

	template<class component>
	bool has();



	unsigned int bits;
};

template<class ...components>
inline Aspect Aspect::getAspect()
{
	unsigned int bits = 0;
	
	//Unpack and sum
	auto unpacker = {
		bits |= components::componentAspect.bits...
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
	bits |= component::componentAspect.bits;
}

template<class component>
inline void Aspect::unset()
{
	bits &= ~(component::componentAspect.bits);
}

template<class component>
inline bool Aspect::has()
{
	return (bits & component::componentAspect.bits);
}
