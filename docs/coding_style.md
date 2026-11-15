# Coding Style

This guide applies to **C++ source code** and describes how you should write your code. It is not only about syntax but also about good practices.

## 1. File and directory naming

* Files and directories are named using `lower_snake_case`.
* Use `.cpp` for C++ source files, `.cppm` for C++ modules and `.h` for C++ headers.
```
--> Bad
Source/
    Main.CPP
    modLoader.cpp
    Player_Manager.cxx

--> Good
src/
    main.cpp
    mod_loader.cpp
    player_manager.cpp
```

## 2. Modules

* Prefer using modules over headers, excepted they are not compatible with the build system or the toolchain.
* Use `lower_snake_case` for module names.
* Represent the directory structure in module names. For example, if a module is located at `entities/overworld/player.cppm`, it must be named `entities.overworld.player`.
* Each module has its own namespace. For example, if we consider the module described above, its namespace is `entities::overworld::player`.

## 3. Exporting symbols

* Do not export entire namespaces.
* Do not export data that should not be visible by other modules.
```cpp
// Bad
export namespace entities::overworld::player {

enum class PlayerState {};

class Player {};

} // export namespace entities::overworld::player

// Good
namespace entities::overworld::player {

enum class PlayerState {};

export class Player {};

} // namespace entities::overworld::player
```

## 4. Header guards

* Every header must have a header guard in order to prevent it to be included multiple times.
* Do not use `#pragma once` as it is not a standard preprocessor directive.
* The macro defined in a header guard must represent the directory structure from the latest include directory. The name of the macro must end with an underscore `_`. For example, a header located at `renderer/include/backends/opengl.h` must have a macro named `BACKENDS_OPENGL_H_`.
* There must be a comment with the name of the macro after the `#endif` directive.

```cpp
// Bad
#pragma once

class Person {};

// Bad
#ifndef PERSON_H
#define PERSON_H

class Person {};

#endif

// Good
#ifndef PERSON_H_
#define PERSON_H_

class Person {};

#endif // PERSON_H_
```

## 5. Identifier names

* Variable names use `lower_snake_case`.
* Global variable names use `lower_snake_case` and start with `g_`.
* Const and constexpr names use `UPPER_SNAKE_CASE`.
* Function names use `lower_snake_case`.
* Method names use `lower_snake_case`.
* Private variables and const and constexpr names use `lower_snake_case` and end with `_`.
* Class and struct names use `PascalCase`.
* Enum and enum class names use `PascalCase`.
* Enum constants use `UPPER_SNAKE_CASE`.
* Enum class constants use `PascalCase`.
* Namespace names use `lower_snake_case`.
* Macro names use `UPPER_SNAKE_CASE`.
* Template parameter names use `PascalCase`.
* Module names use `lower_snake_case` and can contain dots `.`.

## 6. Namespaces

* Avoid too long names for namespaces. For example, prefer names like `detail` over names like `implementations`.
* Do not indent code inside namespaces.
* Skip a line after the `{` and before the `}`.
* Add a comment after the end of the namespace which is the exact reproduction of the line where the namespace is defined.
```cpp
// Bad
namespace foo {
    auto void bar() -> int {
        return 42;
    }
}

// Good
namespace foo {

auto void bar() -> int {
    return 42;
}

} // namespace foo
```

## 7. Preprocessor

* Avoid using the preprocessor as much as possible. Replace macros by `constexpr` or `consteval` variables and functions.
```cpp
// Bad
#define MAX_PLAYERS 50
#define SQUARE(x) (x * x)

// Good
#include <cstddef>

constexpr std::size_t MAX_PLAYERS = 50;

constexpr auto square(int x) -> int {
    return x * x;
}
```

## 8. Standard library

* Since `std` module is not fully supported, we do not use it. However we use a precompiled header which exports various standard headers. Always include this header instead of the standard headers. This header is located at [`include/std.h`](/include/std.h).
* Do not use experimental features from the standard library.

```cpp
// Bad
#include <print>

// Good
#include <std.h>
```

## 9. Indentation and whitespaces

* Use whitespaces for indentation.
* A single indentation is 4 characters long.
* Consider refactoring your code if you have more than 4 indentations.
* Do not put whitespaces at the end of a line.

