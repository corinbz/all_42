
#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
  // constructors
  WrongCat();
  WrongCat(const WrongCat &copy);
  // deconstructor
  ~WrongCat();
  // copy assigment
  WrongCat &operator=(const WrongCat &src);
  // methods
  void makeSound() const;
};
#endif // !WRONGCAT_HPP
