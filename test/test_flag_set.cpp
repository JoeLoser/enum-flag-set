#include "gtest/gtest.h"

#include <flag_set.hpp>
#include <use_flags.hpp>

using namespace flag_set;

namespace
{
    enum class Example : int
    {
        One = 1,        // 00001
        Two = 1 << 1,   // 00010
        Four = 2 << 2,  // 00100
        Eight = 2 << 3, // 01000
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

TEST(FlagSet, setValue)
{
    ExampleEnumSet ut{};
    constexpr auto whatever = 42u;
    ut.set_value(whatever);
    EXPECT_EQ(whatever, ut.value());
}

namespace
{
    auto zero = static_cast<Example>(0);
    auto one = static_cast<Example>(1);
    auto two = static_cast<Example>(2);
    auto four = static_cast<Example>(4);
    auto eight = static_cast<Example>(8);
    flag_set<Example> flag_set_zero{zero};
    flag_set<Example> flag_set_one{one};
    flag_set<Example> flag_set_two{two};
    flag_set<Example> flag_set_four{four};
    flag_set<Example> flag_set_eight{eight};
}

TEST(FlagSet, bitOREnumerators)
{
    flag_set<Example> result = static_cast<Example>(1) | static_cast<Example>(2)
                               | static_cast<Example>(4);
    EXPECT_EQ(1 | 2 | 4, result.value());
}

TEST(FlagSet, bitOR)
{
    auto result = flag_set_zero | flag_set_one;
    // 0
    // 1
    EXPECT_EQ(0b1, result.value());

    result = flag_set_one | flag_set_two;
    // 01
    // 10
    EXPECT_EQ(0b11, result.value());

    result = flag_set_one | flag_set_four;
    // 001
    // 100
    EXPECT_EQ(0b101, result.value());

    result = flag_set_two | flag_set_four;
    // 010
    // 100
    EXPECT_EQ(0b110, result.value());
}

TEST(FlagSet, bitORAssign)
{
    auto flag_set_modified{flag_set_zero};
    flag_set_modified |= flag_set_one;
    EXPECT_EQ(0b1, flag_set_modified.value());

    flag_set_modified |= flag_set_two;
    // 01
    // 10
    EXPECT_EQ(0b11, flag_set_modified.value());

    flag_set_modified |= flag_set_four;
    // 011
    // 100
    EXPECT_EQ(0b111, flag_set_modified.value());
}

TEST(FlagSet, bitAND)
{
    auto result = flag_set_zero & flag_set_one;
    // 0
    // 1
    EXPECT_EQ(0b0, result.value());

    result = flag_set_one & flag_set_two;
    // 01
    // 10
    EXPECT_EQ(0b0, result.value());

    result = flag_set_one & flag_set_four;
    // 001
    // 100
    EXPECT_EQ(0b0, result.value());

    result = flag_set_two & flag_set_four;
    // 010
    // 100
    EXPECT_EQ(0b0, result.value());

    result = flag_set_one & flag_set_one;
    EXPECT_EQ(0b1, result.value());

    result = flag_set_two & flag_set_two;
    // 10
    // 10
    EXPECT_EQ(0b10, result.value());
}

TEST(FlagSet, negate)
{
    auto result = ~flag_set_zero;
    EXPECT_EQ(~flag_set_zero.value(), result.value());

    result = ~flag_set_one;
    EXPECT_EQ(~flag_set_one.value(), result.value());

    result = ~flag_set_two;
    EXPECT_EQ(~flag_set_two.value(), result.value());

    result = ~flag_set_four;
    EXPECT_EQ(~flag_set_four.value(), result.value());

    result = ~flag_set_eight;
    EXPECT_EQ(~flag_set_eight.value(), result.value());
}

TEST(FlagSet, exclusiveORWithEnumerator)
{
    ExampleEnumSet result = zero ^ zero;
    EXPECT_EQ(0, result.value());

    result = zero ^ one;
    EXPECT_EQ(1, result.value());

    result = one ^ zero;
    EXPECT_EQ(1, result.value());

    result = one ^ one;
    EXPECT_EQ(0, result.value());
}

TEST(FlagSet, exclusiveORWithFlagSet)
{
    auto result = flag_set_zero ^ flag_set_zero;
    EXPECT_EQ(0, result.value());

    result = flag_set_zero ^ flag_set_one;
    EXPECT_EQ(1, result.value());

    result = flag_set_one ^ flag_set_zero;
    EXPECT_EQ(1, result.value());

    result = flag_set_one ^ flag_set_one;
    EXPECT_EQ(0, result.value());
}

TEST(FlagSet, asBitSet)
{
    auto bitsetUnderTest = flag_set_zero.as_bitset();
    EXPECT_EQ(flag_set_zero.value(), bitsetUnderTest.to_ulong());

    bitsetUnderTest = flag_set_one.as_bitset();
    EXPECT_EQ(flag_set_one.value(), bitsetUnderTest.to_ulong());

    bitsetUnderTest = (one | two | four).as_bitset();
    // 001
    // 010
    // 100
    // produces 111
    EXPECT_EQ(1 | 2 | 4, bitsetUnderTest.to_ulong());
}

namespace
{
    template <class From, class To>
    struct is_explicitly_convertible
    {
        static constexpr bool value
            = std::is_constructible_v<To,
                                      From> && !std::is_convertible_v<From, To>;
    };

    template <class From, class To>
    constexpr bool is_explicitly_convertible_v
        = is_explicitly_convertible<From, To>::value;
}

TEST(FlagSet, hasExplicitConversionToBitset)
{
    ExampleEnumSet ut{};
    static_assert(is_explicitly_convertible_v<ExampleEnumSet,
                                              std::bitset<ut.size_in_bits()>>);
}