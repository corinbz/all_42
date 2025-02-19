#ifndef ZOMBIE_CLASS_H
#define ZOMBIE_CLASS_H

#include <string>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

class Zombie {
private:
  std::string _name;

public:
  // constructor
  Zombie(std::string name);
  Zombie(void);
  // deconstructor
  ~Zombie(void);

  void announce(void);
  void set_name(std::string name);
};

Zombie *zombieHorde(int N, std::string name);

#endif
