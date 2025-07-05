#include "../include/Span.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

Span::Span(unsigned int size) : span_(new std::vector<int>), size_(size) {};

Span &Span::operator=(const Span &src) {
  if (this != &src) {
    this->size_ = src.size_;
  }
  return (*this);
}

Span::Span(const Span &src) { *this = src; }

Span::~Span() { delete span_; };

// custom functions

void Span::addNumber(int num) {
  if (span_->size() < size_) {
    span_->push_back(num);
    std::cout << "Number " << num << " added to the span." << std::endl;
  } else {
    throw std::out_of_range("Span is full.");
  }
};

int Span::shortestSpan() {
  if (span_->size() < 2) {
    throw std::runtime_error(
        "Cannot find shortest span; At least 2 numbers needed.");
  }
  std::sort(span_->begin(), span_->end());
  // set minSpan to max int;
  int minSpan = std::numeric_limits<int>::max();
  for (size_t i = 1; i < span_->size(); ++i) {
    int currentDiff = span_->at(i) - span_->at(i - 1);
    minSpan = std::min(minSpan, currentDiff);
  }
  return minSpan;
}

int Span::longestSpan() {
  if (span_->size() < 2) {
    throw std::runtime_error(
        "Cannot find longestSpan span; At least 2 numbers needed.");
  }
  std::sort(span_->begin(), span_->end());
  int low = *span_->begin();
  // reverse sort
  std::sort(span_->rbegin(), span_->rend());
  int high = *span_->begin();
  return (high - low);
}

void Span::populate() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist{1, 100000};
  span_->resize(size_);
  std::generate(span_->begin(), span_->end(), [&]() { return dist(gen); });
}
