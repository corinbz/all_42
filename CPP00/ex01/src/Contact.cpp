#include "../include/Contact.hpp"
#include <algorithm>
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
  // std::all_of checks if every element satisfies a condition
  // takes 3 parameters
  // 1 - beggining of string
  // 2 - end of string
  // 3 - condition to check
  return std::all_of(number.begin() + start, number.end(), ::isdigit);
}

void Contact::addContact() {
  first_name = getInput("First name:");
  last_name = getInput("Last name:");
  nickname = getInput("Nickname:");
  while (true) {
    std::string number =
        getInput("Phone number (digits only or optional + at start)");
    if (isValidPhoneNumber(number)) {
      phone_number = number;
      break;
    }
    std::cout << "Invalid phone number. Try again.";
  }
  darkest_secret = getInput("Darkest secret:");
  std::cout << "\nContact successfully added!\n" << std::endl;
}
