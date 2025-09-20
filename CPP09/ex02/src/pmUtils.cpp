#include "../include/PmergeMe.hpp"

std::vector<int> PmergeMe::buildJacobsthalSeq(int size) {
  std::vector<int> seq;
  if (size <= 0)
    return seq;
  seq.push_back(1); // start with 1
  int j1 = 1, j2 = 1;
  while (true) {
    int jNext = j2 + 2 * j1;
    seq.push_back(jNext);
    if (jNext >= size)
      break;
    j1 = j2;
    j2 = jNext;
  }
  return seq;
}

std::vector<int> PmergeMe::buildInsertSeq(int size,
                                          const std::vector<int> jacSeq) {
  std::vector<int> ordered;
  if (size <= 0 || jacSeq.empty())
    return ordered;

  std::vector<int> res;
  int prev = 0;
  for (const auto &element : jacSeq) {
    int j = element;
    // res.push_back(j);
    for (int k = j; k > prev; --k) // fill the numbers in reverse
      if (k <= size)
        res.push_back(k);
    prev = j;
  }
  return res;
}

bool PmergeMe::isMainChain(std::vector<int> vec, int pos, int blockSize) {
  int blockNum = pos / blockSize;

  // leftover numbers
  if ((blockNum + 1) * blockSize > vec.size())
    return false;
  // main (odd number indexes)
  if (blockNum % 2 == 1)
    return true;

  return false;
}
