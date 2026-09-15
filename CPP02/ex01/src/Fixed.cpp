#include "../include/Fixed.hpp"
#include <cmath>
#include <iostream>

// constructors
Fixed::Fixed() {
  std::cout << "Constructor called" << std::endl;
  _fixedNum = 0;
}
Fixed::Fixed(const int val) {
  std::cout << "Int constructor called" << std::endl;
  _fixedNum = val << _bits;
  // Takes an integer val, shifts it left by _bits (8),
  // effectively multiplying by 256 (2⁸), and stores it in
  // _fixedNum. This converts the integer to fixed-point
  // representation where the fractional part is 0.
}
Fixed::Fixed(const float val) {
  std::cout << "Float constructor called" << std::endl;
  _fixedNum = roundf(val * (1 << _bits));
  /*
   Multiplies val by 256 (1 << 8) to scale it into fixed-point range, rounds to
  the nearest integer using roundf (from <cmath>), and stores it in _fixedNum.
  Example: If val = 3.14, val * 256 = 803.84, roundf(803.84) = 804, so _fixedNum
  = 804. This approximates 3.14 (804 / 256 ≈ 3.140625).
  */
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed::Fixed(const Fixed &t) {
  this->_fixedNum = t._fixedNum;
  std::cout << "Copy constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &C) {
  std::cout << "Copy assigment operator called" << std::endl;
  // Check for self assignment
  if (this != &C) {
    this->_fixedNum = C.getRawBits();
  }
  return *this;
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits method called" << std::endl;
  return (this->_fixedNum);
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits method called" << std::endl;
  this->_fixedNum = raw;
}

float Fixed::toFloat(void) const {
  float res;
  res = static_cast<float>(_fixedNum) / (1 << _bits);
  return res;
}

int Fixed::toInt(void) const {
  int res;
  res = _fixedNum >> _bits;
  return res;
}

std::ostream &Fixed::output(std::ostream &os) const {
  os << toFloat();
  return os;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fp) {
  os << fp.toFloat();
  return (os);
}
