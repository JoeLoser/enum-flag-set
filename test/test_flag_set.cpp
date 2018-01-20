#include "gtest/gtest.h"

#include <flag_set.hpp>

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

TEST(FlagSet, mainFiveDefaulted)
{
   static_assert(std::is_nothrow_default_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_copy_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_copy_assignable_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_move_constructible_v<ExampleEnumSet>);
   static_assert(std::is_nothrow_move_assignable_v<ExampleEnumSet>);
}
