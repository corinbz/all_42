#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include <iostream>

//A deep copy has it's allocated memory
//A shallow copy is just a new pointer to the original data
int main() {
	//    std::cout << "=== Creating Animal Array ===\n";
	//    const int size = 4;
	//    Animal* animals[size];
	// //fill first half with dogs, second half with cats
	//    for (int i = 0; i < size / 2; ++i) {
	//        animals[i] = new Dog();
	//    }
	//    for (int i = size / 2; i < size; ++i) {
	//        animals[i] = new Cat();
	//    }
	//
	//    std::cout << "\n=== Testing Sounds ===\n";
	//    for (int i = 0; i < size; ++i) {
	//        animals[i]->makeSound();
	//    }
	// 	for (int i = 0; i < size; ++i) {
	// 					delete animals[i];
	// 			}

    std::cout << "\n=== Testing Deep Copy ===\n";
    Dog *originalDog = new Dog();
		originalDog->setIdea(1, "jump around");
		originalDog->setIdea(2, "run around tail");
		originalDog->getIdeas();
    originalDog->makeSound();
		Dog *copiedDog = new Dog(*originalDog);
    copiedDog->makeSound();
		copiedDog->setIdea(1, "just sit");
		copiedDog->getIdeas();
    originalDog->makeSound();
    copiedDog->makeSound();
		delete originalDog;
		delete copiedDog;

    Cat *originalCat = new Cat();
		originalCat->setIdea(1, "lick fur");
		originalCat->setIdea(2, "eat fish");
		originalCat->getIdeas();
    originalCat->makeSound();
		Cat *copiedCat = new Cat(*originalCat);
    copiedCat->makeSound();
		copiedCat->setIdea(1, "sleep");
		copiedCat->getIdeas();

    originalCat->makeSound();
    copiedCat->makeSound();
		delete originalCat;
		delete copiedCat;
    return 0;
}
