#ifndef HUMAN_B_CLASS_H
#define HUMAN_B_CLASS_H

#include "../include/Weapon.hpp"

class HumanB {
private:
	std::string name;
	Weapon weapon;
public:
	//constructor
	HumanB(Weapon weapon);
	HumanB();
	void setWeapon(std::string name);
	std::string get_name();
	void attack();
};
#endif // !HUMAN_B_CLASS_H
