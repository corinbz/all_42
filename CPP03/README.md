# CPP03: inheritance

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A little robot-fighting-game class hierarchy, used to practice single
inheritance, constructor/destructor call order, and overriding.

## ex00: ClapTrap

The base class: hit points, energy points, attack damage, and
`attack()`/`takeDamage()`/`beRepaired()`, each printing a status message
and each costing one energy point (no-op once energy is exhausted).

## ex01: ScavTrap

Inherits `ClapTrap` with its own (higher HP / lower damage) stats and an
extra ability, `guardGate()`. Demonstrates constructor chaining
(`ScavTrap` explicitly calls `ClapTrap`'s constructor) and that
`attack()`'s message changes even though the underlying mechanics are
inherited.

## ex02: FragTrap

A sibling of `ScavTrap`, also inheriting `ClapTrap`, with its own stat
profile and an extra ability, `highFivesGuys()`.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
