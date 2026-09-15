#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"

class RobotomyRequestForm : public AForm {
private:
  std::string _target;

public:
  // Build and destroy
  RobotomyRequestForm();
  RobotomyRequestForm(std::string const &target);
  RobotomyRequestForm(RobotomyRequestForm const &copy);
  RobotomyRequestForm const &operator=(RobotomyRequestForm const &src);
  ~RobotomyRequestForm();

  // Member functions
  void beExecuted(Bureaucrat const &bureaucrat) const;
};

std::ostream &operator<<(std::ostream &str, RobotomyRequestForm const &form);
