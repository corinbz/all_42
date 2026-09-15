#pragma once

#include <cstddef>
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
private:
  const std::string _name;
  bool _signed;
  const size_t _grade_to_sign;
  const size_t _grade_to_exec;

public:
  // Build and destroy
  Form();
  Form(const std::string name, const size_t grade_to_sign,
       const size_t grade_to_exec);

  Form(const Form &copy);
  Form const &operator=(const Form &src);
  ~Form();

  // Methods
  // getters
  std::string getName() const;
  bool getSigned() const;
  size_t getGradeToSign() const;
  size_t getGradeToExec() const;

  void beSigned(Bureaucrat &bureaucrat);
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

std::ostream &operator<<(std::ostream &str, Form const &form);
