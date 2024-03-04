#pragma once

#include <set>
#include <algorithm>

template <class T, class CMP = std::less<T>, class ALLOC = std::allocator<T>>
std::set<T, CMP, ALLOC> operator*(
	const std::set<T, CMP, ALLOC>& s1, const std::set<T, CMP, ALLOC>& s2)
{
	std::set<T, CMP, ALLOC> res;
	std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
		std::inserter(res, s1.begin()));
	return res;
}
