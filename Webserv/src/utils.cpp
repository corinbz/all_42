#include "../includes/utils.hpp"
 
std::string requestTypeAsString(HttpMethods type)
{
	if(type == GET)
		return "GET";
	if(type == POST)
		return "POST";
	if(type == DELETE)
		return "DELETE";
	return "Unknown";
}

std::string trimWhitespace(const std::string& str)
{
	size_t start = 0;

	while(start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
        start++;

    if(start == str.size())
        return "";

    size_t end = str.size() - 1;
    while(end > start && std::isspace(static_cast<unsigned char>(str[end])))
        end--;

    return str.substr(start, end - start + 1);
}
