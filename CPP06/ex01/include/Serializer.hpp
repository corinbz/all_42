#pragma once
#include "Data.hpp"
#include <cstdint>
//
// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

class Serializer {
private:
  // build and destroy
  Serializer();
  Serializer(const Serializer &copy);
  Serializer &operator=(const Serializer &src);
  virtual ~Serializer() = 0;

public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialize(uintptr_t raw);
};
