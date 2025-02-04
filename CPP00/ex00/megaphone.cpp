#include <cctype>
#include <iostream>
#include <string>
#include <ostream>

std::string StrToUpper(std::string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return str;
}

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	std::string upper_string;
	for (int i = 1; av[i]; i++)
	{
		upper_string = StrToUpper(av[i]);
	  std::cout << upper_string ;
	}
	return (0);
}
