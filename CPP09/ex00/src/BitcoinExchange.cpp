#include "../include/BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

// Date class

// helper functions for date validation

static bool isValidDateFormat(const std::string &dateStr) {
  // check if string matches the format YYYY-MM-DD
  std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
  return std::regex_match(dateStr, dateRegex);
}

static bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static bool isValidDate(int year, int month, int day) {
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isLeapYear(year)) {
    daysInMonth[1] = 29;
  }
  return day <= daysInMonth[month - 1];
}

Date::Date() : year(0), month(0), day(0) {};
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {};
Date::Date(std::string dateStr) {
  if (!isValidDateFormat(dateStr)) {
    throw std::invalid_argument("(Regex) Invalid date format(YYYY-MM-DD) : " +
                                dateStr);
  }

  std::istringstream ss(dateStr);
  std::string yearStr, monthStr, dayStr;
  if (!std::getline(ss, yearStr, '-') || !std::getline(ss, monthStr, '-') ||
      !std::getline(ss, dayStr, '-'))
    throw std::invalid_argument("Invalid date format(YYYY-MM-DD) : " + dateStr);
  year = std::stoi(yearStr);
  month = std::stoi(monthStr);
  day = std::stoi(dayStr);
  if (!isValidDate(year, month, day))
    throw std::invalid_argument("Invalid date values : " + dateStr);
}
Date::~Date() {};
Date &Date::operator=(const Date &src) {
  if (this != &src) {
    this->year = src.year;
    this->month = src.month;
    this->day = src.day;
  }
  return (*this);
}
Date::Date(const Date &src) {
  this->year = src.year;
  this->month = src.month;
  this->day = src.day;
}

bool Date::operator<(const Date &other) const {
  if (this->year != other.year)
    return this->year < other.year;
  if (this->month != other.month)
    return this->month < other.month;
  if (this->day != other.day)
    return this->day < other.day;
  return false;
}

std::string Date::toString() const {
  std::ostringstream oss;
  oss << this->year << "-" << (this->month < 10 ? "0" : "") << this->month
      << "-" << (this->day < 10 ? "0" : "") << this->day;
  return oss.str();
}
std::ostream &Date::output(std::ostream &COUT) const {
  COUT << this->toString();
  return COUT;
}

// BtcConvertor class

BtcConvertor::BtcConvertor() {};

BtcConvertor &BtcConvertor::operator=(const BtcConvertor &src) {
  if (this != &src) {
    this->conversionRates = src.conversionRates;
    this->input = src.input;
  }
  return (*this);
}

BtcConvertor::BtcConvertor(const BtcConvertor &src) {
  this->conversionRates = src.conversionRates;
  this->input = src.input;
}

void BtcConvertor::setConversionRates() {
  std::string filePath = "data.csv";
  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file : " + filePath);
  }
  std::string line;
  // skip first line
  std::getline(file, line);
  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    size_t commaPos = line.find(',');
    std::string dateStr = line.substr(0, commaPos);
    std::string rateStr = line.substr(commaPos + 1);
    // std::cout << rateStr << std::endl;
    Date date(dateStr);
    double rate = std::stod(rateStr);

    conversionRates[date] = rate;
    /* std::cout << date << " has conversion rate:" << conversionRates[date] */
    /*           << std::endl; */
  }
  file.close();
}

void BtcConvertor::setInput(std::string &inputFile) {
  std::ifstream file(inputFile);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file : " + inputFile);
  }
  std::string line;
  // skip first line
  std::getline(file, line);
  std::string datePrev;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    size_t separatorPos = line.find('|');
    std::string dateStr = line.substr(0, separatorPos);
    datePrev = dateStr;
    std::string valueStr = line.substr(separatorPos + 1);
    /* std::cout << "date : " << dateStr << "\nvalue : " << valueStr <<
     * std::endl; */
    double value = std::stod(valueStr);
    input[dateStr].push_back(value);
  }
  file.close();
}

BtcConvertor::BtcConvertor(std::string filePath) {
  try {
    setConversionRates();
    setInput(filePath);
    printOutput();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
};

void BtcConvertor::printOutput() const {
  for (const auto &pair : input) {
    {
      try {
        const Date inputDate(pair.first);
        const std::list<double> &values = pair.second;

        for (double inputValue : values) {
          try {
            if (inputValue < 0) {
              throw std::runtime_error("Not a positive number.");
            }
            if (inputValue >= 1000) {
              throw std::runtime_error("Number too large.");
            }
            double rate = 0;
            auto exactDate = conversionRates.find(inputDate);
            if (exactDate != conversionRates.end()) {
              rate = exactDate->second;
            } else {
              auto prevDate = conversionRates.upper_bound(inputDate);
              if (prevDate != conversionRates.begin()) {
                --prevDate;
                rate = prevDate->second;
              } else {
                throw std::runtime_error("Bad input : " + inputDate.toString());
              }
            }
            double res = inputValue * rate;
            std::cout << inputDate << " => " << inputValue << " = " << res
                      << std::endl;
          } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
          }
        }
      } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
  }
}

BtcConvertor::~BtcConvertor() {};

std::ostream &operator<<(std::ostream &COUT, const Date &src) {
  COUT << std::fixed << std::setprecision(2) << src.toString();
  return COUT;
}
