#pragma once
#include <cstddef>
#include <iostream>

template <typename T> void iter(T *str, std::size_t len, void (*func)(T &)) {
  if (!str || !func) {
    std::cerr << "Invalid input" << std::endl;
    return;
  }
  for (std::size_t i = 0; i < len; ++i) {
    func(str[i]);
  }
}
