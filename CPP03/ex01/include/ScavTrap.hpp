#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
  //constructors
  ScavTrap();
  ScavTrap(std::string name);
  ScavTrap(const ScavTrap &copy);

  //destructor
  ~ScavTrap();
  
  //copy operator
  ScavTrap &operator=(const ScavTrap &src);
  
  //methods
  void attack(const std::string &target);
  void guardGate();
};
#endif // !SCAVTRAP_HPP
