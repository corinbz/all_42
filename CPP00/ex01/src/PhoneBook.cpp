#include "../include/PhoneBook.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

void PhoneBook::displayContacts() {
  if (this->total_contacts == 0) {
    std::cout << "\nPhoneBook is empty. Please add contact first!\n"
              << std::endl;
    return;
  }
  std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
  std::cout << "|----------|----------|----------|----------|" << std::endl;

  for (int i = 0; i < MAX_CONTACTS; i++) {
    char index = i + 49;

    // right-align each field
    std::cout << "|" << std::string(9, ' ') << index << "|"
              << formatField(contacts[i].getFirstName()) << "|"
              << formatField(contacts[i].getLastName()) << "|"
              << formatField(contacts[i].getNickname()) << "|" << std::endl;
  }
  while (true) {
    std::cout << "\nChose index to display full contact information"
              << std::endl;
    std::string choice;
    if (!std::getline(std::cin, choice)) {
      std::cin.clear();
      std::cout << "\nEnd of input detected. Exiting..." << std::endl;
      exit(0);
    }
      if (choice.empty()) {
        std::cout << "Input cannot be empty. Try again!" << std::endl;
        continue;
      }
      if (!std::all_of(choice.begin(), choice.end(), ::isdigit)) {
        std::cout << "Invalid input. Try again!" << std::endl;
        continue;
      }
      if (std::stoi(choice) <= total_contacts) {
        displayContact(std::stoi(choice) - 1);
        break;
      }
      std::cout << "Index out of range. Try again!" << std::endl;
    }
  }
std::string PhoneBook::formatField(const std::string &text) {
  const int width = 10;
  if (text.length() >= width) {
    // If text too long truncate and add . at the end
    return text.substr(0, width - 1) + ".";
  } else {
    // if text is shorter than width, pad with spaces
    // what happens here
    return (std::string(width - text.length(), ' ') + text);
  }
}

void PhoneBook::displayContact(int index) {
  std::cout << "\nFirst Name: " << contacts[index].getFirstName() << std::endl;
  std::cout << "Last Name: " << contacts[index].getLastName() << std::endl;
  std::cout << "Nickname: " << contacts[index].getNickname() << std::endl;
  std::cout << "Phone numer: " << contacts[index].getPhoneNumber() << std::endl;
  std::cout << "Darkest secret: " << contacts[index].getDarkestSecret()
            << std::endl
            << std::endl;
}
