#include <cctype>
#include <string>

class Contact {
private:
  std::string first_name;
  std::string last_name;
  std::string nickname;
  std::string phone_number;
  std::string darkest_secret;

  static std::string getInput(const std::string &prompt);
  bool isValidPhoneNumber(const std::string &number);

public:
  Contact() = default;
  void addContact();
  // Getter methods for displaying contact information
  std::string getFirstName() const { return first_name; }
  std::string getLastName() const { return last_name; }
  std::string getNickname() const { return nickname; }
  std::string getPhoneNumber() const { return phone_number; }
  std::string getDarkestSecret() const { return darkest_secret; }
};
