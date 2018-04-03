#pragma once

template <typename T> 
inline int sgn(T val) {
	//https://stackoverflow.com/a/4609795/6702489
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
inline T clamp(T x, T vmin, T vmax)
{
	return min(max(x, vmin), vmax);
}

template <typename T>
inline T absmin(T a, T b)
{
	return (abs(a) < abs(b)) ? a : b;
}

template <typename T>
inline T absmax(T a, T b)
{
	return (abs(a) > abs(b)) ? a : b;
}