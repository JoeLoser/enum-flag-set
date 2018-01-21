#include "gtest/gtest.h"

#include <flag_set.hpp>
#include <use_flags.hpp>

using namespace flag_set;

namespace
{
    enum class Example
    {
        One = 1,
        Two = 1 << 1,
        Four = 2 << 2,
        Eight = 2 << 3,
        Sixteen = 2 << 4,
    };

    using ExampleEnumSet = flag_set<Example>;
}
USE_FLAGS_FOR_ENUM(Example);

TEST(FlagSet, mainFiveDefaulted)
{
   static_assert(std::is_nothrow_default_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_copy_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_copy_assignable_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_move_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_move_assignable_v<ExampleEnumSet>);
}

TEST(FlagSet, canConstructFromOneElement)
{
    static_assert(std::is_constructible_v<ExampleEnumSet, decltype(Example::One)>);
}
