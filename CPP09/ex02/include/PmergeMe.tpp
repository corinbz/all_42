#pragma once

template <typename Container> 
std::string PmergeMe::getContainerName() {
  return "unknown";
}

template <> 
inline std::string PmergeMe::getContainerName<std::vector<int>>() {
  return "std::vector";
}

template <> 
inline std::string PmergeMe::getContainerName<std::deque<int>>() {
  return "std::deque";
}

template <> 
inline std::string PmergeMe::getContainerName<std::list<int>>() {
  return "std::list";
}

template <typename Container>
void PmergeMe::binaryInsert(Container &arr,
                            typename Container::value_type value, size_t end) {
  // For containers that support random access (vector, deque)
  if (end == 0) {
    arr.insert(arr.begin(), value);
    return;
  }

  // Binary search for insertion position
  typename Container::iterator start = arr.begin();
  typename Container::iterator endIt = start;
  std::advance(endIt, end);

  size_t left = 0, right = end;
  while (left < right) {
    size_t mid = left + (right - left) / 2;
    typename Container::iterator midIt = start;
    std::advance(midIt, mid);

    if (*midIt < value) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  typename Container::iterator insertPos = start;
  std::advance(insertPos, left);
  arr.insert(insertPos, value);
}

template <typename Container>
Container PmergeMe::fordJohnsonSort(Container arr) {
  size_t n = arr.size();

  if (n <= 1)
    return arr;

  // Convert container to vector for easier manipulation
  std::vector<typename Container::value_type> tempVec;
  for (typename Container::iterator it = arr.begin(); it != arr.end(); ++it) {
    tempVec.push_back(*it);
  }

  // Phase 1: Pair elements and compare
  std::vector<
      std::pair<typename Container::value_type, typename Container::value_type>>
      pairs;
  typename Container::value_type oddElement = typename Container::value_type();
  bool hasOdd = false;

  // Create pairs
  for (size_t i = 0; i < tempVec.size() - 1; i += 2) {
    if (tempVec[i] > tempVec[i + 1]) {
      pairs.push_back(std::make_pair(tempVec[i], tempVec[i + 1]));
    } else {
      pairs.push_back(std::make_pair(tempVec[i + 1], tempVec[i]));
    }
  }

  // Handle odd element
  if (tempVec.size() % 2 == 1) {
    oddElement = tempVec[tempVec.size() - 1];
    hasOdd = true;
  }

  if (pairs.empty()) {
    return arr;
  }

  // Phase 2: Recursively sort the larger elements
  Container largerElements;
  Container smallerElements;

  for (size_t i = 0; i < pairs.size(); ++i) {
    largerElements.insert(largerElements.end(), pairs[i].first);
    smallerElements.insert(smallerElements.end(), pairs[i].second);
  }

  // Recursive call
  largerElements = fordJohnsonSort(largerElements);

  // Phase 3: Insert smaller elements using Jacobsthal sequence
  Container result = largerElements;

  if (smallerElements.size() == 0) {
    if (hasOdd) {
      binaryInsert(result, oddElement, result.size());
    }
    return result;
  }std

  // Insert the first smaller element at the beginning
  result.insert(result.begin(), *smallerElements.begin());

  // Generate Jacobsthal numbers for insertion order
  std::vector<int> jacobsthal = generateJacobsthal(smallerElements.size());
  std::vector<bool> inserted(smallerElements.size(), false);

  inserted[0] = true; // First element already inserted

  // Convert smallerElements to vector for easier indexing
  std::vector<typename Container::value_type> smallerVec;
  for (typename Container::iterator it = smallerElements.begin();
       it != smallerElements.end(); ++it) {
    smallerVec.push_back(*it);
  }std

  // Insert remaining elements following Jacobsthal order
  for (size_t jIdx = 1; jIdx < jacobsthal.size(); jIdx++) {
    int j = jacobsthal[jIdx];

    // Insert elements from j down to previous Jacobsthal + 1
    int prevJ = (jIdx > 0) ? jacobsthal[jIdx - 1] : 0;

    for (int k = std::min(j, static_cast<int>(smallerVec.size())) - 1;
         k > prevJ - 1; k--) {
      if (!inserted[k]) {
        binaryInsert(result, smallerVec[k], result.size());
        inserted[k] = true;
      }
    }
  }

  // Insert any remaining elements
  for (size_t i = 0; i < smallerVec.size(); i++) {
    if (!inserted[i]) {
      binaryInsert(result, smallerVec[i], result.size());
    }
  }

  // Insert odd element if exists
  if (hasOdd) {
    binaryInsert(result, oddElement, result.size());
  }

  return result;
}

template <typename Container>
void PmergeMe::displayResults(const Container &original,
                              const Container &sorted, double timeFirst,
                              double timeSecond, const std::string &firstType,
                              const std::string &secondType, int size) {
  // Display original sequence
  std::cout << "Before: ";
  typename Container::const_iterator it = original.begin();
  for (int i = 0; i < 4 && it != original.end(); ++i, ++it) {
    std::cout << *it << " ";
  }
  if (original.size() > 4) {
    std::cout << "[...]";
  }
  std::cout << std::endl;

  // Display sorted sequence
  std::cout << "After: ";
  it = sorted.begin();
  for (int i = 0; i < 4 && it != sorted.end(); ++i, ++it) {
    std::cout << *it << " ";
  }
  if (sorted.size() > 4) {
    std::cout << "[...]";
  }
  std::cout << std::endl;

  // Display timing results
  std::cout << "Time to process a range of " << size << " elements with "
            << firstType << " : " << timeFirst << " us" << std::endl;
  std::cout << "Time to process a range of " << size << " elements with "
            << secondType << " : " << timeSecond << " us" << std::endl;
}
