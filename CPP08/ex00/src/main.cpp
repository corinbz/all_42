#include "../include/easyfind.hpp"
#include <array>
#include <iostream>
#include <vector>

int main() {
  int val = 1;

  std::array<int, 3> arrr = {1, 2, 3};
  std::array<int, 3>::const_iterator arr_it = easyfind(arrr, val);
  if (arr_it != arrr.end())
    std::cout << "Found it!" << std::endl;
  else
    std::cout << "Not found" << std::endl;

  std::vector<int> vecc = {1, 2, 3};
  std::vector<int>::const_iterator vec_it = easyfind(vecc, val);
  if (vec_it != vecc.end())
    std::cout << "Found it!" << std::endl;
  else
    std::cout << "Not found" << std::endl;
  return 0;
}
