#pragma once
#include <stack>
#include <string>
#include <unordered_set>

class RPN {
private:
  std::stack<double> numbers;
  const std::unordered_set<char> valid_operators = {'+', '-', '*', '/'};

  double performOperation(double a, double b, char op) const;
  bool isOperator(char c) const;

public:
  RPN();
  ~RPN();
  RPN(const RPN &src);
  RPN &operator=(const RPN &src);

  double calculate(const std::string &input);
};
