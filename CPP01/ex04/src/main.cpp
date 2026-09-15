#include <cctype>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>

std::string get_content(std::ifstream& file)
{
	std::string result;
	std::string line;

	while (std::getline(file, line)){
		result += line + "\n";
	}
	return result;
}

std::string find_and_replace(std::string& content, std::string& s1, std::string& s2){
	std::string new_string;
	size_t pos = 0;
	size_t last_pos = 0;

	if(s1.empty()){
		return content;
	}

	//searches for the first occurance of s1, starting from position pos
	//until std::string::npos which means untill end of string;
	while ((pos = content.find(s1, pos)) != std::string::npos) {
		//i need to check if char before and after word are not alphanumeric
		bool is_word_start = (pos == 0 || !std::isalnum(content[pos - 1]));
		bool is_word_end   = (pos + s1.length() == content.length() || !isalnum(content[pos + s1.length()]));

		if (is_word_start && is_word_end) {
			//append first part of the string untill the occurance of s1
			new_string += content.substr(last_pos, pos - last_pos);
			new_string += s2;
			pos += s1.length();
			last_pos = pos;
		}
		else
			pos += 1;
	}

	//add the remainder of the string
	if (last_pos < content.length()) {
		new_string += content.substr(last_pos);
	}
	
	return new_string;
}


int main(int ac, char **av)
{
	if (ac != 4) {
		std::cout << "I need 3 arguments fool!" << std::endl;
		return 1;
	}

	std::string s1 = av[2];
	std::string s2 = av[3];
	std::ifstream inFile(av[1]);

	if (inFile.is_open()) {
		std::cout << "File opened succesfully!" << std::endl;
	}
	else {
		std::cout << "Error opening file!" << std::endl;
		return (1);
	}
	std::string content = get_content(inFile);
	inFile.close();
	std::string new_content = find_and_replace(content, s1, s2);
	std::string filename = av[1];
	std::string outFileName = filename + ".replace";
	std::ofstream outFile(outFileName);
	if (outFile.is_open()) {
		outFile << new_content;
		outFile.close();
		std::cout << "Modified the text and wrote it to " << outFileName << std::endl;
	}
	else {
		std::cout << "Error writing to " << outFileName << std::endl;
		return 1;
	}

	return 0;
}
