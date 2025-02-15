#include "../include/Zombie.hpp"
#include <iostream>

//constructor
Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << "Look out! " << _name << " is alive... well, undead!" << std::endl;
}

//destructor
Zombie::~Zombie()
{
	std::cout << "Zombie " << _name << " has been destroyed. The world is safe... for now." << std::endl;
}

void Zombie::announce(void)
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
