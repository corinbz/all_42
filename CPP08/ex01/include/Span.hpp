#pragma once
#include <vector>

class Span {
private:
  std::vector<int> *span_;
  unsigned int size_ = 0;
  int &operator[](unsigned int index);

public:
  Span(unsigned int size);
  Span(const Span &src);
  Span &operator=(const Span &src);
  ~Span();
  void addNumber(int num);
  void populate();
  int shortestSpan();
  int longestSpan();
};
