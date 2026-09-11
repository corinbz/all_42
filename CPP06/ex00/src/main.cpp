#include "../include/ScalarConverter.hpp"
#include <iostream>

int main() {
  // Char inputs
  std::cout << "Test: Printable char (\"a\"):\n";
  ScalarConverter::convert("a");
  std::cout << "\n";

  // Int inputs
  std::cout << "Test: Positive integer (\"42\"):\n";
  ScalarConverter::convert("42");
  std::cout << "\n";

  // Float inputs
  std::cout << "Test: Positive float (\"42.0f\"):\n";
  ScalarConverter::convert("42.0f");
  std::cout << "\n";
  std::cout << "Test: NaN float (\"nan\"):\n";
  ScalarConverter::convert("nan");
  std::cout << "\n";

  // Double inputs
  std::cout << "Test: Negative double (\"-42.0\"):\n";
  ScalarConverter::convert("-42.0");
  std::cout << "\n";
  std::cout << "Test: Positive infinity double (\"+inf\"):\n";
  ScalarConverter::convert("+inf");
  std::cout << "\n";

  // Invalid input
  std::cout << "Test: Invalid input (\"invalid\"):\n";
  ScalarConverter::convert("invalid");
  std::cout << "\n";

  // Edge cases
  std::cout << "Test: Large float beyond int (\"2147483648.0f\"):\n";
  ScalarConverter::convert("2147483648.0f");
  std::cout << "\n";

  return 0;
}
