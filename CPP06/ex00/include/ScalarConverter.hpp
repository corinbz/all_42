#pragma once
#include <string>

#define SPECIAL 0
#define CHAR 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4
#define INVALID -1

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

class ScalarConverter {
private:
  // build and destroy
  ScalarConverter();
  ScalarConverter(const ScalarConverter &copy);
  ScalarConverter &operator=(const ScalarConverter &src);
  virtual ~ScalarConverter() = 0;

  // type detection
  static bool isPseudoLiteral(const std::string &str, double &value);
  static bool isInt(const std::string &str);
  static bool isDouble(const std::string &str);
  static bool isFloat(const std::string &str);
  static bool isChar(const std::string &str);

  // printing helpers
  static void printChar(double value, bool invalid);
  static void printInt(double value, bool invalid);
  static void printFloat(double value, bool invalid, const std::string &str);
  static void printDouble(double value, bool invalid, const std::string &str);

public:
  static void convert(const std::string &str);
};
