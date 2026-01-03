#include "../include/PmergeMe.hpp"

// Generate Jacobsthal sequence 
std::vector<int> PmergeMe::jacobsthal(int size) {
    std::vector<int> seq;
    if (size <= 0) return seq;
    
    seq.push_back(0);
    seq.push_back(1);
    
    while (seq.back() < size) {
        int prev = seq[seq.size() - 2];
        int curr = seq.back();
        int next = curr + 2 * prev;
        seq.push_back(next);
    }
    
    return seq;
}

// Binary search to find insertion position in vector
int PmergeMe::binSearch(const std::vector<int>& arr, int val, int end) {
    int left = 0;
    int right = end;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > val) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Binary search to find insertion position in deque
int PmergeMe::binSearchDeq(const std::deque<int>& arr, int val, int end) {
    int left = 0;
    int right = end;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > val) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Create pairs from input vector
PmergeMe::PairVector PmergeMe::makePairs(const std::vector<int>& vec,
                                         int& straggler,
                                         bool& hasStraggler) {
    PairVector pairs;
    size_t size = vec.size();
    
    // Process elements in pairs
    for (size_t i = 0; i < size - 1; i += 2) {
        int first = vec[i];
        int second = vec[i + 1];
        
        // Ensure larger element is second in pair
        if (first > second) {
            pairs.push_back(std::make_pair(second, first));
        } else {
            pairs.push_back(std::make_pair(first, second));
        }
    }
    
    // Check for odd number of elements (straggler)
    hasStraggler = (size % 2 == 1);
    if (hasStraggler) {
        straggler = vec[size - 1];
    }
    
    return pairs;
}

// CORRECTED: Recursively sort pairs by their larger elements using Ford-Johnson
void PmergeMe::sortPairsByLarger(PairVector& pairs) {
    if (pairs.size() <= 1) return;
    
    // Extract larger elements
    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); i++) {
        largerElements.push_back(pairs[i].second);
    }
    
    // Recursively sort the larger elements using Ford-Johnson
    std::vector<int> sortedLarger = fjSortVec(largerElements);
    
    // Reorder pairs based on sorted larger elements
    PairVector sortedPairs;
    for (size_t i = 0; i < sortedLarger.size(); i++) {
        // Find the pair with this larger element
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].second == sortedLarger[i]) {
                sortedPairs.push_back(pairs[j]);
                // Mark as used by setting to invalid value
                pairs[j].second = -1;
                break;
            }
        }
    }
    
    pairs = sortedPairs;
}

// Extract main chain and pending elements from sorted pairs
void PmergeMe::splitToMainAndPend(const PairVector& pairs,
                                  std::vector<int>& main,
                                  std::vector<int>& pend) {
    for (PairVector::const_iterator it = pairs.begin(); 
         it != pairs.end(); ++it) {
        main.push_back(it->second);  // Larger elements form main chain
        pend.push_back(it->first);   // Smaller elements are pending
    }
}

// Generate optimal insertion order using Jacobsthal sequence
std::vector<int> PmergeMe::buildInsertOrder(int pendSize) {
    std::vector<int> jac = jacobsthal(pendSize);
    std::vector<int> order;
    std::set<int> used;
    
    // Build insertion order based on Jacobsthal sequence
    for (size_t i = 2; i < jac.size(); i++) {
        int curr = jac[i];
        int prev = jac[i - 1];
        
        // Cap current at pendSize
        if (curr > pendSize) curr = pendSize;
        
        // Insert indices in descending order from curr down to prev+1
        for (int j = curr - 1; j >= prev; j--) {
            if (used.find(j) == used.end()) {
                order.push_back(j);
                used.insert(j);
            }
        }
    }
    
    // Add any remaining indices not covered by Jacobsthal sequence
    for (int i = 0; i < pendSize; i++) {
        if (used.find(i) == used.end()) {
            order.push_back(i);
        }
    }
    
    return order;
}

// CORRECTED: Insert pending elements with proper search range limits
void PmergeMe::insertPend(std::vector<int>& main,
                         const std::vector<int>& pend,
                         const std::vector<int>& order) {
    
    for (size_t i = 0; i < order.size(); i++) {
        int idx = order[i];
        if (idx < static_cast<int>(pend.size())) {
            int val = pend[idx];
            
            // Calculate search limit: position of paired element + already inserted
            // The paired larger element is at position idx+1 in the original main chain
            // Plus we've already inserted i elements before this one
            int searchLimit = idx + 1 + i + 1;
            if (searchLimit > static_cast<int>(main.size())) {
                searchLimit = main.size();
            }
            
            int pos = binSearch(main, val, searchLimit);
            main.insert(main.begin() + pos, val);
        }
    }
}

// Insert straggler element if it exists
void PmergeMe::addStraggler(std::vector<int>& main,
                            int straggler,
                            bool hasStraggler) {
    if (hasStraggler) {
        int pos = binSearch(main, straggler, main.size());
        main.insert(main.begin() + pos, straggler);
    }
}

// ================== DEQUE HELPER FUNCTIONS ==================

