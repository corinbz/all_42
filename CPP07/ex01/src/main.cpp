#include "../include/iter.hpp"
#include <iostream>
#include <string>

// void capitalizeChar(char &c) {
//   c = std::toupper(static_cast<unsigned char>(c));
// }

template <typename T> void printElement(T &el) {
  std::cout << "- " << el << std::endl;
}

int main() {
  int int_array[] = {1, 2, 3, 4};
  std::string my_string = "abcd";
  double another_array[] = {0.3, 4.5, 2.0};

  iter<char>(&my_string[0], 4, printElement);
  iter<int>(&int_array[0], 4, printElement);
  iter<double>(&another_array[0], 3, printElement);
  return 0;
}
