#include "Contact.hpp"
//
// Colors
// #define GREEN "\033[0;32m" 
// #define RED "\033[0;31m" 
// #define BLUE "\033[0;34m" 
// #define YELLOW "\033[0;33m" 
// #define RESET "\033[0m" 
#define MAX_CONTACTS 8

class PhoneBook {

public:
  Contact contacts[MAX_CONTACTS];
  int current_index = 0;
  int total_contacts = 0;
  void displayContacts();
  void displayContact(int index);

private:
  std::string formatField(const std::string &text);
};
