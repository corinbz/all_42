#include "../include/Array.hpp"
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

int main() {
  // Test 1: Default constructor (empty array)
  std::cout << BOLD << CYAN << "=== Test 1: Empty array ===" << RESET
            << std::endl;
  Array<int> empty;
  std::cout << MAGENTA << "Size: " << RESET << GREEN << empty.size() << RESET
            << std::endl;
  try {
    empty[0];
  } catch (const std::out_of_range &e) {
    std::cout << RED << e.what() << RESET << std::endl;
  }
  std::cout << std::endl;

  // Test 2: Array of integers
  std::cout << BOLD << CYAN << "=== Test 2: Integer array ===" << RESET
            << std::endl;
  Array<int> intArray(3);
  intArray[0] = 1;
  intArray[1] = 2;
  intArray[2] = 3;
  std::cout << MAGENTA << "Size: " << RESET << GREEN << intArray.size() << RESET
            << std::endl;
  for (unsigned int i = 0; i < intArray.size(); ++i) {
    std::cout << MAGENTA << "intArray[" << i << "] = " << RESET << YELLOW
              << intArray[i] << RESET << std::endl;
  }
  try {
    intArray[3];
  } catch (const std::out_of_range &e) {
    std::cout << RED << e.what() << RESET << std::endl;
  }
  std::cout << std::endl;

  // Test 3: Copy constructor
  std::cout << BOLD << CYAN << "=== Test 3: Copy constructor ===" << RESET
            << std::endl;
  Array<int> copy(intArray);
  copy[1] = 999;
  std::cout << BLUE << "Original intArray[1] = " << RESET << YELLOW
            << intArray[1] << RESET << std::endl;
  std::cout << BLUE << "Copy copy[1] = " << RESET << YELLOW << copy[1] << RESET
            << std::endl;
  std::cout << std::endl;

  // Test 4: Assignment operator
  std::cout << BOLD << CYAN << "=== Test 4: Assignment operator ===" << RESET
            << std::endl;
  Array<int> assigned;
  assigned = intArray;
  assigned[2] = 777; // Modify assigned
  std::cout << BLUE << "Original intArray[2] = " << RESET << YELLOW
            << intArray[2] << RESET << std::endl;
  std::cout << BLUE << "Assigned assigned[2] = " << RESET << YELLOW
            << assigned[2] << RESET << std::endl;
  std::cout << std::endl;

  // Test 5: Array of doubles
  std::cout << BOLD << CYAN << "=== Test 5: Double array ===" << RESET
            << std::endl;
  Array<double> doubleArray(2);
  doubleArray[0] = 3.14;
  doubleArray[1] = 2.718;
  std::cout << MAGENTA << "Size: " << RESET << GREEN << doubleArray.size()
            << RESET << std::endl;
  for (unsigned int i = 0; i < doubleArray.size(); ++i) {
    std::cout << MAGENTA << "doubleArray[" << i << "] = " << RESET << YELLOW
              << doubleArray[i] << RESET << std::endl;
  }
  std::cout << std::endl;

  // Test 6: Array of strings
  std::cout << BOLD << CYAN << "=== Test 6: String array ===" << RESET
            << std::endl;
  Array<std::string> stringArray(2);
  stringArray[0] = "Hello";
  stringArray[1] = "World";
  std::cout << MAGENTA << "Size: " << RESET << GREEN << stringArray.size()
            << RESET << std::endl;
  for (unsigned int i = 0; i < stringArray.size(); ++i) {
    std::cout << MAGENTA << "stringArray[" << i << "] = " << RESET << YELLOW
              << stringArray[i] << RESET << std::endl;
  }

  return 0;
}
