# CPP05: repetition and exceptions

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A little bureaucracy simulator, built up across four exercises to practice
custom exceptions (deriving from `std::exception`), abstract classes, and
a simple factory pattern.

## ex00: Bureaucrat

`Bureaucrat` has a name and a grade from 1 (highest) to 150
(lowest). Constructing one outside that range throws
`GradeTooHighException`/`GradeTooLowException` (nested classes overriding
`what()`); `incrementGrade()`/`decrementGrade()` throw the same way at the
boundaries.

## ex01: Form

`Form` adds `gradeToSign`/`gradeToExecute` requirements and a `signed_`
flag. `Bureaucrat::signForm(Form &)` calls `Form::beSign(Bureaucrat &)`,
which checks the signing bureaucrat's grade against `gradeToSign` and
throws `GradeTooLowException` if insufficient.

## ex02: AForm + concrete forms

`Form` becomes the abstract base `AForm` (pure virtual `execute()`), with
three concrete forms, each requiring different grades to sign/execute:

| Form | Effect |
|------|--------|
| `ShrubberyCreationForm` | Writes an ASCII tree to `<target>_shrubbery` |
| `RobotomyRequestForm` | 50% chance of printing a "robotomy success" message (with drilling noises either way) |
| `PresidentialPardonForm` | Prints `<target> has been pardoned by Zaphod Beeblebrox` |

`execute()` also re-checks the executing bureaucrat's grade
(`gradeToExecute`) and that the form has been signed.

## ex03: Intern

`Intern::makeForm(const std::string &formName, const std::string &target)`
is a small factory: given a form name as a string, it constructs and
returns the matching `AForm *` (or reports an unknown form name), without
an `if`/`else if` chain per the subject's constraints.

## Build all

```sh
for d in ex00 ex01 ex02 ex03; do (cd "$d" && make); done
```
