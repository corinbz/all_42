#pragma once

#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

class PmergeMe {
private:
  // i don't need the class to be instantiated, just need the functions
  PmergeMe();
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);
  ~PmergeMe();

public:
  static std::vector<int> sortVector(int ac, char **av, int &comp);

  // utils
  static std::vector<int> buildJacobsthalSeq(int size);
  static std::vector<int> buildInsertSeq(int size,
                                         const std::vector<int> jacSeq);
};

// Include template implementations
#include "PmergeMe.tpp"
