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
  template <typename Container> Container fordJohnsonSort(Container arr);

  template <typename Container>
  void binaryInsert(Container &arr, typename Container::value_type value,
                    size_t end);

  std::vector<int> generateJacobsthal(int n);

public:
  PmergeMe();
  ~PmergeMe();

  void processSequence(const std::vector<std::string> &args);
  bool isValidInput(const std::vector<std::string> &args);

  template <typename Container>
  void displayResults(const Container &original, const Container &sorted,
                      double timeFirst, double timeSecond,
                      const std::string &firstType,
                      const std::string &secondType, int size);

  // Template method to get container type name
  template <typename Container> std::string getContainerName();
};

// Include template implementations
#include "PmergeMe.tpp"
