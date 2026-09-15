#pragma once
#include <cstddef>
#include <iostream>

template <typename T> class Array {
private:
  T *my_array_;
  unsigned int size_;

public:
  // construct and destroy
  Array();
  Array(unsigned int size);
  Array(const Array &src);
  Array &operator=(const Array &src);
  ~Array();

  // member functions
  unsigned int size() const;
  T &operator[](unsigned int index); // subscript operator for non const
  const T &operator[](unsigned int index) const; // subscript operator for const
};

#include "Array.tpp"
