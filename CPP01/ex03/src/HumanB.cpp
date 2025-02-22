#include "../include/HumanB.hpp"
#include <iostream>

//constructor
HumanB::HumanB(Weapon weapon){
	HumanB::weapon = weapon;
}

HumanB::HumanB(){};

std::string HumanB::get_name()
	{
	return HumanB::name;
}
	
void HumanB::setWeapon(std::string name)
{
	this->name = name;
}

void HumanB::attack()
{
	std::cout << HumanB::get_name() << " attacks with their weapon " << HumanB::weapon.getType() << std::endl;
}
