# CPP08: templated containers, STL

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Working *with* the STL instead of against it: generic algorithms over
iterators, and building a container on top of an existing one.

## ex00: easyfind

```cpp
template <typename T>
typename T::iterator easyfind(T &container, int value);
```

Finds the first occurrence of `value` in any STL container that exposes
iterators (`std::vector`, `std::list`, `std::deque`...) using
`std::find`, throwing if the value isn't present. Works for any
container type without being rewritten per container.

## ex01: Span

`Span` stores up to `N` unsigned ints (`addNumber`, or a range-insert from
any iterator pair) and computes:

- `shortestSpan()`: the smallest gap between any two stored numbers,
- `longestSpan()`: the difference between the max and min stored
  numbers,

both throwing if fewer than two numbers have been added.

## ex02: MutantStack

`MutantStack<T>` is a `std::stack<T>` with iterators added. Since
`std::stack` is an adapter over an underlying container
(`std::deque` by default) that hides iteration, `MutantStack` inherits
`std::stack<T, Container>` and exposes `begin()`/`end()` (and their
`const` counterparts) by accessing the protected underlying
container (`c`), so the LIFO-only interface also becomes iterable.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
