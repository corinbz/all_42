#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include <iostream>

// Build and destroy
AForm::AForm()
    : _name("default"), _signed(false), _grade_to_sign(150),
      _grade_to_exec(150) {
  std::cout << BLUE << "AForm: default form constructor called for the form "
            << this->_name
            << " with parameters: " << "\nsigned: " << this->_signed
            << "\ngrade required to sign: " << this->_grade_to_sign
            << "\ngrade required to execute: " << this->_grade_to_exec << RESET
            << std::endl;
}

AForm::AForm(const std::string name, const size_t grade_to_sign,
             const size_t grade_to_exec)
    : _name(name), _signed(false), _grade_to_sign(grade_to_sign),
      _grade_to_exec(grade_to_exec) {

  if (_grade_to_sign > 150 || _grade_to_exec > 150)
    throw(AForm::GradeTooLowException());
  if (_grade_to_sign < 1 || _grade_to_exec < 1)
    throw(AForm::GradeTooHighException());
  std::cout << BLUE << "AForm: default form constructor called for the form "
            << this->_name
            << " with parameters: " << "\nsigned: " << this->_signed
            << "\ngrade required to sign: " << this->_grade_to_sign
            << "\ngrade required to execute: " << this->_grade_to_exec << RESET
            << std::endl;
}

AForm::AForm(const AForm &copy)
    : _name(copy._name), _signed(copy._signed),
      _grade_to_sign(copy._grade_to_sign), _grade_to_exec(copy._grade_to_exec) {
  *this = copy;
}

AForm const &AForm::operator=(const AForm &src) {
  this->_signed = src._signed;
  return (*this);
}

AForm::~AForm() {
  std::cout << RED << "AForm: AForm " << this->getName() << " is destroyed"
            << RESET << std::endl;
}

// Custom Methods
// Getters
std::string AForm::getName() const { return (this->_name); }
bool AForm::getSigned() const { return (this->_signed); }
size_t AForm::getGradeToSign() const { return (this->_grade_to_sign); }
size_t AForm::getGradeToExec() const { return (this->_grade_to_exec); }
//
void AForm::beSigned(Bureaucrat &bureaucrat) {
  if (this->getSigned()) {
    std::cout << RED << this->getName() << " is already signed.\n" << RESET;
    return;
  } else if (bureaucrat.getGrade() > this->getGradeToSign()) {
    std::cout << MAGENTA << bureaucrat.getName() << " could not sign form "
              << this->getName() << " because grade is not high enough" << RESET
              << std::endl;
    throw(AForm::GradeTooLowException());
  }
  this->_signed = true;
  std::cout << CYAN << "Bureaucrat " << bureaucrat.getName()
            << " has signed the form " << this->getName() << RESET << std::endl;
}

// Exceptions
char const *AForm::GradeTooLowException::what() const throw() {
  return (MAGENTA "Grade is too low!\n" RESET);
}

char const *AForm::GradeTooHighException::what() const throw() {
  return (MAGENTA "Grade is too high!\n" RESET);
}

std::ostream &operator<<(std::ostream &str, AForm const &form) {
  return (str << YELLOW << form.getName()
              << " with attributes:\nsigned: " << form.getSigned()
              << "\n_grade_to_sign: " << form.getGradeToSign()
              << "\n_grade_to_exec: " << form.getGradeToExec() << RESET
              << std::endl);
}
