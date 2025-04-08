#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
public:
  // constructors
  Dog();
  Dog(const Dog &copy);
  // deconstructor
  ~Dog();
  // copy assigment
  Dog &operator=(const Dog &src);
  // methods
  void makeSound() const;
};
#endif // !DOG_HPP
