#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
class ClapTrap {
	private:
		std::string _name;
		unsigned int _hitpoints;
		unsigned int _energy_points;
		unsigned int _atack_damage;
	public:
		ClapTrap();
		ClapTrap(std::string name);
		~ClapTrap();

		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif