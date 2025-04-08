#include "../include/Cat.hpp"
#include <iostream>

// constructors
Cat::Cat() : Animal() {
  this->type = "cat";
  std::cout << "Cat: Default constructor called\n" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy) {
  std::cout << "Cat: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Cat::~Cat() { std::cout << "Cat: class being destroyed...\n" << std::endl; }

// copy assigment
Cat &Cat::operator=(const Cat &src) {
  this->type = src.type;
  std::cout << "Cat: copy assigment operator called\n" << std::endl;
  return (*this);
}

// methods
void Cat::makeSound() const { std::cout << "Cat: Meoow" << std::endl; }
