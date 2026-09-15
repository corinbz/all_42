#include "../include/PhoneBook.hpp"
#include <iostream>

void displayMenu() {
  std::cout << "Please enter a command:\n"
            << "1. ADD\n"
            << "2. SEARCH\n"
            << "3. EXIT\n";
}

int parseCommand(const std::string &input) {
  if (input == "ADD" || input == "1")
    return 1;
  if (input == "SEARCH" || input == "2")
    return 2;
  if (input == "EXIT" || input == "3")
    return 3;
  return 4;
}

int main(void) {
  PhoneBook my_phonebook;
  Contact my_first_contact;
  std::string choice;

  while (true) {
    std::cin.clear();
    displayMenu();
    if (!std::getline(std::cin, choice)) {
      std::cin.clear();
      std::cout << "\nEnd of input detected. Exiting..." << std::endl;
      exit(0);
    }

    switch (parseCommand(choice)) {
    case 1: // ADD
      my_phonebook.contacts[my_phonebook.current_index % MAX_CONTACTS]
          .addContact();
      my_phonebook.current_index++;
      if (my_phonebook.total_contacts < MAX_CONTACTS)
        my_phonebook.total_contacts++;
      break;
    case 2: // SEARCH
      my_phonebook.displayContacts();
      break;
    case 3: // EXIT
      return (0);
    case 4: // Invalid command
      std::cout << "Invalid command. Try again";
      break;
    }
  }
}
