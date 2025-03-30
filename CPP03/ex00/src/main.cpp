#include "../include/ClapTrap.hpp"

int main(void) {
  ClapTrap test("air_trap");
  test.attack("Goblin");
  // test.takeDamage(20);
  test.beRepaired(999);
  test.attack("Ranzo");
  return (0);
}
