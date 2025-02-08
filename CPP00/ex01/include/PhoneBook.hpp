#include "Contact.hpp"
#include <iostream>

class PhoneBook {

public:
  Contact contacts[8];
  int current_contact = 1;
  void displayContacts() {
    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
    std::cout << "|----------|----------|----------|----------|" << std::endl;

    for (int i = 1; i < current_contact; i++) {
      std::string index = std::to_string(i);

      // right-align each field
      std::cout << "|" << std::string(10 - index.length(), ' ') << index << "|"
                << formatField(contacts[i].getFirstName()) << "|"
                << formatField(contacts[i].getLastName()) << "|"
                << formatField(contacts[i].getNickname()) << "|" << std::endl;
    }
  }

private:
  std::string formatField(const std::string &text) {
    const int width = 10;
    if (text.length() >= width) {
      // If text too long trucate and add . at the end
      return text.substr(0, width - 1) + ".";
    } else {
      // if text is shorter then width, pad with spaces
      // what happens here
      return (std::string(width - text.length(), ' ') + text);
    }
  }
};
