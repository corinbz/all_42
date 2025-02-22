#ifndef HUMAN_A_CLASS_H
#define HUMAN_A_CLASS_H

#include "../include/Weapon.hpp"

class HumanA {
private:
	std::string name;
	Weapon *weapon;
public:
	//constructor
	HumanA(std::string name, );
	std::string get_name();
	void setWeapon(Weapon weapon);
	void attack();
};
#endif // !HUMAN_A_CLASS_H
