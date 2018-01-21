#pragma once

#include <type_traits>

namespace flag_set
{
    template <class>
    struct use_flags : std::false_type
    {
    };

    template<class E>
    constexpr bool use_flags_v = use_flags<E>::value;
}

#define USE_FLAGS_FOR_ENUM(name)                \
    namespace flag_set                          \
    {                                           \
        template <>                             \
        struct use_flags<name> : std::true_type \
        {                                       \
        };                                      \
    }