#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include <iostream>

int main() {
    std::cout << "=== Creating Animal Array ===\n";
    const int size = 4;
    Animal* animals[size];
	//fill first half with dogs, second half with cats
    for (int i = 0; i < size / 2; ++i) {
        animals[i] = new Dog();
    }
    for (int i = size / 2; i < size; ++i) {
        animals[i] = new Cat();
    }

    std::cout << "\n=== Testing Sounds ===\n";
    for (int i = 0; i < size; ++i) {
        animals[i]->makeSound();
    }

    std::cout << "\n=== Testing Deep Copy ===\n";
    Dog originalDog;
    Dog copiedDog(originalDog);
    originalDog.makeSound();
    copiedDog.makeSound();
    copiedDog = originalDog;
    std::cout << "After assignment:\n";
    originalDog.makeSound();
    copiedDog.makeSound();

    Cat originalCat;
    Cat copiedCat(originalCat);
    originalCat.makeSound();
    copiedCat.makeSound();
    copiedCat = originalCat;
    std::cout << "After assignment:\n";
    originalCat.makeSound();
    copiedCat.makeSound();

    std::cout << "\n=== Deleting Animal Array ===\n";
    for (int i = 0; i < size; ++i) {
        delete animals[i];
    }

    return 0;
}
