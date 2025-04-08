#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
protected:
  std::string type;

public:
  // constructors
  Animal();
  Animal(const Animal &copy);
  // deconstructor
  virtual ~Animal();
  // copy assigment
  Animal &operator=(const Animal &src);
  // methods
  virtual void makeSound() const;
  // getters
  std::string getType() const;
};

#endif // ANIMAL_HPP
