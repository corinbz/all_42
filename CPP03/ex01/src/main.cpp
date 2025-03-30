#include "../include/ClapTrap.hpp"
#include "../include/ScavTrap.hpp"

int main(void) {
  /* ClapTrap test("air_trap"); */
  ScavTrap scav("Gandalf");
  scav.attack("Goblin");
  /* test.takeDamage(20); */
  scav.beRepaired(999);
  scav.attack("Ranzo");
  scav.guardGate();
  return (0);
}