PmergeMe::PairVector PmergeMe::makePairsDeq(const std::deque<int>& deq,
                                            int& straggler,
                                            bool& hasStraggler) {
    PairVector pairs;
    size_t size = deq.size();
    
    for (size_t i = 0; i < size - 1; i += 2) {
        int first = deq[i];
        int second = deq[i + 1];
        
        if (first > second) {
            pairs.push_back(std::make_pair(second, first));
        } else {
            pairs.push_back(std::make_pair(first, second));
        }
    }
    
    hasStraggler = (size % 2 == 1);
    if (hasStraggler) {
        straggler = deq[size - 1];
    }
    
    return pairs;
}

void PmergeMe::splitToMainAndPendDeq(const PairVector& pairs,
                                     std::deque<int>& main,
                                     std::deque<int>& pend) {
    for (PairVector::const_iterator it = pairs.begin();
         it != pairs.end(); ++it) {
        main.push_back(it->second);
        pend.push_back(it->first);
    }
}

void PmergeMe::insertPendDeq(std::deque<int>& main,
                             const std::deque<int>& pend,
                             const std::vector<int>& order) {
    for (size_t i = 0; i < order.size(); i++) {
        int idx = order[i];
        if (idx < static_cast<int>(pend.size())) {
            int val = pend[idx];
            
            // Apply same search limit optimization
            int searchLimit = idx + 1 + i + 1;
            if (searchLimit > static_cast<int>(main.size())) {
                searchLimit = main.size();
            }
            
            int pos = binSearchDeq(main, val, searchLimit);
            main.insert(main.begin() + pos, val);
        }
    }
}

void PmergeMe::addStragglerDeq(std::deque<int>& main,
                               int straggler,
                               bool hasStraggler) {
    if (hasStraggler) {
        int pos = binSearchDeq(main, straggler, main.size());
        main.insert(main.begin() + pos, straggler);
    }
}

// Ford-Johnson sort implementation for vector
std::vector<int> PmergeMe::fjSortVec(std::vector<int> vec) {
    size_t size = vec.size();
    
    // Handle base cases
    if (size <= 1) return vec;
    if (size == 2) {
        if (vec[0] > vec[1]) {
            std::swap(vec[0], vec[1]);
        }
        return vec;
    }
    
    // Step 1: Create pairs and identify straggler
    int straggler = -1;
    bool hasStraggler = false;
    PairVector pairs = makePairs(vec, straggler, hasStraggler);
    
    // Step 2: CORRECTED - Recursively sort pairs by their larger elements
    sortPairsByLarger(pairs);
    
    // Step 3: Extract main chain and pending elements
    std::vector<int> main;
    std::vector<int> pend;
    splitToMainAndPend(pairs, main, pend);
    
    // Step 4: Insert first pending element at the beginning
    if (!pend.empty()) {
        main.insert(main.begin(), pend[0]);
        pend.erase(pend.begin());
    }
    
    // Step 5: Generate optimal insertion order
    std::vector<int> order = buildInsertOrder(pend.size());
    
    // Step 6: CORRECTED - Insert remaining pending elements with search limits
    insertPend(main, pend, order);
    
    // Step 7: Insert straggler if exists
    addStraggler(main, straggler, hasStraggler);
    
    return main;
}

// Ford-Johnson sort implementation for deque
std::deque<int> PmergeMe::fjSortDeq(std::deque<int> deq) {
    size_t size = deq.size();
    
    if (size <= 1) return deq;
    if (size == 2) {
        if (deq[0] > deq[1]) {
            std::swap(deq[0], deq[1]);
        }
        return deq;
    }
    
    int straggler = -1;
    bool hasStraggler = false;
    PairVector pairs = makePairsDeq(deq, straggler, hasStraggler);
    
    // CORRECTED - Recursive sort
    sortPairsByLarger(pairs);
    
    std::deque<int> main;
    std::deque<int> pend;
    splitToMainAndPendDeq(pairs, main, pend);
    
    if (!pend.empty()) {
        main.push_front(pend[0]);
        pend.pop_front();
    }
    
    std::vector<int> order = buildInsertOrder(pend.size());
    
    // CORRECTED - Insert with search limits
    insertPendDeq(main, pend, order);
    
    addStragglerDeq(main, straggler, hasStraggler);
    
    return main;
}

// Sort with vector and display results with timing
void PmergeMe::sortWithVector(const std::vector<int>& input) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> sorted = fjSortVec(input);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                    (end - start);
    
    std::cout << "After:  ";
    for (size_t i = 0; i < sorted.size(); i++) {
        std::cout << sorted[i];
        if (i < sorted.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "Time to process a range of " << input.size() 
              << " elements with std::vector : " << duration.count() 
              << " us" << std::endl;
}

void PmergeMe::sortWithDeque(const std::vector<int>& input) {
    std::deque<int> deq(input.begin(), input.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::deque<int> sorted = fjSortDeq(deq);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                    (end - start);
    
    std::cout << "Time to process a range of " << input.size() 
              << " elements with std::deque  : " << duration.count() 
              << " us" << std::endl;
}
