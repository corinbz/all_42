#include "../include/RPN.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>

RPN::RPN() {};

RPN::~RPN() {};

RPN &RPN::operator=(const RPN &src) {
  if (this != &src) {
    this->numbers = src.numbers;
  }
  return (*this);
}
RPN::RPN(const RPN &src) { *this = src; }

bool RPN::isOperator(char c) const {
  return valid_operators.find(c) != valid_operators.end();
}

double RPN::performOperation(double a, double b, char op) const {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    if (b == 0) {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  default:
    throw std::runtime_error("Invalid operator");
  }
};

double RPN::calculate(const std::string &input) {
  while (!numbers.empty())
    numbers.pop();
  std::istringstream iss(input);
  std::string token;

  while (iss >> token) {
    if (token.length() == 1 && isOperator(token[0])) {
      if (numbers.size() < 2) {
        throw std::runtime_error(
            "Need at least 2 numbers to perform calculation");
      }
      double b = numbers.top();
      // std::cout << "poping " << b << std::endl;
      numbers.pop();
      double a = numbers.top();
      numbers.pop();
      // std::cout << "poping " << a << std::endl;

      double result = performOperation(a, b, token[0]);
      numbers.push(result);
      // std::cout << "Applied " << token << ": " << a << " " << token << " " <<
      // b
      //           << " = " << result << std::endl;
    } else {
      try {
        double num = std::stod(token);
        numbers.push(num);
        // std::cout << "pushed " << num << " to stack" << std::endl;
      } catch (const std::exception &) {
        throw std::runtime_error("Invalid token: " + token);
      }
    }
  }
  // std::cout << numbers.top() << std::endl;
  // numbers.pop();
  // std::cout << numbers.top() << std::endl;
  if (numbers.size() != 1) {
    throw std::runtime_error("Stack should contain one result");
  }
  return numbers.top();
};
