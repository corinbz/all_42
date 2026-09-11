# CPP04 — Subtype Polymorphism, Abstract Classes

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

`Animal`/`Cat`/`Dog`, built up across three exercises to show why
`virtual` matters, how to deep-copy pointer members, and what an abstract
class buys you.

## ex00 — virtual dispatch

`Animal` has a `virtual makeSound()`; `Cat` and `Dog` override it. A
`WrongAnimal`/`WrongCat` pair (identical shape, but `makeSound()` is
**not** virtual) sits alongside them to make the bug visible side by side:
calling `makeSound()` through an `Animal *`/`WrongAnimal *` pointing at
the derived object dispatches correctly for the virtual pair and
incorrectly (calls the base version) for the non-virtual pair.

## ex01 — deep copies, arrays of base pointers

Same hierarchy, plus a `Brain` member (an array of string "ideas") owned
by `Cat`/`Dog`. Copy constructors and copy-assignment operators are
implemented to **deep-copy** the `Brain` (not just the pointer), verified
by allocating an array of `Animal *` mixing `Cat`s and `Dog`s and
`delete`-ing it through the base pointer (requires a virtual destructor).

## ex02 — abstract class

`Animal` becomes **abstract**: `makeSound()` is now a pure virtual
(`= 0`), so `Animal` itself can no longer be instantiated — only through
`Cat`/`Dog`. Everything else (the `Brain` deep-copy machinery) carries
over unchanged from ex01.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
