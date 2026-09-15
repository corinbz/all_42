#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/Intern.hpp"

int main() {
  Intern intern;
  {
    AForm *form = nullptr;
    try {
      form = intern.makeForm("shrubbery creation", "garden");
      if (form) {
        delete form;
      }
      form = intern.makeForm("robotomy request", "printer");
      if (form) {
        delete form;
      }
      form = intern.makeForm("presidential pardon", "Zaphod");
      if (form) {
        delete form;
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }
    form = intern.makeForm("invalid form", "target");
  }
  std::cout << "\n\n";
  {
    AForm *form = nullptr;
    try {
      form = intern.makeForm("robotomy request", "printer");
      Bureaucrat John("John", 50);
      form->beSigned(John);
      form->beExecuted(John);
      if (form) {
        delete form;
      }
    } catch (const std::exception &e) {
      if (form)
        delete form;
      std::cerr << e.what() << "\n";
    }
  }
  return 0;
}
