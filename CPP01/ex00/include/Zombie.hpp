#include <string>

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
