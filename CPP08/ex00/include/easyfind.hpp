#pragma once
#include <algorithm>

// template to find b in containter a
// we assume T is a container of integers
template <typename T> typename T::const_iterator easyfind(const T &a, int b) {
  // return type will be an iterator.
  // iterator type is just a pointer to the a value inside the container.
  // iterator.end() point to the theoretical next element position. it's used to
  // check if any value was found.
  return (std::find(a.begin(), a.end(), b));
}
