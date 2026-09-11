# CPP02 — Ad-hoc Polymorphism, Orthodox Canonical Form

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A fixed-point number class (`Fixed`), built up across three exercises to
also cover the **Orthodox Canonical Form** (default constructor, copy
constructor, copy assignment operator, destructor) and operator
overloading.

## ex00 — Fixed, raw bits

`Fixed` wraps a fixed-point value as a plain `int` with **8 fractional
bits** (`const static int fractionalBits = 8`). Exposes only
`getRawBits()`/`setRawBits()`; no arithmetic, no conversions — this
exercise is purely about implementing the four canonical-form members
correctly (including a copy constructor that logs, per the subject) and
`operator<<` for printing.

## ex01 — Fixed, conversions

Adds constructors from `int` and `float` (encoding into the fixed-point
representation) and `toInt()`/`toFloat()` conversions (decoding back).

## ex02 — Fixed, full operators

Adds the full set of C++ operators: comparisons (`<`, `>`, `<=`, `>=`,
`==`, `!=`), arithmetic (`+`, `-`, `*`, `/`), pre/post increment and
decrement (`++x`, `x++`, `--x`, `x--`), and static `min`/`max` helpers (4
overloads each, covering `const`/non-`const` reference pairs).

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
