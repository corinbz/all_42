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

  //more operator overloading
  Fixed operator++(int);
  Fixed operator--(int);
  Fixed& operator++();
  Fixed& operator--();

	//comparison operators overloading
	bool operator==(const Fixed &c) const;
	bool operator>(const Fixed &c) const;
	bool operator<(const Fixed &c) const;
	bool operator>=(const Fixed &c) const;
	bool operator<=(const Fixed &c) const;
	bool operator!=(const Fixed &c) const;

	//arithmetic operators
	Fixed operator+(Fixed const& obj) const;
	Fixed operator-(Fixed const& obj) const;
	Fixed operator*(Fixed const& obj) const;
	Fixed operator/(Fixed const& obj) const;

	//max and min
	const static Fixed &min(Fixed const &a, Fixed const &b);
	const static Fixed &max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &os, const Fixed &fp);
Fixed const		&min(Fixed const &a, Fixed const &b);
Fixed const		&max(Fixed const &a, Fixed const &b);
#endif // !FIXED_HPP
