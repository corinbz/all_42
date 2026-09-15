#include "../include/ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap() : ClapTrap("noname") {
	_hitpoints = 100;
	_energy_points = 50;
	_atack_damage = 20;
  std::cout << "Default ScavTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	_hitpoints = 100;
	_energy_points = 50;
	_atack_damage = 20;
  std::cout << "ScavTrap constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy) {
  std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src) {
	std::cout << "ScavTrap copy assigment operator called\n" << std::endl;
  if (this != &src) {
    ClapTrap::operator=(src);
	_name = src._name;
	_hitpoints = src._hitpoints;
	_energy_points = src._energy_points;
	_atack_damage = src._atack_damage;
  }
  return *this;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
  if (!_energy_points) {
    std::cout << "ScavTrap energy depleted!\n" << std::endl;
    return;
  }
  if (!_hitpoints) {
    std::cout << "Not enought hp. Cannot attack!\n" << std::endl;
    return;
  }
  std::cout << "ScavTrap " << _name << " atacks " << target << ",causing "
            << _atack_damage << " points of damage!" << std::endl;
  _energy_points--;
  std::cout << "Energy points remaining: " << _energy_points << "\n"
            << std::endl;
}

void ScavTrap::guardGate() {
  std::cout << _name << " is now guardian of the gate. You shall not pass!\n"
            << std::endl;
}
