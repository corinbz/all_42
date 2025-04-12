#include "../include/ClapTrap.hpp"
#include <iostream>

// Constructors
ClapTrap::ClapTrap() {
  this->_name = "default";
  this->_hitpoints = 100;
  this->_energy_points = 50;
  this->_atack_damage = 20;
  std::cout << "Default ClapTrap constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy) {
  std::cout << "ClapTrap copy constructor called" << std::endl;
  *this = copy;
}

ClapTrap::ClapTrap(std::string name) {
  this->_name = name;
  this->_hitpoints = 100;
  this->_energy_points = 50;
  this->_atack_damage = 20;
  std::cout << "Default named ClapTrap constructor called" << std::endl;
  std::cout << "Hitpoints: " << _hitpoints << std::endl;
  std::cout << "Energy points: " << _energy_points << std::endl;
  std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

// Destructors
ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap destructor called" << std::endl;
}

// Assignment operator
ClapTrap &ClapTrap::operator=(const ClapTrap &src) {
  std::cout << "ClapTrap assignment operator called\n" << std::endl;
  if (this != &src) {
	this->_name = src._name;
	this->_hitpoints = src._hitpoints;
	this->_energy_points = src._energy_points;
	this->_atack_damage = src._atack_damage;
  }
  return (*this);
}

void ClapTrap::attack(const std::string &target) {
  if (!_energy_points) {
    std::cout << "Energy depleted!\n" << std::endl;
    return;
  }
  if (!_hitpoints) {
    std::cout << "Not enought hp. Cannot attack!\n" << std::endl;
    return;
  }
  std::cout << "ClapTrap " << _name << " atacks " << target << ",causing "
            << _atack_damage << " points of damage!" << std::endl;
  _energy_points--;
  std::cout << "Energy points remaining: " << _energy_points << "\n"
            << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (amount > _hitpoints)
    _hitpoints = 0;
  else
    _hitpoints -= amount;
  std::cout << _name << " takes " << amount << " damage!\n"
            << "New hp: " << _hitpoints << "\n"
            << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (!_energy_points) {
    std::cout << "Cannot repair! Energy depleted!" << std::endl;
    return;
  }
  if (!_hitpoints) {
    std::cout << "Cannot repaird! You have no hp left!\n" << std::endl;
    return;
  }
  long long unsigned overflow;
  overflow = static_cast<unsigned long long>(_hitpoints) + amount;
  if (overflow > UINT32_MAX) {
    amount = UINT32_MAX - _hitpoints;
  }
  _hitpoints += amount;
  _energy_points--;
  std::cout << "Repair in progress...\n"
            << "New hp: " << _hitpoints << std::endl;
  std::cout << "Energy points remaining: " << _energy_points << "\n"
            << std::endl;
}
