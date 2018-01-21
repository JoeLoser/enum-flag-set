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
            // This is intentionally not explicit so that we can construct
            // a flag_set from an enumerator.
            // TODO: May revisit option of enabling explicit ctor by means of macro.
            constexpr flag_set(enum_type e) noexcept
                : value_{static_cast<rep_type>(e)}
            {}

            constexpr flag_set& operator=(enum_type e) noexcept(
                noexcept(std::declval<flag_set>().assign(e)))
            {
                assign(e);
                return *this;
            }

            constexpr underlying_type value() const noexcept
            {
                return static_cast<underlying_type>(value_);
            }

            // Equality
            friend constexpr bool
            operator==(flag_set lhs, flag_set rhs) noexcept(
                noexcept(std::declval<decltype(lhs)>().value()))
            {
                return lhs.value() == rhs.value();
            }
            friend constexpr bool
            operator!=(flag_set lhs,
                       flag_set rhs) noexcept(noexcept(operator==(lhs, rhs)))
            {
                return !(lhs == rhs);
            }

        private:
            void assign(enum_type e) noexcept
            {
                value_ = static_cast<rep_type>(e);
            }

            // At any given time, only *one* value is represented when using
            // an enum class-like thing.
            rep_type value_{};
        };
    }
}
