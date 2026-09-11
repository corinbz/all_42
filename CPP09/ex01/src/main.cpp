#include "../include/RPN.hpp"
#include <iostream>
#include <stdexcept>

int main(int ac, char **av) {
  try {
    if (ac != 2)
      throw std::invalid_argument(
          "Invalid argument! \nUsage: ./RPN \"1 2 + 3 /\"");
    std::string input = av[1];
    RPN stack;
    std::cout << "Result is: " << stack.calculate(input) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
