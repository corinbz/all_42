#include "../include/Animal.hpp"
#include <iostream>

// constructors
Animal::Animal() {
  this->type = "animal";
  std::cout << "Animal: Default constructor called\n" << std::endl;
}

Animal::Animal(const Animal &copy) {
  std::cout << "Animal: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Animal::~Animal() {
  std::cout << "Animal: class being destroyed...\n" << std::endl;
}

// copy assigment
Animal &Animal::operator=(const Animal &src) {
	if (this == &src) {
		return *this;
	}
  this->type = src.type;
  std::cout << "Animal: copy assigment operator called\n" << std::endl;
  return (*this);
}

// methods
void Animal::makeSound() const {
}

// getters
std::string Animal::getType() const { return (this->type); }
