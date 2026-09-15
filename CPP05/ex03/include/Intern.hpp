#pragma once

#include "AForm.hpp"
#include <string>
class Intern {
public:
  // Build and destroy
  Intern();
  Intern(const Intern &copy);
  Intern const &operator=(const Intern &src);
  ~Intern();

  // Methods
  AForm *makeForm(std::string const name, std::string const target);
};
