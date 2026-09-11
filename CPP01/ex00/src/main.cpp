#include "../include/Zombie.hpp"


int main()
{
	Zombie *alloc_zombie = newZombie("Stinky Pete");
	randomChump("Sir Limps-A-Lot");
	delete alloc_zombie;
	return (0);
}
