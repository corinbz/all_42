#include "../include/Cat.hpp"
#include <iostream>

// constructors
Cat::Cat() : Animal() {
  this->type = "cat";
  std::cout << "Cat: Default constructor called\n" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy) {
	type = copy.type;
  std::cout << "Cat: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Cat::~Cat() { std::cout << "Cat: class being destroyed...\n" << std::endl; }

// copy assigment
Cat &Cat::operator=(const Cat &src) {
	std::cout << "Cat: copy assigment operator called\n" << std::endl;
	if(this == &src) {
		return *this;
	}
  this->type = src.type;
  return (*this);
}

// methods
void Cat::makeSound() const { std::cout << "Cat: Meoow" << std::endl; }
