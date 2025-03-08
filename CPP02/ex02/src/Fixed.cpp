#include "../include/Fixed.hpp"
#include <cmath>
#include <iostream>

// constructors
Fixed::Fixed() {
  _fixedNum = 0;
}
Fixed::Fixed(const int val) {
  _fixedNum = val << _bits;
  // Takes an integer val, shifts it left by _bits (8),
  // effectively multiplying by 256 (2⁸), and stores it in
  // _fixedNum. This converts the integer to fixed-point
  // representation where the fractional part is 0.
}
Fixed::Fixed(const float val) {
  _fixedNum = roundf(val * (1 << _bits));
  /*
   Multiplies val by 256 (1 << 8) to scale it into fixed-point range, rounds to
  the nearest integer using roundf (from <cmath>), and stores it in _fixedNum.
  Example: If val = 3.14, val * 256 = 803.84, roundf(803.84) = 804, so _fixedNum
  = 804. This approximates 3.14 (804 / 256 ≈ 3.140625).
  */
}

Fixed::~Fixed() {}

Fixed::Fixed(const Fixed &t) {
  this->_fixedNum = t._fixedNum;
}

Fixed &Fixed::operator=(const Fixed &C) {
  // Check for self assignment
  if (this != &C) {
    this->_fixedNum = C.getRawBits();
  }
  return *this;
}

int Fixed::getRawBits(void) const {
  return (this->_fixedNum);
}

void Fixed::setRawBits(int const raw) {
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

//more operators

//Post increment/decrement
Fixed Fixed::operator++(int){
	Fixed temp = *this;
	++_fixedNum;
	return temp;
}

Fixed Fixed::operator--(int){
	Fixed temp = *this;
	--_fixedNum;
	return temp;
}

//Pre increment/decrement
Fixed& Fixed::operator++()
{
	++_fixedNum;
	return *this;
}


Fixed& Fixed::operator--()
{
	--_fixedNum;
	return *this;
}

//Comparison operators
bool Fixed::operator==(const Fixed &c) const{
	return (getRawBits() == c.getRawBits());
}


bool Fixed::operator>(const Fixed &c) const{
	return (getRawBits() > c.getRawBits());
}


bool Fixed::operator<(const Fixed &c) const {
	return (getRawBits() < c.getRawBits());
}

bool Fixed::operator>=(const Fixed &c) const{
	return (getRawBits() >= c.getRawBits());
}

bool Fixed::operator<=(const Fixed &c) const{
	return (getRawBits() <= c.getRawBits());
}

bool Fixed::operator!=(const Fixed &c) const{
	return (getRawBits() != c.getRawBits());
}

//arithmetic operators

Fixed Fixed::operator+(Fixed const& obj) const{
	Fixed res;
	res.setRawBits(getRawBits() + obj.getRawBits());
	return res;
}

Fixed Fixed::operator*(Fixed const& obj) const{
	Fixed res;
	res.setRawBits(getRawBits() * obj.getRawBits() >> _bits);
	return res;
}

Fixed Fixed::operator-(Fixed const& obj) const{
	Fixed res;
	res.setRawBits(getRawBits() - obj.getRawBits());
	return res;
}

Fixed Fixed::operator/(Fixed const& obj) const{
	Fixed res;
	res.setRawBits(getRawBits() / obj.getRawBits() >> _bits);
	return res;
}

//max and min
Fixed const &Fixed::min(Fixed const &a, Fixed const &b){
	if (a < b)
		return a;
	return b;
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b){
	if (a < b)
		return b;
	return a;
}

Fixed const &min(Fixed const &a, Fixed const &b) {
	return Fixed::min(a,b);
}

Fixed const &max(Fixed const &a, Fixed const &b) {
	return Fixed::max(a,b);
}
