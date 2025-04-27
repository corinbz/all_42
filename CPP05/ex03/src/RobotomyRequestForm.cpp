#include "../include/RobotomyRequestForm.hpp"
#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include <iostream>
#include <random>

// Build and destroy
// no specified target
RobotomyRequestForm::RobotomyRequestForm()
    : AForm::AForm("RobotomyRequestForm", 72, 45), _target("default") {}
// with specified target
RobotomyRequestForm::RobotomyRequestForm(std::string const &target)
    : AForm::AForm("RobotomyRequestForm", 72, 45), _target(target) {};
RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &copy)
    : AForm::AForm(copy), _target(copy._target) {};
RobotomyRequestForm const &
RobotomyRequestForm::operator=(const RobotomyRequestForm &src) {
  AForm::operator=(src);
  this->_target = src._target;
  return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {
  std::cout << RED << "RobotomyRequestForm has been destroyed" << RESET
            << std::endl;
};

void RobotomyRequestForm::beExecuted(const Bureaucrat &bureaucrat) const {
  if (bureaucrat.getGrade() > this->getGradeToExec())
    throw(RobotomyRequestForm::GradeTooHighException());
  else if (!this->getSigned()) {
    std::cout << RED << "Form must be signed first!\n" << RESET;
  } else {
    std::random_device rd;  // generate seed from device
    std::mt19937 gen(rd()); // Mersenne Twister engine

    std::bernoulli_distribution dist(0.5); // 50% chance
    std::cout << YELLOW << "BZZZ! DRRR! WHIRR! \n" << RESET;

    if (dist(gen))
      std::cout << GREEN << this->_target
                << " has been robotomized succesfully!\n"
                << RESET;
    else
      std::cout << RED << "Robotomy failed for " << this->_target << ".\n"
                << RESET;
  }
}

std::ostream &operator<<(std::ostream &str, RobotomyRequestForm const &form) {
  return (str << YELLOW << form.getName()
              << " with attributes:\nsigned: " << form.getSigned()
              << "\n_grade_to_sign: " << form.getGradeToSign()
              << "\n_grade_to_exec: " << form.getGradeToExec() << RESET
              << std::endl);
}
