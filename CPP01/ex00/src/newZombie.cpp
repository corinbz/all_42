#include "../include/Zombie.hpp"

Zombie *newZombie(std::string name)
{
	Zombie *named_zombie = new Zombie(name);
	named_zombie->announce();
	return (named_zombie);
}
