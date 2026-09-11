# CPP09 — STL

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Three standalone programs, each built around a different part of the STL:
associative containers, sequence containers as a stack, and a
performance-sensitive sorting algorithm.

## ex00 — BitcoinExchange

```sh
cd ex00 && make
./btc input.txt
```

Loads a `date,exchange_rate` CSV database (`data.csv`) into a
`std::map<std::string, float>` for fast sorted date lookups, then reads
`input.txt` (`date | value`), validates each line (date format/range,
value in `[0, 1000]`), finds the closest date **not after** the requested
one (`std::map::lower_bound`), and prints `date => value = result`.

## ex01 — RPN

```sh
cd ex01 && make
./rpn "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

A Reverse Polish Notation calculator: pushes operands onto a
`std::stack<int>`/`std::stack<double>`, and on each operator (`+ - * /`)
pops the top two, applies it, and pushes the result — the exact structural
use case a stack exists for.

## ex02 — PmergeMe

```sh
cd ex02 && make
./PmergeMe 3 5 9 7 4
```

Implements the **Ford–Johnson (merge-insertion) sort** — pair up elements,
recursively sort by the larger of each pair, then binary-insert the
smaller elements back in using the jacobsthal-number insertion order to
minimize comparisons — and runs it **twice**, once over a `std::vector`
and once over a `std::deque`, timing each (`<chrono>`) to compare the two
containers' real-world performance for this access pattern.

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
