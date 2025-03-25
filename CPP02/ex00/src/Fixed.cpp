#include "../include/Fixed.hpp"
#include <iostream>

Fixed::Fixed() {
	this->_fixedNum = 0;
	std::cout << "Constructor called" << std::endl; }
Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }
Fixed::Fixed(Fixed &t) {
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
