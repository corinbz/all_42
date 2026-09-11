#include "../include/MutantStack.hpp"
#include <iostream>
#include <list>
#include <stack>
#include <vector>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

void printStack(const std::string &name, MutantStack<int> &mstack) {
  std::cout << BOLD << BLUE << "--- " << name << " ---" << RESET << std::endl;
  if (mstack.empty()) {
    std::cout << YELLOW << "Stack is empty." << RESET << std::endl;
    return;
  }
  std::cout << "Top element: " << GREEN << mstack.top() << RESET << std::endl;
  std::cout << "Size: " << GREEN << mstack.size() << RESET << std::endl;
  std::cout << "Elements (bottom to top):" << std::endl;
  MutantStack<int>::iterator it = mstack.begin();
  MutantStack<int>::iterator ite = mstack.end();
  while (it != ite) {
    std::cout << CYAN << *it << " " << RESET;
    ++it;
  }
  std::cout << std::endl;
  std::cout << BOLD << BLUE << "------------------" << RESET << std::endl;
}

int main() {
  std::cout << BOLD << MAGENTA
            << "--- Test 1: Basic Push, Pop, Top, Size, and Iteration ---"
            << RESET << std::endl;
  MutantStack<int> mstack;
  mstack.push(5);
  mstack.push(17);
  std::cout << "Top: " << GREEN << mstack.top() << RESET
            << std::endl; // Expected: 17
  mstack.pop();
  std::cout << "Size after pop: " << GREEN << mstack.size() << RESET
            << std::endl; // Expected: 1
  mstack.push(3);
  mstack.push(5);
  mstack.push(737);
  mstack.push(0);

  MutantStack<int>::iterator it = mstack.begin();
  MutantStack<int>::iterator ite = mstack.end();

  std::cout << "Iterating through mstack:" << std::endl;
  ++it; // Move past 5
  --it; // Move back to 5
  while (it != ite) {
    std::cout << CYAN << *it << RESET
              << std::endl; // Expected: 5, 3, 5, 737, 0 (bottom to top)
    ++it;
  }
  std::cout << std::endl;

  std::cout << BOLD << MAGENTA << "--- Test 2: Empty Stack ---" << RESET
            << std::endl;
  MutantStack<int> empty_mstack;
  std::cout << "Is empty_mstack empty? "
            << (empty_mstack.empty() ? GREEN "Yes" : RED "No") << RESET
            << std::endl; // Expected: Yes
  std::cout << "Size of empty_mstack: " << GREEN << empty_mstack.size() << RESET
            << std::endl; // Expected: 0
  MutantStack<int>::iterator empty_it = empty_mstack.begin();
  MutantStack<int>::iterator empty_ite = empty_mstack.end();
  std::cout << "Iterating through empty_mstack (should print nothing):"
            << std::endl;
  while (empty_it != empty_ite) {
    std::cout << CYAN << *empty_it << RESET << std::endl;
    ++empty_it;
  }
  std::cout << std::endl;

  std::cout << BOLD << MAGENTA << "--- Test 3: Popping all elements ---"
            << RESET << std::endl;
  MutantStack<int> full_pop_stack;
  full_pop_stack.push(1);
  full_pop_stack.push(2);
  full_pop_stack.push(3);
  printStack("Before popping all", full_pop_stack);
  while (!full_pop_stack.empty()) {
    std::cout << "Popping: " << GREEN << full_pop_stack.top() << RESET
              << std::endl;
    full_pop_stack.pop();
  }
  printStack("After popping all", full_pop_stack); // Should be empty

  std::cout << BOLD << MAGENTA
            << "--- Test 4: Iterator Increments and Decrements ---" << RESET
            << std::endl;
  MutantStack<int> iter_stack;
  iter_stack.push(10);
  iter_stack.push(20);
  iter_stack.push(30);
  iter_stack.push(40);

  MutantStack<int>::iterator current_it = iter_stack.begin();
  std::cout << "Current element: " << CYAN << *current_it << RESET
            << std::endl; // Expected: 10
  ++current_it;
  std::cout << "After ++: " << CYAN << *current_it << RESET
            << std::endl; // Expected: 20
  current_it++;
  std::cout << "After ++ (postfix): " << CYAN << *current_it << RESET
            << std::endl; // Expected: 30
  --current_it;
  std::cout << "After --: " << CYAN << *current_it << RESET
            << std::endl; // Expected: 20
  current_it--;
  std::cout << "After -- (postfix): " << CYAN << *current_it << RESET
            << std::endl; // Expected: 10
  std::cout << std::endl;

  std::cout << BOLD << MAGENTA
            << "--- Test 5: Iterators with different types (e.g., char) ---"
            << RESET << std::endl;
  MutantStack<char> char_stack;
  char_stack.push('a');
  char_stack.push('b');
  char_stack.push('c');
  std::cout << "Iterating through char_stack:" << std::endl;
  for (MutantStack<char>::iterator ch_it = char_stack.begin();
       ch_it != char_stack.end(); ++ch_it) {
    std::cout << CYAN << *ch_it << " " << RESET; // Expected: a b c
  }
  std::cout << std::endl << std::endl;

  std::cout << BOLD << MAGENTA << "--- Test 6: Comparison with std::list ---"
            << RESET << std::endl;
  std::list<int> test_list;
  test_list.push_back(5);
  test_list.push_back(3);
  test_list.push_back(5);
  test_list.push_back(737);
  test_list.push_back(0);

  std::cout << "Elements in std::list:" << std::endl;
  for (std::list<int>::iterator list_it = test_list.begin();
       list_it != test_list.end(); ++list_it) {
    std::cout << GREEN << *list_it << RESET << std::endl;
  }
  std::cout << "Comparing with MutantStack (should be the same output as Test "
               "1 iteration):"
            << std::endl;
  MutantStack<int> comparison_mstack;
  comparison_mstack.push(5);
  comparison_mstack.push(3);
  comparison_mstack.push(5);
  comparison_mstack.push(737);
  comparison_mstack.push(0);

  for (MutantStack<int>::iterator m_it = comparison_mstack.begin();
       m_it != comparison_mstack.end(); ++m_it) {
    std::cout << CYAN << *m_it << RESET << std::endl;
  }
}
