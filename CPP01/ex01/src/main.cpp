#include "../include/Zombie.hpp"

int main() {

  int num_zombies = 3;
  Zombie *horde = zombieHorde(num_zombies, "chumpo");

  for (int i = 0; i < num_zombies; i++) {
    horde[i].announce();
  }

  // delete[] is uset to deallocate (free) arrays
  delete[] horde;
  return (0);
}
