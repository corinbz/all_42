#pragma once
#include <fstream>
#include <map>
#include <sstream>

class Date {
private:
  int year, month, day;
  // date validation for string

public:
  Date();
  Date(std::string dateStr);
  Date(int y, int m, int d);
  Date &operator=(const Date &src);
  Date(const Date &src);
  ~Date();
  bool operator<(const Date &other) const;
  std::ostream &output(std::ostream &COUT) const;
  std::string toString() const;
};

class BtcConvertor {
private:
  std::map<Date, double> conversionRates;
  std::map<Date, double> input;

  void setConversionRates();
  void setInput(std::string &input);

public:
  BtcConvertor();
  BtcConvertor(std::string filePath);
  /* BtcConvertor &operator=(const BtcConvertor &src); */
  /* BtcConvertor(const BtcConvertor &src); */
  ~BtcConvertor();
};

std::ostream &operator<<(std::ostream &COUT, const Date &src);
