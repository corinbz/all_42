#include "../include/FragTrap.hpp"
#include <iostream>

//constructors
FragTrap::FragTrap() : ClapTrap("default") {
    std::cout << "FragTrap default constructor called" << std::endl;
    std::cout << "Hitpoints: " << _hitpoints << std::endl;
    std::cout << "Energy points: " << _energy_points << std::endl;
    std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    std::cout << "FragTrap named constructor called" << std::endl;
    std::cout << "Hitpoints: " << _hitpoints << std::endl;
    std::cout << "Energy points: " << _energy_points << std::endl;
    std::cout << "Atack damage: " << _atack_damage << "\n" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy): ClapTrap(copy)
{
    std::cout << "FragTrap copy constructor called" << std::endl;
}

//destructor
FragTrap::~FragTrap(){
    std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void){
    std::cout << "FragTrap " << _name << " highfives everyone! BOOM!\n"
                << std::endl;
}