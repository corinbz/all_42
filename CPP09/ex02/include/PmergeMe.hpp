#pragma once

#include <algorithm>
#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

class PmergeMe {
private:
  // Private constructors to prevent instantiation
  PmergeMe();
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);
  ~PmergeMe();

  // Helper structures
  typedef std::pair<int, int> IntPair;
  typedef std::vector<IntPair> PairVector;

  // Vector helper functions
  static PairVector makePairs(const std::vector<int> &vec, int &straggler, bool &hasStraggler);
  static void sortPairsByLarger(PairVector &pairs);
  static void splitToMainAndPend(const PairVector &pairs,
                                 std::vector<int> &main,
                                 std::vector<int> &pend);
  static std::vector<int> buildInsertOrder(int pendSize);
  static void insertPend(std::vector<int> &main, const std::vector<int> &pend,
                         const std::vector<int> &order);
  static void addStraggler(std::vector<int> &main, int straggler,
                           bool hasStraggler);

  // Deque helper functions
  static PairVector makePairsDeq(const std::deque<int> &deq, int &straggler,
                                 bool &hasStraggler);
  static void splitToMainAndPendDeq(const PairVector &pairs,
                                    std::deque<int> &main,
                                    std::deque<int> &pend);
  static void insertPendDeq(std::deque<int> &main, const std::deque<int> &pend,
                            const std::vector<int> &order);
  static void addStragglerDeq(std::deque<int> &main, int straggler,
                              bool hasStraggler);

public:
  // Main sorting functions for different containers
  static void sortWithVector(const std::vector<int> &input);
  static void sortWithDeque(const std::vector<int> &input);

  // Ford-Johnson implementation for vector
  static std::vector<int> fjSortVec(std::vector<int> vec);

  // Ford-Johnson implementation for deque
  static std::deque<int> fjSortDeq(std::deque<int> deq);

  // Utility functions
  static std::vector<int> jacobsthal(int size);
  static int binSearch(const std::vector<int> &arr, int val, int end);
  static int binSearchDeq(const std::deque<int> &arr, int val, int end);
};
