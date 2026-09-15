#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm {
private:
  std::string _target;

public:
  // Build and destroy
  PresidentialPardonForm();
  PresidentialPardonForm(std::string const &target);
  PresidentialPardonForm(PresidentialPardonForm const &copy);
  PresidentialPardonForm const &operator=(PresidentialPardonForm const &src);
  ~PresidentialPardonForm();

  // Member functions
  void beExecuted(Bureaucrat const &bureaucrat) const;
};

std::ostream &operator<<(std::ostream &str, PresidentialPardonForm const &form);
