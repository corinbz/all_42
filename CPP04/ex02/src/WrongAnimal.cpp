
#include "../include/WrongAnimal.hpp"
#include <iostream>

// constructors
WrongAnimal::WrongAnimal() {
  this->type = "wronganimal";
  std::cout << "WrongAnimal: Default constructor called\n" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &copy) {
  std::cout << "WrongAnimal: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
WrongAnimal::~WrongAnimal() {
  std::cout << "WrongAnimal: class being destroyed...\n" << std::endl;
}

// copy assigment
WrongAnimal &WrongAnimal::operator=(const WrongAnimal &src) {
	std::cout << "WrongAnimal: copy assigment operator called\n" << std::endl;
	if(this == &src) {
		return *this;
	}
  this->type = src.type;
  return (*this);
}

// methods
void WrongAnimal::makeSound() const {
  std::cout << "WrongAnimal: makes a generic sound! What is this beast?"
            << std::endl;
}

// getters
std::string WrongAnimal::getType() const { return (this->type); }
