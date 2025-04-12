
#include "../include/WrongCat.hpp"
#include <iostream>

// constructors
WrongCat::WrongCat() : WrongAnimal() {
  this->type = "cat";
  std::cout << "WrongCat: Default constructor called\n" << std::endl;
}

WrongCat::WrongCat(const WrongCat &copy) : WrongAnimal(copy) {
	type = copy.type;
  std::cout << "WrongCat: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
WrongCat::~WrongCat() { std::cout << "WrongCat: class being destroyed...\n" << std::endl; }

// copy assigment
WrongCat &WrongCat::operator=(const WrongCat &src) {
  this->type = src.type;
  std::cout << "WrongCat: copy assigment operator called\n" << std::endl;
  return (*this);
}

// methods
void WrongCat::makeSound() const { std::cout << "WrongCat: Meoow" << std::endl; }
