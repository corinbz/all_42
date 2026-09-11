#include "../include/ShrubberyCreationForm.hpp"
#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include <fstream>

// Build and destroy
// no specified target
ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm::AForm("ShrubberyCreationForm", 145, 137), _target("default") {}
// with specified target
ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
    : AForm::AForm("ShrubberyCreationForm", 145, 137), _target(target) {};
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &copy)
    : AForm::AForm(copy), _target(copy._target) {};
ShrubberyCreationForm const &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src) {
  AForm::operator=(src);
  this->_target = src._target;
  return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
  std::cout << RED << "ShrubberyCreationForm has been destroyed" << RESET
            << std::endl;
};

void ShrubberyCreationForm::beExecuted(const Bureaucrat &bureaucrat) const {
  if (bureaucrat.getGrade() > this->getGradeToExec())
    throw(ShrubberyCreationForm::GradeTooHighException());
  else if (!this->getSigned()) {
    std::cout << RED << "Form must be signed first!\n" << RESET;
  } else {

    std::ofstream outfile;

    outfile.open((this->_target + "_shrubbery").c_str());
    outfile << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⣸⠀⠀⠀⠀⠀⠀⠀⠀⡄⡄⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⢶⢠⠀⢀⡸⡄⠒⢺⠀⣸⣀⡀⣦⠽⠑⠁⠀⠀⠀⠀⠀⠀⠀⣆⣀⠗⠂⠀⠀⡆⢠⠃⡠⠜⠒⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⢤⠞⢳⠊⠓⠣⢸⡸⣲⠇⣘⣦⠚⢗⣻⠉⠻⡴⠂⢀⣀⠀⠀⣠⠂⠀⡇⠀⠀⠀⠀⡚⡲⢃⡉⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠐⠺⠤⢼⡀⡞⢶⠦⣤⡖⠯⠭⡽⠟⡲⠀⠀⣆⠴⠊⢀⠀⠈⠅⡜⠒⠁⠀⠀⠉⢱⠀⠀⠀⠈⣑⡼⠁⢀⢠⢠⠄⢠⠆⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠢⢄⢳⣁⣀⠆⠃⣇⡇⠜⠍⢳⡄⢰⢃⡈⡩⣲⠾⡃⢀⠀⠘⠤⢁⣠⠃⢠⢼⣇⣰⢃⣼⠀⠀⠀⣩⡾⠦⣆⠷⣅⠜⠉⠁⠀⠀⠀⠀\n"
            << "⠀⠀⠀⢦⠀⠈⠒⡥⣽⢁⠌⢹⢶⡤⡧⣾⠀⠀⠙⣾⣤⠖⠿⡿⣄⡗⢴⢣⡌⢲⣩⠚⠸⣌⣍⠹⣸⣚⡙⢷⣤⠞⠡⢄⣀⡳⣎⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⢄⣣⡈⠦⡜⣸⡹⣰⠃⡀⢱⣛⣰⣑⢽⣧⠀⢰⣿⡇⠰⠋⠑⡜⡗⡞⠋⠂⠘⢦⠳⣠⠿⠦⣼⢩⣤⢊⡾⠋⠀⠀⠀⠋⠀⢨⠏⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⢁⠇⠀⡏⠀⠈⢾⡄⠙⣤⠃⣟⠀⠋⣿⣅⡾⢻⢀⡀⡆⣰⣥⣟⢱⣞⣀⠀⣨⠧⣯⡀⠀⢸⣈⣷⡟⠀⢀⢦⠀⠀⠀⢠⠏⠀⠀⡀⣷⠀⠀⠀⠀\n"
            << "⠤⢲⠚⢒⢻⠙⢶⣴⢺⠉⠒⡧⠔⠛⠲⢤⣸⣿⠁⣼⡶⠿⠿⣽⣓⣸⢿⣓⡶⣚⢧⡷⣿⢫⣦⣸⣿⠏⢹⡴⠋⠸⡄⠀⠀⡞⠀⢰⣰⢣⠊⠀⣰⡠⠀\n"
            << "⠀⠈⡄⠀⢭⡇⡀⠉⠻⣇⠀⡇⠀⠀⠀⣀⡝⢿⡆⣿⢁⢀⡴⠋⣏⣏⡼⠋⡷⣇⡝⣇⣿⡜⠋⣿⣿⡆⣼⡝⡄⣠⢹⠀⣸⠁⠀⠀⠀⠛⣄⣸⡖⠊⠀\n"
            << "⠐⠴⣅⡆⠘⡎⢢⠀⠀⢹⣎⣷⠀⠀⣀⡕⠻⢚⣿⣿⡉⠉⠳⣄⣰⠟⠑⢶⠁⠹⢴⠁⡇⣠⣴⠿⣏⣾⡇⢹⡃⡗⢸⣷⢃⣠⠔⠋⠀⢠⠃⠀⠑⠹⠀\n"
            << "⠀⢤⢎⣈⡲⠵⣈⠉⠓⣾⠙⣾⣇⠀⠀⠛⣆⡇⢻⣿⡇⠀⣠⡾⠛⢶⡆⠈⣇⣰⠏⢰⣿⢏⡏⢠⣏⣼⠞⠉⠉⠱⣿⢿⡭⣄⠀⠀⢠⠏⠀⠀⠀⠀⠀\n"
            << "⠐⠚⠒⠂⠼⣄⠀⠉⠢⣼⡀⠈⢻⣆⠠⡄⠳⡇⢸⣿⣧⣾⡟⠀⠀⢸⡇⠀⣸⠋⠀⣼⡏⢾⠛⣿⢹⡏⠀⠀⢀⡼⠃⢘⠂⢨⠀⢀⡞⠀⢀⠄⢀⠆⡀\n"
            << "⠀⠀⠀⠀⠀⠈⠳⣄⠀⠈⠳⣄⠀⣿⣆⠸⡠⠜⣆⣿⣿⠏⠀⠀⠀⢸⡇⢰⠇⠀⢀⣿⠁⣿⢰⡇⣼⠁⠀⢠⡞⠁⠀⠸⣚⣮⠵⠟⠓⠦⣸⠀⡤⠼⠓\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠙⢦⣀⣀⣈⠳⣜⢿⣯⠀⠀⢈⣿⡿⠦⣤⣀⠀⢸⣷⡏⠀⠀⣸⣿⡾⠋⣿⢁⡟⠀⣰⣯⣤⠶⠞⣋⠽⢓⣒⡡⠤⠒⠛⠳⢧⡀⡄\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠙⠳⣿⣷⡀⢸⣿⡇⠀⠀⠉⠛⢾⣿⠀⠀⠀⣿⡟⠁⣸⣿⣾⣿⣿⠟⢉⣠⣴⠞⠋⠉⠉⠉⠂⠀⠀⠀⠀⠈⠃⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣾⣿⡇⠀⠀⠀⠀⢸⣿⠀⠀⢸⡟⢀⣼⡿⠋⣼⣿⣿⡿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⡇⠀⠀⠀⠀⠀⣿⡀⠀⣿⣷⡿⠋⠀⢠⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣄⠀⠀⠀⠀⢿⡇⣸⣿⠟⠀⠀⢀⣾⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⣸⣷⣿⡇⠀⠀⠀⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡏⢿⣿⣦⣀⣾⣿⢯⣿⠀⠀⠀⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣮⣿⣿⣿⡿⠁⣸⡟⠀⠀⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣿⣿⣿⣿⡟⠀⢠⣿⠃⠀⣼⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣷⣠⣾⣿⣤⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠿⠛⠻⣿⣿⠿⠿⠿⢿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠈⠡⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    outfile.close();
    std::cout << GREEN << "Shrubbery created succesfully" << RESET << std::endl;
  }
}

std::ostream &operator<<(std::ostream &str, ShrubberyCreationForm const &form) {
  return (str << YELLOW << form.getName()
              << " with attributes:\nsigned: " << form.getSigned()
              << "\n_grade_to_sign: " << form.getGradeToSign()
              << "\n_grade_to_exec: " << form.getGradeToExec() << RESET
              << std::endl);
}
