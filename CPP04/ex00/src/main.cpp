#include "../include/Animal.hpp"
#include "../include/Cat.hpp"
#include "../include/Dog.hpp"
#include <iostream>

int main() {
  std::cout << "=== Test 1: Basic Object Creation ===\n";
  Animal *animal = new Animal();
  Cat *cat = new Cat();
  Dog *dog = new Dog();
  std::cout << "Animal type: " << animal->getType() << "\n";
  std::cout << "Cat type: " << cat->getType() << "\n";
  std::cout << "Dog type: " << dog->getType() << "\n";
  animal->makeSound();
  cat->makeSound();
  dog->makeSound();
  delete animal;
  delete cat;
  delete dog;

  /* std::cout << "\n=== Test 2: Const Pointers and Polymorphism ===\n"; */
  /* const Animal *constAnimal = new Animal(); */
  /* const Animal *constCat = new Cat(); */
  /* const Animal *constDog = new Dog(); */
  /* std::cout << "Const Animal type: " << constAnimal->getType() << "\n"; */
  /* std::cout << "Const Cat type: " << constCat->getType() << "\n"; */
  /* std::cout << "Const Dog type: " << constDog->getType() << "\n"; */
  /* constAnimal->makeSound(); // Should call Animal::makeSound */
  /* constCat->makeSound();    // Should call Cat::makeSound (virtual) */
  /* constDog->makeSound();    // Should call Dog::makeSound (virtual) */
  /* delete constAnimal; */
  /* delete constCat; */
  /* delete constDog; */
  /**/
  /* std::cout << "\n=== Test 3: Array of Animals (Polymorphism) ===\n"; */
  /* const int size = 3; */
  /* Animal *animals[size] = {new Animal(), new Cat(), new Dog()}; */
  /* for (int i = 0; i < size; ++i) { */
  /*   std::cout << "Animal " << i << " type: " << animals[i]->getType() <<
   * "\n"; */
  /*   animals[i]->makeSound(); */
  /* } */
  /* for (int i = 0; i < size; ++i) { */
  /*   delete animals[i]; */
  /* } */

  return 0;
}
