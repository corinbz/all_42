#include "../include/Harl.hpp"
#include <iostream>

int main() {
    Harl harl;

    std::cout << "Harl's complaints:" << std::endl;

    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    harl.complain("RAGE"); 

    return 0;
}
