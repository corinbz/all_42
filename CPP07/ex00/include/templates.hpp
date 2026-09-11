#pragma once

template <typename T> void swap(T &a, T &b) {
  T temp = b;
  b = a;
  a = temp;
}

template <typename T> T max(const T &a, const T &b) {
  if (a == b)
    return b;
  return (a > b ? a : b);
}

template <typename T> T min(const T &a, const T &b) {
  if (a == b)
    return b;
  return (a < b ? a : b);
}
