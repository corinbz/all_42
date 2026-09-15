
#include "../include/Dog.hpp"
#include <iostream>

// constructors
Dog::Dog() : Animal() {
  this->type = "dog";
	brain = new Brain();
  std::cout << "Dog: Default constructor called\n" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy) {
	type = copy.type;
	brain = new Brain(*copy.brain);
  std::cout << "Dog: Copy constructor called\n" << std::endl;
  *this = copy;
}

// deconstructor
Dog::~Dog() {
	delete brain;
	std::cout << "Dog: class being destroyed...\n" << std::endl; }

// copy assigment
Dog &Dog::operator=(const Dog &src) {
	std::cout << "Dog: copy assigment operator called\n" << std::endl;
	if (this != &src) {
		Animal::operator=(src);
		delete brain;
		brain = new Brain(*src.brain);
		type = src.type;
	}
  return (*this);
}

// methods
void Dog::makeSound() const { std::cout << "Dog: Woof" << std::endl; }

void Dog::getIdeas() const {
	for (int i = 0; i < 5; i++)
		std::cout << "Idea " << i << " for dog is: " << brain->getIdea(i) << " at adress " << brain->getIdeaAdress(i) << std::endl;
}

void Dog::setIdea(int index, std::string idea)
{
	this->brain->setIdea(index, idea);
}
