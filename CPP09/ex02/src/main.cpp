#include "../include/PmergeMe.hpp"
#include <cctype>
#include <climits>
#include <cstdlib>
#include <set>
#include <sstream>

// Check if string represents a valid positive integer
bool isValidPosInt(const std::string &str) {
  if (str.empty())
    return false;

  // Check for leading zeros (except single "0")
  bool leadingZero = (str.length() > 1 && str[0] == '0');
  if (leadingZero)
    return false;

  // Check each character is a digit
  for (size_t i = 0; i < str.length(); i++) {
    if (!std::isdigit(str[i]))
      return false;
  }

  // Check if number is within valid range
  char *end;
  long num = std::strtol(str.c_str(), &end, 10);
  if (*end != '\0' || num > INT_MAX || num < 0)
    return false;

  return true;
}

// Parse command line arguments and validate input
bool parseArgs(int ac, char **av, std::vector<int> &nums) {
  const int MIN_ARGS = 2;
  if (ac < MIN_ARGS) {
    std::cerr << "Error: No arguments provided" << std::endl;
    return false;
  }

  // Process each argument (skip program name at index 0)
  for (int i = 1; i < ac; i++) {
    std::string arg(av[i]);

    // Check for negative numbers
    if (!arg.empty() && arg[0] == '-') {
      std::cerr << "Error" << std::endl;
      return false;
    }

    // Validate positive integer format
    if (!isValidPosInt(arg)) {
      std::cerr << "Error" << std::endl;
      return false;
    }

    // Convert string to integer
    int num = std::atoi(av[i]);
    nums.push_back(num);
  }

  // Check if we have at least one number
  if (nums.empty()) {
    std::cerr << "Error" << std::endl;
    return false;
  }

  return true;
}

// Display the unsorted sequence
void showBefore(const std::vector<int> &nums) {
  std::cout << "Before: ";
  for (size_t i = 0; i < nums.size(); i++) {
    std::cout << nums[i];
    if (i < nums.size() - 1) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  // Parse and validate command line arguments
  std::vector<int> nums;
  if (!parseArgs(argc, argv, nums)) {
    return 1;
  }

  // Display the original unsorted sequence
  showBefore(nums);

  // Sort using both container types and measure performance
  PmergeMe::sortWithVector(nums);
  PmergeMe::sortWithDeque(nums);

  return 0;
}
