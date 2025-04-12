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
  virtual ~Cat();
  // copy assigment
  Cat &operator=(const Cat &src);
  // methods
  void makeSound() const override;
	//getter
	void getIdeas() const;
	//setter
	void setIdea(int index, std::string idea);
};
#endif // !CAT_HPP
