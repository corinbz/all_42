#include "../include/HumanA.hpp"
#include <iostream>

//constructor
HumanA::HumanA(std::string name, Weapon weapon) {
	this->name = name;
	HumanA::setWeapon(weapon);
}

std::string HumanA::get_name()
	{
	return HumanA::name;
}
	
void HumanA::setWeapon(Weapon weapon)
{
	this->weapon = &weapon;
}

void HumanA::attack()
{
	std::cout << HumanA::get_name() << " attacks with their weapon " << HumanA::weapon->getType() << std::endl;
}
