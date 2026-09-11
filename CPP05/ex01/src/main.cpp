#include "../include/Bureaucrat.hpp"
#include "../include/Form.hpp"

int main(void) {
  {
    try {
      Form form_one("Cut Forest", 99, 0);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      Form form_two("Cut Forest", 99, 151);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      std::cout << "\n\n";
      Form form_two("Cut Forest", 99, 11);
      Bureaucrat John("John", 50);
      John.signForm(form_two);
      std::cout << form_two;
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      std::cout << "\n\n";
      Form form_two("Cut Forest", 99, 11);
      Bureaucrat John("John", 150);
      John.signForm(form_two);
      std::cout << form_two;
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return (0);
}
