#ifndef HUMAN_A_CLASS_H
#define HUMAN_A_CLASS_H

#include "../include/Weapon.hpp"

class HumanA {
private:
	std::string name;
	Weapon *weapon;
public:
	//constructor
	HumanA(std::string name,Weapon &weapon);
	~HumanA();
	std::string get_name();
	void attack();
};
#endif // !HUMAN_A_CLASS_H
