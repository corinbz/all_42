#pragma once

#include <cstddef>
#include <string>
#include <sys/types.h>

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

class Form;

class Bureaucrat {
private:
  std::string const _name;
  size_t _grade;

public:
  // Build and destroy
  // Multiple constructors
  Bureaucrat();
  Bureaucrat(std::string const name, size_t grade);
  Bureaucrat(size_t grade);
  Bureaucrat(std::string const name);

  Bureaucrat(const Bureaucrat &copy);
  ~Bureaucrat();
  Bureaucrat &operator=(const Bureaucrat &src);

  // Methods
  std::string getName() const;
  size_t getGrade() const;
  void incrementGrade();
  void decrementGrade();
  void signForm(Form &form);

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

std::ostream &operator<<(std::ostream &str, Bureaucrat const &bureaucrat);
