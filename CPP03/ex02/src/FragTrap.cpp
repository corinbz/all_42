#include "../include/FragTrap.hpp"
#include <iostream>

// constructors
FragTrap::FragTrap() : ClapTrap("default") {
	_hitpoints = 100;
	_energy_points = 100;
	_atack_damage = 30;
  std::cout << "FragTrap default constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	_hitpoints = 100;
	_energy_points = 100;
	_atack_damage = 30;
  std::cout << "FragTrap named constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy) {
  _hitpoints = copy._hitpoints;
  _energy_points = copy._energy_points;
  _atack_damage = copy._atack_damage;
  _name = copy._name;
  std::cout << "FragTrap copy assigment operator called" << std::endl;
}

// destructor
FragTrap::~FragTrap() {
  std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void) {
  std::cout << "FragTrap " << _name << " highfives everyone! BOOM!\n"
            << std::endl;
}
