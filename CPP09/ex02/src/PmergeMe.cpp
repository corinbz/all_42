#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidInput(const std::vector<std::string> &args) {
  if (args.empty()) {
    std::cerr << "Error: No arguments provided" << std::endl;
    return false;
  }

  for (size_t i = 0; i < args.size(); ++i) {
    const std::string &arg = args[i];

    // Check if string contains only digits
    if (arg.empty() || arg[0] == '-' || arg[0] == '+') {
      std::cerr << "Error" << std::endl;
      return false;
    }

    for (size_t j = 0; j < arg.length(); ++j) {
      if (!std::isdigit(arg[j])) {
        std::cerr << "Error" << std::endl;
        return false;
      }
    }

    // Convert and check if it's a positive integer
    try {
      long num = std::atol(arg.c_str());
      if (num <= 0 || num > 2147483647) { // INT_MAX
        std::cerr << "Error" << std::endl;
        return false;
      }
    } catch (...) {
      std::cerr << "Error" << std::endl;
      return false;
    }
  }
  return true;
}

std::vector<int> PmergeMe::generateJacobsthal(int n) {
  std::vector<int> jacobsthal;
  if (n <= 0)
    return jacobsthal;

  jacobsthal.push_back(1);
  if (n <= 1)
    return jacobsthal;

  jacobsthal.push_back(1);

  int a = 1, b = 1;
  while (true) {
    int next = a + 2 * b;
    if (next > n)
      break;
    jacobsthal.push_back(next);
    a = b;
    b = next;
  }

  return jacobsthal;
}

void PmergeMe::processSequence(const std::vector<std::string> &args) {
  if (!isValidInput(args)) {
    return;
  }

  // Convert strings to integers and fill containers
  std::vector<int> originalVec;
  std::deque<int> originalDeq;

  for (size_t i = 0; i < args.size(); ++i) {
    int num = std::atoi(args[i].c_str());
    originalVec.push_back(num);
    originalDeq.push_back(num);
  }

  // Sort using vector with template
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  std::vector<int> sortedVec = fordJohnsonSort(originalVec);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  double timeVector =
      std::chrono::duration<double, std::micro>(end - start).count();

  // Sort using deque with template
  start = std::chrono::high_resolution_clock::now();
  std::deque<int> sortedDeq = fordJohnsonSort(originalDeq);
  end = std::chrono::high_resolution_clock::now();
  double timeDeque =
      std::chrono::duration<double, std::micro>(end - start).count();

  // Display results
  displayResults(originalVec, sortedVec, timeVector, timeDeque, "std::vector",
                 "std::deque", originalVec.size());
}

// main.cpp remains the same
