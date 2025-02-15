#include "../include/Zombie.hpp"

//Basic zombie ( not allocated )
void randomChump(std::string name)
{
	Zombie empty_zombie(name);
	empty_zombie.announce();
}
