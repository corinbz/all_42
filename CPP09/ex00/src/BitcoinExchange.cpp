#include "../include/BitcoinExchange.hpp"
#include <stack>

RPN::RPN() {};
RPN::RPN(std::stack<double> numbers) : stackarino_(&numbers) {}
RPN::RPN(const RPN &src) { *this = src; }
RPN &RPN ::operator=(const RPN &src) {
  if (this != &src) {
    this->stackarino_ = src.stackarino_;
  }
  return *this;
}
RPN::~RPN() {};