```cpp
// Bad
auto process(const Config& config) -> std::expected<Result, Error> {
    if (config.isValid()) {
        for (const auto& item : config.items()) {
            if (item.isEnabled()) {
                if (item.hasData()) {
                    handle(item);
                }
            }
        }
    }
    return Result{};
}

// Good
auto processItem(const Item& item) -> void {
    if (!item.isEnabled() || !item.hasData())
        return;
    handle(item);
}

auto process(const Config& config) -> std::expected<Result, Error> {
    if (!config.isValid())
        return std::unexpected(Error::InvalidConfig);

    for (const auto& item : config.items())
        processItem(item);

    return Result{};
}
```

## 10. Functions

* Always use trailing return types.
* Declare the parameters on the same line.
* Do not make and use too much `consteval` functions as they can significantly increase the compilation time.

```cpp
// Bad
int foo(
    int a,
    int b
) {
    return 42;
}

// Good
auto foo(int a, int b) -> int {
    return 42;
}
```

## 11. Structs and classes

* Use classes when the object has invariants.
* Use structs when the object members can vary independently.

## 12. Templates and concepts

* Do not turn the code into a template hell: use templates only when necessary, for example when you need a generic structure. Otherwise, consider using overloaded functions.
* The `template` statement is above the symbol definition.
* Use concepts when you need type checking in template parameters: they can make the code a lot more readable.

```cpp
// Bad
template<typename T> auto add(T a, T b) -> T {
    return a + b;
}

// Good
template<std::integral T>
auto add(T a, T b) -> T {
    return a + b;
}
```

## 13. Use the right types

* Use fixed-size types when you care about the size. For example, prefer `std::uint16_t` over `unsigned short` for a port address.
* Use size types like `std::size_t` and `ssize_t` when iterating over values or accessing data by index.
* Use range-based `for` unless you need a lot of control over the iterator.

```cpp
// Bad
for (int i = 0; i < vec.size(); i++)
    std::println("vec[{}] = {}", i, vec[i]);

// Good
for (const auto &[i, obj] : std::views::enumerate(vec))
    std::println("vec[{}] = {}", i, obj);
```

## 14. Inheritance

* Consider changing of design if you have 3 or more levels of inheritance: too deep inheritance makes the code more complex and less understandable.

```cpp
// Bad
class Entity {};
class Player : Entity {};
class Monster : Entity {};
class Zombie : Monster {};
class Skeleton : Monster {};
class BabyZombie : Zombie {};
class BabySkeleton : Skeleton {};

// Good
class Entity {};
class Player : Entity {};

enum class MonsterType {
    Zombie,
    Skeleton
};

class Monster : Entity {
    // ...
private:
    MonsterType type_;
    bool is_baby_;
};
```

## 15. RAII and encapsulation

* Use RAII and encapsulation when possible.
* Respect the rule of 0, 3 or 5 for all objects.
* Never let sensitive data be accessed by other objects.
* Don't use friend classes unless there is really no other way.
* Make getters `const`.
* Avoid global constructors.

## 16. Global variables

* Avoid global variables.

## 17. Pointers

* Avoid raw pointers. Use `std::unique_ptr` and `std::shared_ptr` instead.
* When a function needs to access an object, make it expect a reference instead of a pointer.
* Use `const` references or pointers when a function needs to access an object but does not modify it.

## 18. Braces

* Do not put braces around single-statement branches.
* Never put branch statements on the same line than the condition.
* In `if` (- `else if`) - `else` chains, do not put braces around single statement branches but if a conditional block has a multi-statement branch.

```cpp
// Bad
if (x) {
    std::println("x is true");
}
if (!y) std::println("y is false");

if (a)
    std::println("a is true");
else {
    std::println("a is false");
    std::exit(EXIT_FAILURE);
}

if (b)
{
    // ...
}

// Good
if (x)
    std::println("x is true");
if (!y)
    std::println("y is false");

if (a) {
    std::println("a is true");
} else {
    std::println("a is false");
    std::exit(EXIT_FAILURE);
}

if (b) {
    // ...
}
```

## 19. Switch loops

* Switch caes are aligned on the same column than the `switch` statement.

```cpp
// Bad
switch (x) {
    case 42:
        foo();
        break;

    case 12:
        bar();
        break;

    default:
        end();
        break;
}

// Good
switch (x) {
case 42:
    foo();
    break;

case 12:
    bar();
    break;

default:
    end();
    break;
}
```

## 20. Labels

* It is not a shame to use labels. However we are writing modern C++ so there are multiple and safe ways to avoid them.