#pragma once

#include <cstddef>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm {
private:
  const std::string _name;
  bool _signed;
  const size_t _grade_to_sign;
  const size_t _grade_to_exec;

public:
  // Build and destroy
  AForm();
  AForm(const std::string name, const size_t grade_to_sign,
        const size_t grade_to_exec);

  AForm(const AForm &copy);
  AForm const &operator=(const AForm &src);
  virtual ~AForm() = 0;

  // Methods
  // getters
  std::string getName() const;
  bool getSigned() const;
  size_t getGradeToSign() const;
  size_t getGradeToExec() const;

  void beSigned(Bureaucrat &bureaucrat);
  void execute(Bureaucrat const &bureaucrat) const;
  virtual void beExecuted(Bureaucrat const &bureaucrat) const = 0;
  // Exceptions
  class GradeTooHighException : public std::exception {
  public:
    virtual char const *what(void) const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    virtual char const *what(void) const throw();
  };
};

std::ostream &operator<<(std::ostream &str, AForm const &form);
