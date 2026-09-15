#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"
#include <iostream>

Bureaucrat::Bureaucrat() : _name("Just_a_number"), _grade(150) {
  std::cout << BLUE << "Bureaucrat: default constructor called for "
            << this->getName() << " with grade " << this->getGrade() << RESET
            << std::endl;
}

Bureaucrat::Bureaucrat(std::string const name, size_t grade)
    : _name(name), _grade(grade) {
  std::cout << BLUE << "Bureaucrat: constructor called for " << this->getName()
            << " with grade " << this->getGrade() << RESET << std::endl;
  if (this->_grade < 1)
    throw(Bureaucrat::GradeTooHighException());
  else if (this->_grade > 150)
    throw(Bureaucrat::GradeTooLowException());
}

Bureaucrat::Bureaucrat(size_t grade) : _name("Just_a_number"), _grade(grade) {
  std::cout << BLUE << "Bureaucrat: constructor called for " << this->getName()
            << " with grade " << this->getGrade() << RESET << std::endl;
  if (this->_grade < 1)
    throw(Bureaucrat::GradeTooHighException());
  else if (this->_grade > 150)
    throw(Bureaucrat::GradeTooLowException());
}

Bureaucrat::Bureaucrat(std::string const name) : _name(name), _grade(150) {
  std::cout << BLUE << "Bureaucrat: constructor called for " << this->getName()
            << " with grade " << this->getGrade() << RESET << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy)
    : _name(copy._name), _grade(copy._grade) {
  std::cout << BLUE << "Bureaucrat: copy constructor called" << RESET
            << std::endl;
  *this = copy;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src) {
  std::cout << BLUE << "Bureaucrat:: copy assigment operator called" << RESET
            << std::endl;
  if (this == &src) {
    return *this;
  }
  this->_grade = src.getGrade();
  return *this;
}

Bureaucrat::~Bureaucrat() {
  std::cout << RED << "Bureaucrat: Bureaucrat " << this->getName()
            << " is destroyed" << RESET << std::endl;
};

// Custom methods
// getters
std::string Bureaucrat::getName() const { return (this->_name); }
size_t Bureaucrat::getGrade() const { return (this->_grade); }

void Bureaucrat::incrementGrade() {
  this->_grade--;
  if (this->_grade < 1)
    throw(Bureaucrat::GradeTooHighException());
}

void Bureaucrat::decrementGrade() {
  this->_grade++;
  if (this->_grade > 150)
    throw(Bureaucrat::GradeTooLowException());
}

void Bureaucrat::signForm(AForm &form) { form.beSigned(*this); }

void Bureaucrat::executeForm(AForm const &form) const {
  if (this->getGrade() > form.getGradeToExec())
    throw(Bureaucrat::GradeTooLowException());
  else if (!form.getSigned())
    std::cout << RED << "Form must be signed first.\n" << RESET;
  else {
    form.beExecuted(*this);
    std::cout << GREEN << this->getName() << " executed " << form.getName()
              << ".\n"
              << RESET;
  }
}

char const *Bureaucrat::GradeTooLowException::what() const throw() {
  return (MAGENTA "Grade is too low!\n" RESET);
}

char const *Bureaucrat::GradeTooHighException::what() const throw() {
  return (MAGENTA "Grade is too high!\n" RESET);
}

std::ostream &operator<<(std::ostream &str, Bureaucrat const &bureaucrat) {
  return (str << YELLOW << bureaucrat.getName() << ", bureaucrat grade "
              << bureaucrat.getGrade())
         << RESET;
}
