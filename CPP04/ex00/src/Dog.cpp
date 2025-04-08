
#include "../include/Dog.hpp"
#include <iostream>

// constructors
Dog::Dog() : Animal() {
  this->type = "dog";
  std::cout << "Dog: Default constructor called\n" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy) {
  std::cout << "Dog: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Dog::~Dog() { std::cout << "Dog: class being destroyed...\n" << std::endl; }

// copy assigment
Dog &Dog::operator=(const Dog &src) {
  this->type = src.type;
  std::cout << "Dog: copy assigment operator called\n" << std::endl;
  return (*this);
}

// methods
void Dog::makeSound() const { std::cout << "Dog: Woof" << std::endl; }
