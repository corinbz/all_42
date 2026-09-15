#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
protected:
  std::string type;

public:
  // constructors
  WrongAnimal();
  WrongAnimal(const WrongAnimal &copy);
  // deconstructor
  virtual ~WrongAnimal();
  // copy assigment
  WrongAnimal &operator=(const WrongAnimal &src);
  // methods
  void makeSound() const;
  // getters
  std::string getType() const;
};
#endif // !WRONGANIMAL_HPP
