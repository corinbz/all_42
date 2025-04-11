#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
private:
	Brain *brain;
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
