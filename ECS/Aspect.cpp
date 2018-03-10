#include "Aspect.h"

Aspect::Aspect() : bits(0)
{
}

Aspect::Aspect(unsigned int bits) : bits(bits)
{
}

Aspect Aspect::operator&(const Aspect & rhs) const
{
	return Aspect(bits & rhs.bits);
}

bool Aspect::operator<(const Aspect & rhs) const
{
	return bits < rhs.bits;
}

bool Aspect::subAspect(const Aspect & rhs) const
{
	return (bits & rhs.bits) == bits;
}

bool Aspect::intersects(const Aspect & rhs) const
{
	return (bits & rhs.bits);
}

void Aspect::set(const unsigned int i)
{
	bits |= 1 << i;
}

void Aspect::set(const Aspect& rhs)
{
	bits |= rhs.bits;
}


void Aspect::unset(const unsigned int i)
{
	bits &= ~(1 << i);
}

bool Aspect::has(const int i) const
{
	return bits & (1 << i);
}
