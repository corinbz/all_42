#ifndef WEAPON_CLASS_H
#define WEAPON_CLASS_H

#include <string>

class Weapon {
private:
	std::string type;

public:
	Weapon();
	Weapon(std::string type);
	std::string getType();
	void setType(std::string type);
};

#endif // !WEAPON_CLASS_H
