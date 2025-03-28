#include "../include/ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(){
	std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name){
	this->_name = name;
	this->_hitpoints = 10;
	this->_energy_points = 10;
	this->_atack_damage = 0;
	std::cout << "Default ClapTrap constructor called" << std::endl;
	std::cout << "Hitpoints: " << _hitpoints << std::endl;
	std::cout << "Energy points: " << _energy_points << std::endl;
	std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

ClapTrap::~ClapTrap(){
	std::cout << "ClapTrap destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target){
	if (_energy_points > 0)
	{
		std::cout << "ClapTrap " << _name << " atacks " << target << ",causing "
				<< _atack_damage << " points of damage!" << std::endl;
		_energy_points--;
		std::cout << "Energy points remaining: " << _energy_points 
				<< "\n" << std::endl;
		return ;
	}
	std::cout << "Energy depleted!\n" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount){
	if (amount > _hitpoints)
		_hitpoints = 0;
	else
		_hitpoints -= amount;
	std::cout << _name << " takes " << amount << " damage!\n" << "New hp: "
			<< _hitpoints << "\n" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount){
	if (_energy_points && _hitpoints)
	{
		long long unsigned overflow;
		overflow = _hitpoints + amount;
		std::cout << overflow << std::endl;
		if (overflow > UINT32_MAX)
		{
			std::cout << "got here\n";
			amount = UINT32_MAX - _hitpoints;
		}
		_hitpoints += amount;
		_energy_points--;
		std::cout << "Repair in progress...\n" << "New hp: " << _hitpoints
				<<std::endl;
		std::cout << "Energy points remaining: " << _energy_points 
				<< "\n" << std::endl;
		return ;
	}
	if (!_energy_points)
	{
		std::cout << "Cannot repair! Energy depleted!" << std::endl;
		return ;
	}
	std::cout << "Cannot repaird! You have no hp left!\n" << std::endl;
}