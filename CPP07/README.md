# CPP07: templates

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Function and class templates: writing type-generic code once instead of
overloading by hand for every type.

## ex00: templates.hpp

Three function templates: `swap(T &a, T &b)`, `min(T const &a, T const &b)`,
`max(T const &a, T const &b)`, exercised in `main.cpp` against `int`s,
`std::string`s, and other comparable types.

## ex01: iter.hpp

`template <typename T, typename F> void iter(T *array, size_t length, F f)`
applies a (function-pointer or functor) parameter `f` to every element
of an array of any type, in place, without knowing `T` or `F` ahead of
time.

## ex02: Array.hpp

`template <typename T> class Array` is a fixed-size, dynamically allocated
array with:

- default constructor (zero/default-initialized elements) and a
  size-`n` constructor,
- a copy constructor and copy-assignment operator that deep copy,
- bounds-checked `operator[]` (throws `std::exception` on an out-of-range
  index, never invokes undefined behavior),
- `size()`.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
