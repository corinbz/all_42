#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
  public:
    //constructors
    FragTrap();
    FragTrap(std::string name);
    FragTrap(const FragTrap &copy);
    //copy operator
    FragTrap &operator=(const FragTrap &src);
    //deconstructors
    ~FragTrap();

    //custom method
    void highFivesGuys(void);
};

#endif