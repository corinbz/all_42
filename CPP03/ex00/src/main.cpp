#include "../include/ClapTrap.hpp"

int main(void)
{
	ClapTrap test("air_trap");
	test.attack("Goblin");
	test.takeDamage(20);
	test.beRepaired(100);
	return (0);
}