
## Module-Specific Rules

You will notice that, in this module, the exercises can be solved WITHOUT the standard Containers and WITHOUT the standard Algorithms. However, **using them is precisely the goal of this Module.**

You must use the STL — especially the **Containers** (`vector`/`list`/`map`/and so forth) and the **Algorithms** (defined in header `<algorithm>`) — whenever they are appropriate. Moreover, you should use them as much as you can.

Thus, do your best to apply them wherever it’s appropriate. You will get a very bad grade if you don’t, even if your code works as expected. Please don’t be lazy.

You can define your templates in the header files as usual. Or, if you want to, you can write your template declarations in the header files and write their implementations in `.tpp` files. In any case, the header files are mandatory while the `.tpp` files are optional.

## Exercise 00: Easy find

| Turn-in directory | Files to turn in | Optional file | Forbidden functions |
| :---------------- | :--------------- | :------------ | :------------------ |
| `ex00/`           | `Makefile`, `main.cpp`, `easyfind.{h, hpp}` | `easyfind.tpp` | None                |

A first easy exercise is the way to start off on the right foot.

Write a function template easyfind that accepts a type T. It takes two parameters: the first one is of type T, and the second one is an integer.

Assuming T is a container of integers, this function has to find the first occurrence of the second parameter in the first parameter.

If no occurrence is found, you can either throw an exception or return an error value of your choice. If you need some inspiration, analyze how standard containers behave.

Of course, implement and turn in your own tests to ensure everything works as expected.

⚠️ You don’t have to handle associative containers. ⚠️
