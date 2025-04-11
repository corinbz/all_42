#include "../include/Animal.hpp"
#include "../include/Cat.hpp"
#include "../include/Dog.hpp"
#include "../include/WrongAnimal.hpp"
#include "../include/WrongCat.hpp"
#include <iostream>

int main() {
  // Animal *animal = new Animal();
  // Cat *cat = new Cat();
  // Dog *dog = new Dog();
  // std::cout << "Animal type: " << animal->getType() << "\n";
  // std::cout << "Cat type: " << cat->getType() << "\n";
  // std::cout << "Dog type: " << dog->getType() << "\n";
  // animal->makeSound();
  // cat->makeSound();
  // dog->makeSound();
  // delete animal;
  // delete cat;
  // delete dog;

	//testing wrong animal/cat
	WrongAnimal *wronganimal = new WrongAnimal();
	WrongCat *wrongcat = new WrongCat();
	std::cout << "Animal type: " << wronganimal->getType() << "\n";
  std::cout << "WrongCat type: " << wrongcat->getType() << "\n";
	wronganimal->makeSound();
	wrongcat->makeSound();
	delete wronganimal;
	delete wrongcat;


 // const Animal *constAnimal = new Animal();
 // const Animal *constCat = new Cat();
 // const Animal *constDog = new Dog();
 // std::cout << "Const Animal type: " << constAnimal->getType() << "\n";
 // std::cout << "Const Cat type: " << constCat->getType() << "\n";
 // std::cout << "Const Dog type: " << constDog->getType() << "\n";
 // constAnimal->makeSound();
 // constCat->makeSound();
 // constDog->makeSound();
 // delete constAnimal;
 // delete constCat;
 // delete constDog;


 // const int size = 3;
 // Animal *animals[size] = {new Animal(), new Cat(), new Dog()};
 // for (int i = 0; i < size; ++i) {
 //   std::cout << "Animal " << i << " type: " << animals[i]->getType() <<
 // "\n";
 //   animals[i]->makeSound();
 // }
 // for (int i = 0; i < size; ++i) {
 //   delete animals[i];
 // }
 //
  return 0;
}
