#include "../include/PresidentialPardonForm.hpp"
#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"

// Build and destroy
// no specified target
PresidentialPardonForm::PresidentialPardonForm()
    : AForm::AForm("PresidentialPardonForm", 25, 5), _target("default") {}
// with specified target
PresidentialPardonForm::PresidentialPardonForm(std::string const &target)
    : AForm::AForm("PresidentialPardonForm", 25, 5), _target(target) {};
PresidentialPardonForm::PresidentialPardonForm(
    PresidentialPardonForm const &copy)
    : AForm::AForm(copy), _target(copy._target) {};
PresidentialPardonForm const &
PresidentialPardonForm::operator=(const PresidentialPardonForm &src) {
  AForm::operator=(src);
  this->_target = src._target;
  return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {
  std::cout << RED << "PresidentialPardonForm has been destroyed" << RESET
            << std::endl;
};

void PresidentialPardonForm::beExecuted(const Bureaucrat &bureaucrat) const {
  if (bureaucrat.getGrade() > this->getGradeToExec()) {
    throw(PresidentialPardonForm::GradeTooHighException());
  } else if (!this->getSigned()) {
    std::cout << RED << "Form must be signed first!\n" << RESET;
  } else {
    std::cout << MAGENTA << this->_target
              << " has just been pardoned by Zaphod Beeblebrox!\n"
              << RESET;
  }
}

std::ostream &operator<<(std::ostream &str,
                         PresidentialPardonForm const &form) {
  return (str << YELLOW << form.getName()
              << " with attributes:\nsigned: " << form.getSigned()
              << "\n_grade_to_sign: " << form.getGradeToSign()
              << "\n_grade_to_exec: " << form.getGradeToExec() << RESET
              << std::endl);
}
