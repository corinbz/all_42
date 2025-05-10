#include "../include/class_A.hpp"
#include "../include/class_B.hpp"
#include "../include/class_C.hpp"
#include <iostream>
#include <random>

Base *generate(void) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dist(1, 3);
  int choice = dist(gen);
  switch (choice) {
  case 1:
    return new A();
    break;
  case 2:
    return new B();
    break;
  case 3:
    return new C();
    break;
  default:
    std::cerr << "Something went wrong inside generate!" << std::endl;
  }
  return NULL;
}

void identify(Base *p) {
  if (dynamic_cast<A *>(p))
    std::cout << "Class type is A" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "Class type is B" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "Class type is C" << std::endl;
  else
    std::cerr << "Something went wrong inside identify(Base *)" << std::endl;
}

void identify(Base &p) {
  try {
    A &a = dynamic_cast<A &>(p);
    (void)a;
    std::cout << "Class type is A" << std::endl;
  } catch (std::exception &e) {
  }
  try {
    B &b = dynamic_cast<B &>(p);
    (void)b;
    std::cout << "Class type is B" << std::endl;
  } catch (std::exception &e) {
  }
  try {
    C &c = dynamic_cast<C &>(p);
    (void)c;
    std::cout << "Class type is C" << std::endl;
  } catch (std::exception &e) {
  }
}

int main() {
  for (int i = 0; i < 5; i++) {
    Base *ptr = generate();
    Base &ref = *ptr;
    identify(ptr);
    identify(ref);
    std::cout << "\n\n";
    delete ptr;
  }
  return 0;
}
