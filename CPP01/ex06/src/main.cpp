#include "../include/Harl.hpp"
#include <iostream>

int main(int ac, char **av) {
	if (ac != 2){
		std::cout << "I need one argument!" << std::endl;
		return 1;
	}
    Harl harl;

	harl.complain(av[1]);
    return 0;
}
