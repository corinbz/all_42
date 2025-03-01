#include "../include/HumanA.hpp"
#include <iostream>

//constructor
HumanA::HumanA(std::string name, Weapon &weapon)
{
	this->name = name;
	this->weapon = &weapon;
}

HumanA::~HumanA(){};

std::string HumanA::get_name()
{
	return HumanA::name;
}

void HumanA::attack()
{
	std::cout << HumanA::get_name() << " attacks with their weapon " << HumanA::weapon->getType() << std::endl;
}
