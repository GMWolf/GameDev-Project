#pragma once
//https://stackoverflow.com/a/4609795/6702489
template <typename T> 
inline int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

template <typename  T> 
inline T min(T a, T b)
{
	return (a < b) ? a : b;
}

template <typename  T> 
inline T max(T a, T b)
{
	return (a > b) ? a : b;
}

template <typename T> 
inline T clamp(T x, T min, T max)
{
	return min(max(x, min), max);
}