#include "../include/ScalarConverter.hpp"
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

bool ScalarConverter::isPseudoLiteral(const std::string &str, double &value) {
  if (str == "nan" || str == "nanf") {
    value = std::strtod("nan", NULL);
    return true;
  }
  if (str == "+inf" || str == "inf" || str == "+inff" || str == "inff") {
    value = HUGE_VAL;
    return true;
  }
  if (str == "-inf" || str == "-inff") {
    value = -HUGE_VAL;
    return true;
  }
  return false;
}

bool ScalarConverter::isChar(const std::string &str) {
  return (str.length() == 1 && !std::isdigit(str[0]));
}

bool ScalarConverter::isInt(const std::string &str) {
  char *end;
  errno = 0;
  // convert to c style string, provide char* to
  // store end of string, last parameter is the base
  long val = std::strtol(str.c_str(), &end, 10);
  return (*end == '\0' && val >= INT_MIN && val <= INT_MAX);
}

bool ScalarConverter::isFloat(const std::string &str) {
  if (str == "-inff" || str == "+inff" || str == "nanf")
    return true;
  if (str.empty() || str[str.length() - 1] != 'f')
    return false;
  char *end;
  errno = 0;
  std::strtof(str.c_str(), &end);
  return (*end == 'f' && *(end + 1) == '\0' && errno == 0);
}

bool ScalarConverter::isDouble(const std::string &str) {
  if (str == "-inf" || str == "+inf" || str == "nan")
    return true;
  char *end;
  errno = 0;
  std::strtod(str.c_str(), &end);
  return (*end == '\0' && errno == 0);
}

void ScalarConverter::printChar(double value, bool invalid) {
  std::cout << "char: ";
  if (invalid || std::isnan(value) || std::isinf(value) || value < CHAR_MIN ||
      value > CHAR_MAX) {
    std::cout << "invalid" << std::endl;
  } else if (value < 32 || value >= 127) {
    std::cout << "non displayable" << std::endl;
  } else {
    std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
  }
}

void ScalarConverter::printInt(double value, bool invalid) {
  std::cout << "int: ";
  if (invalid || std::isnan(value) || std::isinf(value) || value < INT_MIN ||
      value > INT_MAX) {
    std::cout << "invalid" << std::endl;
  } else {
    std::cout << static_cast<int>(value) << std::endl;
  }
}

void ScalarConverter::printFloat(double value, bool invalid,
                                 const std::string &str) {
  std::cout << "float: ";
  if (invalid) {
    std::cout << "invalid" << std::endl;
  } else if (str == "-inff" || str == "+inff" || str == "nanf") {
    std::cout << str << std::endl;
  } else if (std::isnan(value)) {
    std::cout << "nanf" << std::endl;
  } else if (std::isinf(value)) {
    std::cout << (value < 0 ? "-inff" : "+inff") << std::endl;
  } else {
    std::cout << static_cast<float>(value);
    if (static_cast<long>(value) == value)
      std::cout << ".0";
    std::cout << "f" << std::endl;
  }
}

void ScalarConverter::printDouble(double value, bool invalid,
                                  const std::string &str) {
  std::cout << "double: ";
  if (invalid) {
    std::cout << "invalid" << std::endl;
  } else if (str == "inf" || str == "+inf" || str == "nan") {
    std::cout << str << std::endl;
  } else if (std::isnan(value)) {
    std::cout << "nan" << std::endl;
  } else if (std::isinf(value)) {
    std::cout << (value < 0 ? "-inf" : "+inf") << std::endl;
  } else {
    std::cout << value;
    if (static_cast<long>(value) == value)
      std::cout << ".0";
    std::cout << std::endl;
  }
}

void ScalarConverter::convert(const std::string &str) {
  double value = 0.0;
  bool invalid = false;

  if (isPseudoLiteral(str, value)) {
  } else if (isChar(str)) {
    value = static_cast<double>(str[0]);
  } else if (isInt(str)) {
    value = static_cast<double>(std::atoi(str.c_str()));
  } else if (isFloat(str)) {
    value = std::strtof(str.c_str(), NULL);
  } else if (isDouble(str)) {
    value = std::strtod(str.c_str(), NULL);
  } else {
    invalid = true;
  }

  printChar(value, invalid);
  printInt(value, invalid);
  printFloat(value, invalid, str);
  printDouble(value, invalid, str);
}
