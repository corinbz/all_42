#include "../include/ClapTrap.hpp"
#include "../include/FragTrap.hpp"

int main(void) {
  /* ClapTrap test("air_trap"); */
  FragTrap frag("Gandalf");
  FragTrap test;
  frag.attack("Goblin");
  /* test.takeDamage(20); */
  frag.beRepaired(999);
  frag.attack("Ranzo");
  frag.highFivesGuys();
  return (0);
}
