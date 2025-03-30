#include "../include/ClapTrap.hpp"

int main(void) {
  ClapTrap test("air_trap");
  ClapTrap test_copy;
  test_copy = test;
  test.attack("Goblin");
  // test.takeDamage(20);
  test.beRepaired(999);
  test.attack("Ranzo");
  test_copy.attack("fake");
  return (0);
}
