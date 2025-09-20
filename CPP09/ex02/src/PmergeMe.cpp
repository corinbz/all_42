#include "../include/PmergeMe.hpp"
#include <algorithm>
#include <filesystem>
#include <vector>

static std::vector<int> createVecFromArg(int ac, char **av) {
  std::vector<int> vec;
  vec.reserve(ac - 1);
  for (int i = 1; av[i]; i++) {
    vec.push_back(std::atoi(av[i]));
  }
  return vec;
}

int sortPairsRecVec(std::vector<int> &vec, int &comp, int recDepth) {
  int blockSize = 1u << (recDepth - 1); // 2^0 -> 2^1 -> 2^2 etc
  int totalBlocks = vec.size() / blockSize;

  /* std::cout << "depth : " << recDepth << std::endl; */
  /* std::cout << "blocksize : " << blockSize << std::endl; */
  /* std::cout << "totalBlocks : " << totalBlocks << std::endl; */
  if (totalBlocks <= 1)
    return recDepth - 1; // returns recursion level

  // iterate over the blocks. eg: blocksize 2 (5 9) (1 8)(4)
  //																					0
  // 1		2	3	 4
  //  first iteration i = 0
  //  0 + 2 * 2 - 1 < 5 -> 3 < 5
  //  if ( vec[0 + 2 -1] > vec[0 + 2 * 2 -1] -> vec[1] > vec[3] )
  //  swap_ranges will swap the blocks (5 9) and (1 8)
  //  new order will be 1 8 5 9 4
  int oldComp = comp;
  for (size_t i = 0; i + 2 * blockSize - 1 < vec.size(); i += 2 * blockSize) {
    ++comp;
    if (vec[i + blockSize - 1] > vec[i + 2 * blockSize - 1]) {
      std::swap_ranges(vec.begin() + i, vec.begin() + i + blockSize,
                       vec.begin() + i + blockSize);
      //						start of 1st block : end
      // 1st block				: start of 2nd block
    }
  }
  /* std::cout << "Swaps performed this depth : " << comp - oldComp << std::endl
   */
  /*           << std::endl; */
  return sortPairsRecVec(vec, comp, recDepth + 1);
}

void arrangeVec(std::vector<int> &vec, int blockSize,
                std::vector<int> insertSeq) {
  std::vector<int> main;
  std::vector<int> pEnd;

  std::cout << "vec: ";
  for (auto &element : vec) {
    std::cout << element << " ";
  }
  main.reserve(vec.size());
  pEnd.reserve(vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    if (PmergeMe::isMainChain(vec, i, blockSize))
      main.push_back(vec[i]);
    else
      pEnd.push_back(vec[i]);
  }
  std::cout << "main: ";
  for (auto &element : main) {
    std::cout << element << " ";
  }
  std::cout << "pEnd: ";
  for (auto &element : pEnd) {
    std::cout << element << " ";
  }
  main.insert(main.begin(), pEnd[insertSeq[0] - 1]);
  for (int i = 1; i < insertSeq.size(); i++) {
    int to_compare = main.size() / 2;
     while (pEnd[insertSeq[i] - 1] > main[to_compare]) to_compare /= 2;
  }
  std::cout << "main: ";
  for (auto &element : main) {
    std::cout << element << " ";
  }
  vec = main;
}

void insertPendVec(std::vector<int> &vec, int blockSize, int numPend,
                   const std::vector<int> &jacSeq, int &comp) {
  std::vector<int> insertSeq = PmergeMe::buildInsertSeq(numPend, jacSeq);
  /* std::cout << "insertSeq: "; */
  /* for (auto &element : insertSeq) { */
  /*   std::cout << element << " "; */
  /* } */
  arrangeVec(vec, blockSize, insertSeq);
  std::cout << std::endl;
  std::cout << "numPend: " << numPend << std::endl;
  std::cout << "blockSize: " << blockSize << std::endl;
  /* for (size_t i = 0; i < numPend; ++i) { */
  /* } */
}

std::vector<int> PmergeMe::sortVector(int ac, char **av, int &comp) {
  std::vector<int> vec = createVecFromArg(ac, av);
  if (vec.size() <= 1)
    return vec;
  int recDepth = sortPairsRecVec(vec, comp, 1);
  int maxPend = vec.size() / 2 + 1;
  std::vector<int> jacSeq = buildJacobsthalSeq(maxPend);
  while (recDepth > 0) {
    int blockSize = 1u << (recDepth - 1); // u makes 1 unsigned
    int numBlocks = vec.size() / blockSize;
    int numPend = numBlocks / 2;
    if (numBlocks % 2 != 0)
      ++numPend;
    std::cout << "Depth: " << recDepth << std::endl;
    if (numPend > 1)
      insertPendVec(vec, blockSize, numPend, jacSeq, comp);
    --recDepth;
  }
  return vec;
}
