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

TEST(FlagSet, constructFromOneElementProperly)
{
    constexpr auto ut = ExampleEnumSet{Example::One};
    static_assert(static_cast<ExampleEnumSet::underlying_type>(1) == ut.value());
}

TEST(FlagSet, canAssignFromEnumerator)
{
    static_assert(std::is_assignable_v<ExampleEnumSet, decltype(Example::Two)>);
}
