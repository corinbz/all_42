#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

class Contact {
private:
  std::string first_name;
  std::string last_name;
  std::string nickname;
  std::string phone_number;
  std::string darkest_secret;

  std::string getInput(const std::string &prompt) {
    std::string input;
    while (true) {
      std::cout << prompt << std::endl;
      std::getline(std::cin, input);

      if (!input.empty()) {
        return input;
      }
      std::cout << "Input cannot be empty. Try again" << std::endl;
    }
  }

  bool isValidPhoneNumber(const std::string &number) {
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

public:
  Contact() = default;

  void addContact() {
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

  // Getter methods for displaying contact information
  std::string getFirstName() const { return first_name; }
  std::string getLastName() const { return last_name; }
  std::string getNickname() const { return nickname; }
  std::string getPhoneNumber() const { return phone_number; }
  std::string getDarkestSecret() const { return darkest_secret; }
};
