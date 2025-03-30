#include "../include/ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap() {
  std::cout << "Default ScavTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) {
  this->_name = name;
  _hitpoints = 100;
  _energy_points = 50;
  _atack_damage = 20;
  std::cout << "ScavTrap constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
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
