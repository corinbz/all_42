#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"

class ShrubberyCreationForm : public AForm {
private:
  std::string _target;

public:
  // Build and destroy
  ShrubberyCreationForm();
  ShrubberyCreationForm(std::string const &target);
  ShrubberyCreationForm(ShrubberyCreationForm const &copy);
  ShrubberyCreationForm const &operator=(ShrubberyCreationForm const &src);
  ~ShrubberyCreationForm();

  // Member functions
  void beExecuted(Bureaucrat const &bureaucrat) const;
};

std::ostream &operator<<(std::ostream &str, ShrubberyCreationForm const &form);
