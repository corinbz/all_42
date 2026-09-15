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
  std::string getFirstName() const;
  std::string getLastName() const;
  std::string getNickname() const;
  std::string getPhoneNumber() const;
  std::string getDarkestSecret() const;
};
