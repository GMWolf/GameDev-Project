#include "Aspect.h"

Aspect::Aspect() : bits(0)
{
}

bool Aspect::subAspect(const Aspect & rhs) const
{
	return (bits & rhs.bits) == bits;
}

bool Aspect::intersects(const Aspect & rhs) const
{
	return (bits & rhs.bits) > 0;
}

void Aspect::set(const unsigned int i)
{
	bits |= 1 << i;
}

void Aspect::unset(const unsigned int i)
{
	bits &= ~(1 << i);
}
