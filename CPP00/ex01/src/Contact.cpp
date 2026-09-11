#include "../include/Contact.hpp"
#include <iostream>

std::string Contact::getInput(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt << std::endl;
    if (!std::getline(std::cin, input)) {
      std::cin.clear();
      std::cout << "\nEnd of input detected. Exiting..." << std::endl;
      exit(0);
    }

    if (!input.empty()) {
      return input;
    }
    std::cout << "Input cannot be empty. Try again" << std::endl;
  }
}

bool Contact::isValidPhoneNumber(const std::string &number) {
  if (number.empty())
    return false;
  size_t start = 0;
  if (number[0] == '+')
    start = 1;
  for(char c: number)
  {
	if(!isdigit(c))
		return false;
  }
  return true;
}

void Contact::addContact() {
  first_name = getInput("First name:");
  last_name = getInput("Last name:");
  nickname = getInput("Nickname:");
  while (true) {
    std::string number =
        getInput("Phone number (digits only)");
    if (isValidPhoneNumber(number)) {
      phone_number = number;
      break;
    }
    std::cout << "Invalid phone number. Try again." << std::endl;
  }
  darkest_secret = getInput("Darkest secret:");
  std::cout << "\nContact successfully added!\n" << std::endl;
}

  // Getter methods for displaying contact information
  std::string Contact::getFirstName() const { return first_name; }
  std::string Contact::getLastName() const { return last_name; }
  std::string Contact::getNickname() const { return nickname; }
  std::string Contact::getPhoneNumber() const { return phone_number; }
  std::string Contact::getDarkestSecret() const { return darkest_secret; }