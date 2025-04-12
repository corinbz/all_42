#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include <type_traits>
#include <iostream>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

int main() {
    std::cout << CYAN << "=== Test 1: Attempt Instantiation ===" << RESET << "\n";
    // This would fail if uncommented:
    // Animal animal("generic");  // error: cannot declare variable ‘animal’ to be of abstract type ‘Animal’
    
    Dog dog;
    Cat cat;
    std::cout << BLUE << "Created Dog: " << dog.getType() << RESET << "\n";
    std::cout << BLUE << "Created Cat: " << cat.getType() << RESET << "\n";

    std::cout << CYAN << "\n=== Test 2: Compile-Time Check ===" << RESET << "\n";
    static_assert(std::is_abstract<Animal>::value, "Animal must be abstract");// type_traits header contains is_abstract function
    static_assert(!std::is_abstract<Dog>::value, "Dog must not be abstract");  //value is a bool
    static_assert(!std::is_abstract<Cat>::value, "Cat must not be abstract");
    std::cout << MAGENTA << "Animal is " << (std::is_abstract<Animal>::value ? "abstract" : "concrete") << RESET << "\n";
    std::cout << MAGENTA << "Dog is " << (std::is_abstract<Dog>::value ? "abstract" : "concrete") << RESET << "\n";
    std::cout << MAGENTA << "Cat is " << (std::is_abstract<Cat>::value ? "abstract" : "concrete") << RESET << "\n";

    std::cout << CYAN << "\n=== Test 3: Polymorphic Array ===" << RESET << "\n";
    Animal* animals[4] = { new Dog(), new Dog(), new Cat(), new Cat() };
    for (int i = 0; i < 4; ++i) {
        std::cout << YELLOW;
        animals[i]->makeSound();
        std::cout << RESET;
    }
    for (int i = 0; i < 4; ++i) {
        delete animals[i];  // Virtual destructor ensures correct cleanup
    }

    return 0;
}
