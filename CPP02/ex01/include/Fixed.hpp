#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>
class Fixed {
private:
  int _fixedNum;
  static const int _bits = 8;

public:
  Fixed();
  Fixed(const int val);
  Fixed(const float val);
  ~Fixed();
  // copy constructor
  Fixed(const Fixed &t);
  // assignment operator overloading
  Fixed &operator=(const Fixed &C);
  int getRawBits(void) const;
  void setRawBits(int const raw);
  float toFloat(void) const;
  int toInt(void) const;
  std::ostream &output(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Fixed &fp);
#endif // !FIXED_HPP
