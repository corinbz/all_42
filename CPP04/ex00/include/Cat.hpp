#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
public:
  // constructors
  Cat();
  Cat(const Cat &copy);
  // deconstructor
  ~Cat();
  // copy assigment
  Cat &operator=(const Cat &src);
  // methods
  void makeSound() const;
};
#endif // !CAT_HPP
