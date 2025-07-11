#include "../include/Span.hpp"
#include <iostream>

int main() {
  try {
    Span my_span(10);
    my_span.addNumber(10);
    my_span.addNumber(1);
    my_span.addNumber(12);
    std::cout << "shortestSpan is " << my_span.shortestSpan() << std::endl;
    std::cout << "longestSpan is " << my_span.longestSpan() << std::endl;

    std::cout << "-------------------------------" << std::endl;
    Span big_span(15000);
    big_span.populate();
    std::cout << "shortestSpan is " << big_span.shortestSpan() << std::endl;
    std::cout << "longestSpan is " << big_span.longestSpan() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }
  return 0;
}
