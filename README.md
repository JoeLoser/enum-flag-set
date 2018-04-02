# Bit Flags for enum classes

## Synopsis

This header-only library introduces a `flag_set` class template which provides bit
flags for enum classes.

## Motivation

While enum classes are great in that they are strongly typed and do not implicitly
cast to the underlying type, we cannot use the bitwise operators directly out
of the box because of this. So, we would like to define bitwise operators on some
type and have our type safety still.

The `flag_set<EnumType>` class template introduces this exact strong type and defines
bitwise operators on the underlying values the container holds.

## Code Example
[Try it out on Wandbox](https://wandbox.org/permlink/KzED2WMlJBYPQybg)

```c++
#include <utility>

#include "flag_set.hpp"

enum class ExampleEnumClass
{
    One = 1,
    Two = 1 << 1
};
USE_FLAGS_FOR_ENUM(ExampleEnumClass);

int main()
{
    constexpr auto mask = ExampleEnumClass::One | ExampleEnumClass::Two;
    if constexpr(mask)
    {
        // Do something :)
    }

    return EXIT_SUCCESS;
}
```
