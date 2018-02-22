#pragma once
#include <HashedArrayTree.h>

int _NextComponentId = 0;

#define COMPONENT(cs, T) \
		static HashedArrayTree<cs, T> mapper; \
		static int constexpr componentId = _NextComponentId++;