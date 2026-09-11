#include <iostream>
#include <string>

int main(void) {
  std::string brain;
  brain = "HI THIS IS BRAIN";
  std::string *brainPTR = &brain;
  std::string &brainREF = brain;

  std::cout << &brain << " :brain value: " << brain << std::endl;
  std::cout << brainPTR << " :value pointed by brainPTR: " << *brainPTR
            << std::endl;
  std::cout << &brainREF << " :value pointed by brainREF: " << brainREF
            << std::endl;
}
