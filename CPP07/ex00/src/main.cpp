#include "../include/templates.hpp"
#include <iostream>

int main() {
  int a = 1;
  int b = 2;

  std::cout << "Running swap template...\n"
            << "Original values:\n"
            << "a = " << a << "\nb = " << b << std::endl;
  swap(a, b);
  std::cout << "After swap:\n" << "a = " << a << "\nb = " << b << std::endl;

  std::cout << "\n\nRunning max template...\n"
            << "Result is " << max(a, b) << std::endl;

  std::cout << "\n\nRunning min template...\n"
            << "Result is " << min(a, b) << std::endl;
}
