#include "../include/Intern.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include <iostream>

Intern::Intern() {
  std::cout << BLUE << "Intern has been constructed\n" << RESET;
}

Intern::Intern(const Intern &copy) { *this = copy; }
Intern const &Intern::operator=(const Intern &src) {
  if (this == &src)
    return *this;
  return *this;
}
Intern::~Intern() {
  std::cout << RED << "Intern has been destroyed\n" << RESET;
}

static AForm *createShrubbery(const std::string target) {
  return (new ShrubberyCreationForm(target));
}

static AForm *createRobotomy(const std::string target) {
  return (new RobotomyRequestForm(target));
}

static AForm *createPresident(const std::string target) {
  return (new PresidentialPardonForm(target));
}

AForm *Intern::makeForm(std::string const name, std::string const target) {

  const std::string formNames[] = {"shrubbery creation", "robotomy request",
                                   "presidential pardon"};
  AForm *(*forms_functions[])(std::string target) = {
      &createShrubbery, &createRobotomy, &createPresident};

  for (int i = 0; i < 3; i++) {
    if (name == formNames[i]) {
      std::cout << BLUE << "Intern created " << name << ".\n" << RESET;
      return (forms_functions[i](target));
    }
  }
  std::cout << RED << "Intern cannot create the form " << name
            << ".\nTry one of the options:\n1. shrubbery creation\n2. robotomy "
               "request\n3. presidential pardon\n"
            << RESET;
  return (NULL);
}
