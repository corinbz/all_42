#include "../include/HumanB.hpp"
#include <iostream>

//constructor
HumanB::HumanB(std::string name){
	this->name = name;
}

HumanB::~HumanB(){};

std::string HumanB::get_name()
	{
	return HumanB::name;
}
	
void HumanB::setWeapon(Weapon weapon)
{
	this->weapon = weapon;
}

void HumanB::attack()
{
	std::cout << HumanB::get_name() << " attacks with their weapon " << HumanB::weapon.getType() << std::endl;
}
