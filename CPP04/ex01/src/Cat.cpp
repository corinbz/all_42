#include "../include/Cat.hpp"
#include <iostream>

// constructors
Cat::Cat() : Animal() {
  this->type = "cat";
	brain = new Brain();
  std::cout << "Cat: Default constructor called\n" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy) {
	type = copy.type;
	brain = new Brain(*copy.brain);
  std::cout << "Cat: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Cat::~Cat() {
	delete brain;
	std::cout << "Cat: class being destroyed...\n" << std::endl; }

// copy assigment
Cat &Cat::operator=(const Cat &src) {
	if (this != &src) {
		Animal::operator=(src);
		delete brain;
		brain = new Brain(*src.brain);
		type = src.type;
	}
  std::cout << "Cat: copy assigment operator called\n" << std::endl;
  return (*this);
}

// methods
void Cat::makeSound() const { std::cout << "Cat: Meoow" << std::endl; }
