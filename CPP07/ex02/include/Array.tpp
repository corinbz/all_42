#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "../include/Array.hpp"
#include <iostream>
#include <stdexcept>

template <typename T> Array<T>::Array() : my_array_(NULL), size_(0) {}

template <typename T>
Array<T>::Array(unsigned int size) : my_array_(new T[size]), size_(size) {
  for (unsigned int i = 0; i < size; ++i) {
    my_array_[i] = T();
  }
}

template <typename T>
Array<T>::Array(const Array &src)
    : my_array_(new T[src.size_]), size_(src.size_) {
  for (unsigned int i = 0; i < size_; ++i) {
    my_array_[i] = src.my_array_[i];
  }
}

template <typename T> Array<T> &Array<T>::operator=(const Array &src) {
  if (this != &src) {
    delete[] my_array_;
    size_ = src.size_;
    my_array_ = new T[size_];
    for (unsigned int i = 0; i < size_; ++i) {
      my_array_[i] = src.my_array_[i];
    }
  }
  return *this;
}

template <typename T> Array<T>::~Array() { delete[] my_array_; }

template <typename T> unsigned int Array<T>::size() const { return size_; }

template <typename T> T &Array<T>::operator[](unsigned int index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds");
  }
  return my_array_[index];
}

template <typename T> const T &Array<T>::operator[](unsigned int index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds");
  }
  return my_array_[index];
}

#endif
