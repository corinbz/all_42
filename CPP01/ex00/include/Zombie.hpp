#include <string>

#define GREEN "\033[0;32m" 
#define RED "\033[0;31m" 
#define BLUE "\033[0;34m" 
#define YELLOW "\033[0;33m" 
#define RESET "\033[0m" 

class Zombie
{
	private:
		std::string _name;
	public:
		//constructor
		Zombie(std::string name);
		//deconstructor
		~Zombie();
		void announce(void);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);
