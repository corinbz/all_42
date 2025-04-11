#include "../include/Brain.hpp"
#include <iostream>
#include <string>

//constructors
Brain::Brain() {
	for (int i = 0; i < 100; ++i) {
		ideas[i] = "no idea " + std::to_string(i);
	}
	std::cout << "Brain: Default constructor called" << std::endl;
}

Brain::Brain(const Brain& copy) {
	for (int i = 0; i < 100; ++i) {
		ideas[i] = copy.ideas[i];
	}
	std::cout << "Brain: Copy constructor called" << std::endl;
}
Brain::~Brain() {
	std::cout << "Brain: class being destroyed...\n" <<std::endl;
}

Brain &Brain::operator=(const Brain &src) {
	if (this != &src) {
		for (int i = 0; i < 100; ++i) {
			ideas[i] = src.ideas[i];
		}
	}
	std::cout << "Brain: copy assigment operator called\n" << std::endl;
	return (*this);
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < 100) {
		ideas[index] = idea;
	}
}

std::string Brain::getIdea(int index) const {
	if (index <= 0 && index < 100) {
		return ideas[index];
	}
	return ("Invalid index");
}
