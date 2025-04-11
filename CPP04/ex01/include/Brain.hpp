#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
class Brain {
private:
	std::string ideas[100];
public:
	//constructors
	Brain();
	Brain(const Brain &copy);
	//deconstructor
	~Brain();
	//copy assigment
	Brain &operator=(const Brain &src);
	//methods
	void setIdea(int index, const std::string& idea);
	std::string getIdea(int index) const;
};

#endif // !BRAIN_HPP
