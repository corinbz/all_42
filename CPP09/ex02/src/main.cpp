#include "../include/PmergeMe.hpp"

// #TODO create function to check arguments
int main(int ac, char **av) {
  // std::vector<int> test;
  // test = PmergeMe::buildJacobsthalSeq(15);
  // std::vector<int> filled = PmergeMe::buildInsertSeq(15, test);
  // for (const auto &element : filled) {
  //   std::cout << element << " ";
  // }
  int comparisons = 0;
  std::vector result = PmergeMe::sortVector(ac, av, comparisons);
  for (const auto &element : result) {
    std::cout << element << " ";
  }
  return 0;
}
