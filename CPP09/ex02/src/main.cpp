#include "../include/PmergeMe.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  PmergeMe sorter;
  sorter.processSequence(args);

  return 0;
}
