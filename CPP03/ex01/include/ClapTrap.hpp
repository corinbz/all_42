#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <cstdint>
#include <string>

class ClapTrap {
protected:
  std::string _name;
  unsigned int _hitpoints;
  unsigned int _energy_points;
  unsigned int _atack_damage;

public:
  // constructors
  ClapTrap();
  ClapTrap(const ClapTrap &copy);
  ClapTrap(std::string name);

  // Deconstructor
  ~ClapTrap();

  // Copy operator
  ClapTrap &operator=(const ClapTrap &src);

  // Methods
  void attack(const std::string &target);
  void takeDamage(unsigned int amount);
  void beRepaired(unsigned int amount);
};

#endif
