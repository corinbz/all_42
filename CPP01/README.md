# CPP01 — Memory Allocation, References, Pointers, Switch

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Stack vs heap allocation (`new`/`delete`), pointers vs references, member
function pointers, and file I/O. Each `exXX/` builds independently.

## ex00 — Zombie (heap)

`newZombie(name)` heap-allocates a `Zombie` and returns it (caller must
`delete`); `randomChump(name)` stack-allocates one that dies with its
scope. Both call `announce()`, which prints `<name>: BraiiiiNs...`.

## ex01 — zombieHorde

`zombieHorde(N, name)` heap-allocates an **array** of `N` zombies with
`new Zombie[N]` and has every one of them `announce()`; the whole array is
freed with a single `delete []`.

## ex02 — stack vs heap

No class — a `main.cpp` that assigns the same string literal to a
stack `std::string`, a `std::string *` (heap, via `new`), and a
`std::string &` (reference to the stack variable), then prints the
**value** and **address** of each to show a reference shares its
referent's address while a pointer has its own.

## ex03 — HumanA / HumanB / Weapon (pointers vs references)

`HumanA` holds a `Weapon &` (must be given one at construction — can never
be weaponless); `HumanB` holds a `Weapon *` (may start unarmed, and
`setWeapon()` can be called any time). Both expose `getName()`; both fight
via `attack()`, printing `<name> attacks with their <weapon>`. Demonstrates
why references vs pointers is a design decision, not just syntax.

## ex04 — file "sed"

```sh
cd ex04 && make
./ex04 <filename> <string1> <string2>
```

No class — reads `<filename>`, replaces every occurrence of `<string1>`
with `<string2>`, and writes the result to `<filename>.replace`.

## ex05 / ex06 — Harl

`Harl` complains at 4 escalating levels: `DEBUG`, `INFO`, `WARNING`,
`ERROR`. Each level's message is a private member function; a
**pointer-to-member-function array** (indexed by level) drives dispatch
from `complain(std::string level)`, avoiding a chain of `if`/`switch`.

```sh
cd ex06 && make
./harl DEBUG      # prints only the DEBUG message
./harl WARNING    # prints WARNING and ERROR (everything >= that severity)
./harl NONSENSE   # "[ Probably complaining about insignificant problems ]"
```

`ex06` adds the "unrecognized level" fallback message that `ex05` doesn't
have.

## Build all

```sh
for d in ex00 ex01 ex02 ex03 ex04 ex05 ex06; do (cd "$d" && make); done
```
