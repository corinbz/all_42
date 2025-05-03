#include "../include/Bureaucrat.hpp"

int main(void) {

  {
    try {
      Bureaucrat John("John", 0);
      std::cout << John << std::endl;
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      Bureaucrat John("John", 151);
      std::cout << John << std::endl;
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      Bureaucrat John("John", 2);
      std::cout << John << std::endl;
      John.incrementGrade();
      John.incrementGrade();
      John.incrementGrade();
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  {
    try {
      Bureaucrat John("John", 149);
      std::cout << John << std::endl;
      John.decrementGrade();
      John.decrementGrade();
      John.decrementGrade();
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return (0);
}
