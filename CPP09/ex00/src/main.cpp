#include "../include/BitcoinExchange.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int main(int ac, char **av) {
  if (ac != 2) {
    throw std::runtime_error("Invalid argument count");
  }
  try {
    /* Date my_date("2020-03-99"); */
    /* std::cout << my_date << std::endl; */
    BtcConvertor convertor(av[1]);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return (0);
}
