#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"

void testShrubberyCreationForm() {
  std::cout << "\n=== Testing ShrubberyCreationForm ===\n";
  try {
    // Create bureaucrats
    Bureaucrat highRank("Alice", 130);
    Bureaucrat lowRank("Bob", 140);
    Bureaucrat tooLow("Charlie", 150);

    // Create form
    ShrubberyCreationForm form("garden");

    // Test signing
    std::cout << "\n-- Signing Tests --\n";
    highRank.signForm(form);
    lowRank.signForm(form);
    tooLow.signForm(form);

    // Test execution
    std::cout << "\n-- Execution Tests --\n";
    highRank.executeForm(form);
    lowRank.executeForm(form);
    tooLow.executeForm(form);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

void testRobotomyRequestForm() {
  std::cout << "\n=== Testing RobotomyRequestForm ===\n";
  try {
    Bureaucrat highRank("Dave", 40);
    Bureaucrat midRank("Eve", 70);
    Bureaucrat tooLow("Frank", 100);

    RobotomyRequestForm form("printer");

    std::cout << "\n-- Signing Tests --\n";
    highRank.signForm(form);
    midRank.signForm(form);
    tooLow.signForm(form);

    std::cout << "\n-- Execution Tests (Random Outcomes) --\n";
    // Execute multiple times to show 50% success rate
    for (int i = 0; i < 3; ++i) {
      highRank.executeForm(form);
    }
    midRank.executeForm(form);
    tooLow.executeForm(form);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

void testPresidentialPardonForm() {
  std::cout << "\n=== Testing PresidentialPardonForm ===\n";
  try {
    Bureaucrat highRank("Grace", 5);
    Bureaucrat midRank("Hank", 20);
    Bureaucrat tooLow("Ivy", 50);

    PresidentialPardonForm form("Zaphod");

    std::cout << "\n-- Signing Tests --\n";
    highRank.signForm(form);
    midRank.signForm(form);
    tooLow.signForm(form);

    std::cout << "\n-- Execution Tests --\n";
    highRank.executeForm(form);
    midRank.executeForm(form);
    tooLow.executeForm(form);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

void testEdgeCases() {
  std::cout << "\n=== Testing Edge Cases ===\n";
  try {
    // Invalid Bureaucrat grades
    std::cout << "\n-- Invalid Grade Tests --\n";
    try {
      Bureaucrat invalidHigh("InvalidHigh", 0);
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }
    try {
      Bureaucrat invalidLow("InvalidLow", 151);
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }

    // Grade increment/decrement
    std::cout << "\n-- Grade Increment/Decrement Tests --\n";
    Bureaucrat edge("Edge", 1);
    try {
      edge.incrementGrade();
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }
    Bureaucrat lowEdge("LowEdge", 150);
    try {
      lowEdge.decrementGrade();
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }

    std::cout << "\n-- Unsigned Form Execution Test --\n";
    Bureaucrat highRank("Jane", 1);
    ShrubberyCreationForm unsignedForm("park");
    highRank.executeForm(unsignedForm);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

int main() {
  testShrubberyCreationForm();
  testRobotomyRequestForm();
  testPresidentialPardonForm();
  testEdgeCases();

  return 0;
}
