# CPP00: namespaces, classes, member functions

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

First C++ module: leaving C's raw structs/functions behind for classes,
member functions, `std::string`/iostreams, and the `static`/`const`
keywords. Each `exXX/` is an independent program with its own
`include/`, `src/` and `Makefile`.

## ex00: megaphone

```sh
cd ex00 && make
./megaphone "hello world"          # SHOUTS EVERY ARGUMENT, UPPERCASED
./megaphone                        # prints a fallback "* LOUD AND UNBEARABLE
                                    #   FEEDBACK NOISE *"-style message
```

No classes yet. Just argument handling and `std::cout`, uppercasing each
`argv` entry via `std::toupper`.

## ex01: PhoneBook

```sh
cd ex01 && make
./phonebook
```

A terminal contact book holding up to 8 `Contact`s (first name, last
name, nickname, phone number, darkest secret). Commands read from
`std::cin`:

| Command | Effect |
|---------|--------|
| `ADD` | Prompts for each field, stores the contact (overwriting the oldest once full) |
| `SEARCH` | Lists contacts in a formatted, column-truncated table; enter an index to see the full record |
| `EXIT` | Quits |

`PhoneBook` owns the fixed-size array of `Contact`; `Contact` is a plain
data holder with accessors.

## ex02: Account

```sh
cd ex02 && make
./tests
```

`Account` tracks money for multiple accounts using `static` class-wide
members and functions (total number of accounts, total amount across all
accounts, total deposits/withdrawals), logging every operation with a
timestamp (`displayTimestamp`). `tests.cpp` exercises `makeDeposit`,
`makeWithdrawal`, and the static "report" (`displayAccountsInfos`).

## Build all

```sh
for d in ex00 ex01 ex02; do (cd "$d" && make); done
```
