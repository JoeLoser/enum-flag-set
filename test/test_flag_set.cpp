#include "gtest/gtest.h"

#include <flag_set.hpp>
#include <use_flags.hpp>

using namespace flag_set;

namespace
{
    enum class Example : int
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
    static_assert(
        std::is_constructible_v<ExampleEnumSet, decltype(Example::One)>);
}

TEST(FlagSet, constructFromOneElementProperly)
{
    constexpr auto ut = ExampleEnumSet{Example::One};
    static_assert(static_cast<ExampleEnumSet::underlying_type>(1)
                  == ut.value());
}

TEST(FlagSet, canAssignFromEnumerator)
{
    static_assert(std::is_assignable_v<ExampleEnumSet, decltype(Example::Two)>);
}

TEST(FlagSet, equality)
{
    {
        constexpr ExampleEnumSet lhs{};
        constexpr ExampleEnumSet rhs{};
        static_assert(lhs == rhs);
        static_assert(rhs == lhs);
    }
    {
        constexpr ExampleEnumSet lhs{Example::Two};
        constexpr ExampleEnumSet rhs{Example::Two};
        static_assert(lhs == rhs);
        static_assert(rhs == lhs);
    }
}

TEST(FlagSet, inequality)
{
    constexpr ExampleEnumSet lhs{Example::One};
    constexpr ExampleEnumSet rhs{Example::Two};
    static_assert(lhs != rhs);
    static_assert(rhs != lhs);
}

TEST(FlagSet, copyConstruct)
{
    const ExampleEnumSet one = Example::One;
    ExampleEnumSet copy_constructed = one;
    EXPECT_EQ(one, copy_constructed);
}

TEST(FlagSet, copyAssign)
{
    const ExampleEnumSet one = Example::One;
    ExampleEnumSet copy_assigned = Example::Two;
    EXPECT_NE(one, copy_assigned);
    copy_assigned = one;
    EXPECT_EQ(one, copy_assigned);
}

TEST(FlagSet, moveConstruct)
{
    const ExampleEnumSet one = Example::Two;
    ExampleEnumSet copy_constructed = one;
    ExampleEnumSet move_constructed = std::move(copy_constructed);
    EXPECT_EQ(one, move_constructed);
}

TEST(FlagSet, moveAssign)
{
    ExampleEnumSet one = Example::One;
    ExampleEnumSet copy_constructed = one;
    ExampleEnumSet move_constructed = std::move(copy_constructed);
    ExampleEnumSet move_assigned = Example::Two;
    EXPECT_NE(one, move_assigned);
    move_assigned = std::move(move_constructed);
    EXPECT_EQ(one, move_assigned);
}

TEST(FlagSet, swapMemberFunction)
{
    ExampleEnumSet one{Example::One};
    ExampleEnumSet two{Example::Two};
    EXPECT_NE(one, two);
    EXPECT_EQ(1, one.value());
    EXPECT_EQ(2, two.value());
    one.swap(two);
    EXPECT_EQ(2, one.value());
    EXPECT_EQ(1, two.value());
}

TEST(FlagSet, swapFreeFunction)
{
    ExampleEnumSet one{Example::One};
    ExampleEnumSet two{Example::Two};
    EXPECT_NE(one, two);
    EXPECT_EQ(1, one.value());
    EXPECT_EQ(2, two.value());
    swap(one, two);
    EXPECT_EQ(2, one.value());
    EXPECT_EQ(1, two.value());
}
