#pragma once

#include <iostream>
#include <stack>
#include <string>

class RPN {
private:
  std::stack<double> *stackarino_;

public:
  RPN();
  RPN(std::stack<double> number);
  RPN(const RPN &src);
  ~RPN();
  RPN &operator=(const RPN &src);
  void solveIt(std::string input);
};
