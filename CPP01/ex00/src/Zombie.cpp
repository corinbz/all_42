#include "../include/Zombie.hpp"
#include <iostream>

//constructor
Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << GREEN << "Look out! " << _name << " is alive... well, undead!" << RESET << std::endl;
}

//destructor
Zombie::~Zombie()
{
	std::cout << RED <<"Zombie " << _name << " has been destroyed. The world is safe... for now." << RESET <<std::endl;
}

void Zombie::announce(void)
{
	std::cout << YELLOW << _name << ": BraiiiiiiinnnzzzZ..." << RESET <<std::endl;
}
