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
	virtual	~Brain();
	//copy assigment
	Brain &operator=(const Brain &src);
	//methods
	//setter
	void setIdea(int index, const std::string& idea);
	//getter
	std::string getIdea(int index) const;
	const std::string *getIdeaAdress(int index) const;
};

#endif // !BRAIN_HPP
