#pragma once
#include <stack>

template <class T>

class MutantStack : public std::stack<T> {
private:
  std::stack<T> stack;

public:
  typedef typename std::stack<T>::container_type::iterator iterator;
  MutantStack() : std::stack<T>() {};
  MutantStack(MutantStack const &src) : std::stack<T>(src) { *this = src; };
  MutantStack &operator=(MutantStack const &src) {
    std::stack<T>::operator=(src);
    return (*this);
  };
  ~MutantStack() {};
  iterator begin() { return this->c.begin(); }
  iterator end() { return this->c.end(); }
};
