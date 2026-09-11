# CPP06 — Casts

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

C++'s four named casts (`static_cast`, `dynamic_cast`, `reinterpret_cast`
— and where each one is (in)appropriate).

## ex00 — ScalarConverter

```sh
cd ex00 && make
./convert 42
./convert nan
./convert 'a'
./convert 4.2f
```

A static (uninstantiable) class that takes one literal on the command
line, figures out its narrowest type (`char`, `int`, `float`, `double`),
and prints its representation as **all four** types — using `static_cast`
for the numeric conversions, and handling out-of-range values and the
special float/double values (`nan`, `+inf`, `-inf`) as `impossible`/passed
through rather than crashing.

## ex01 — Serializer

A static class that converts a `void *` to a `uintptr_t` (`serialize`)
and back (`deserialize`), demonstrating `reinterpret_cast` and proving the
round trip yields the original pointer.

## ex02 — identify with dynamic_cast

`Base` with three empty derived classes `A`, `B`, `C`; `generate()`
returns a random one as a `Base *`. Two `identify` overloads determine the
real dynamic type without adding any RTTI machinery of their own:

- `identify(Base *p)` — tries `dynamic_cast<A *>`, `<B *>`, `<C *>` in
  turn, checking for `NULL`.
- `identify(Base &p)` — the reference version, using `dynamic_cast` +
  `try`/`catch (std::bad_cast &)` instead, since a failed reference cast
  throws rather than returning null.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
