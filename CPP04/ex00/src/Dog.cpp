
#include "../include/Dog.hpp"
#include <iostream>

// constructors
Dog::Dog() : Animal() {
  this->type = "dog";
  std::cout << "Dog: Default constructor called\n" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy) {
	type = copy.type;
  std::cout << "Dog: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Dog::~Dog() { std::cout << "Dog: class being destroyed...\n" << std::endl; }

// copy assigment
Dog &Dog::operator=(const Dog &src) {
	std::cout << "Dog: copy assigment operator called\n" << std::endl;
	if(this == &src) {
		return *this;
	}
  this->type = src.type;
  return (*this);
}

// methods
void Dog::makeSound() const { std::cout << "Dog: Woof" << std::endl; }
