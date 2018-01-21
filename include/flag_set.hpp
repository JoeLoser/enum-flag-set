#pragma once

#include <use_flags.hpp>

#include <type_traits>
#include <cstddef>
#include <climits>

namespace flag_set
{
    inline namespace v1
    {
        template <class E>
        class flag_set
        {
        public:
            static_assert(use_flags_v<E>,
                          "Please use USE_FLAGS_FOR_ENUM macro to enable "
                          "flag_set ops for your enum class.");
            using enum_type = typename std::decay_t<E>;
            using underlying_type = typename std::underlying_type_t<enum_type>;
            using rep_type = typename std::make_unsigned_t<underlying_type>;

            using pointer = enum_type*;
            using const_pointer = const enum_type*;
            using size_type = std::size_t;

            // Default main 5
            flag_set() noexcept = default;
            flag_set(const flag_set&) noexcept = default;
            flag_set& operator=(const flag_set&) noexcept = default;
            flag_set(flag_set&&) noexcept = default;
            flag_set& operator=(flag_set&&) noexcept = default;

            // User constructors
            constexpr explicit flag_set(enum_type e) noexcept
                : value_{static_cast<rep_type>(e)}
            {}

        private:
            // At any given time, only *one* value is represented when using
            // an enum class-like thing.
            rep_type value_{};
        };
    }
}
