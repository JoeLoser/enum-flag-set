#pragma once

#include <use_flags.hpp>

#include <type_traits>
#include <cstddef>
#include <climits>
#include <utility>
#include <bitset>

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

            // Default main 5
            flag_set() noexcept = default;
            flag_set(const flag_set&) noexcept = default;
            flag_set& operator=(const flag_set&) noexcept = default;
            flag_set(flag_set&&) noexcept = default;
            flag_set& operator=(flag_set&&) noexcept = default;

            // User constructors
            // This is intentionally not explicit so that we can construct
            // a flag_set from an enumerator.
            // TODO: May revisit option of enabling explicit ctor by means of
            // macro.
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

            constexpr void set_value(underlying_type val) noexcept(
                noexcept(assign(static_cast<enum_type>(val))))
            {
                assign(static_cast<enum_type>(val));
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

            void swap(flag_set& other) noexcept
            {
                std::swap(value_, other.value_);
            }

            friend constexpr flag_set operator|(flag_set lhs,
                                                flag_set rhs) noexcept
            {
                auto val = lhs.value_ | rhs.value_;
                return flag_set{static_cast<enum_type>(val)};
            }

            flag_set& operator|=(const flag_set& rhs) noexcept
            {
                value_ |= rhs.value_;
                return *this;
            }

            flag_set& operator|=(enum_type e) noexcept
            {
                value_ |= static_cast<decltype(value_)>(e);
                return *this;
            }

            friend constexpr flag_set operator&(flag_set lhs,
                                                flag_set rhs) noexcept
            {
                auto val = lhs.value_ & rhs.value_;
                return flag_set{val};
            }

            flag_set& operator&=(const flag_set& rhs) noexcept
            {
                value_ &= rhs.value_;
                return *this;
            }

            flag_set& operator&=(enum_type e) noexcept
            {
                value_ &= static_cast<decltype(value_)>(e);
                return *this;
            }

            constexpr flag_set operator~() const noexcept
            {
                auto negated = ~value_;
                return flag_set{negated};
            }

            friend constexpr flag_set operator^(flag_set lhs,
                                                flag_set rhs) noexcept
            {
                auto xor_value
                    = static_cast<rep_type>(lhs.value() ^ rhs.value());
                return flag_set{xor_value};
            };

            flag_set operator^=(const flag_set& rhs) noexcept
            {
                auto xor_value = value_ ^ rhs.value_;
                return flag_set{xor_value};
            }

            flag_set& operator^=(enum_type e) noexcept
            {
                value_ ^= static_cast<decltype(value_)>(e);
                return *this;
            }

            constexpr void clear() noexcept
            {
                value_ = 0;
            }

            constexpr static auto size_in_bits() noexcept
            {
                return sizeof(rep_type) * 8 * CHAR_BIT;
            }

            constexpr std::bitset<size_in_bits()> as_bitset() const noexcept
            {
                return {value_};
            }

            explicit constexpr operator std::bitset<size_in_bits()>() const
                noexcept
            {
                return as_bitset();
            }

        private:
            constexpr explicit flag_set(rep_type value) : value_{value}
            {}

            void assign(enum_type e) noexcept
            {
                value_ = static_cast<rep_type>(e);
            }

            // At any given time, only *one* value is represented when using
            // an enum class-like thing.
            rep_type value_{};
        };
    }

    template <class E>
    void swap(flag_set<E>& lhs, flag_set<E>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}

template <class E>
constexpr auto operator|(E lhs, E rhs) noexcept
{
    static_assert(flag_set::use_flags_v<E>,
                  "Please use USE_FLAGS_FOR_ENUM macro to enable flag_set "
                  "ops for your enum class.");
    return flag_set::flag_set<E>(lhs) | rhs;
}

template <class E>
constexpr auto operator&(E lhs, E rhs) noexcept
{
    static_assert(flag_set::use_flags_v<E>,
                  "Please use USE_FLAGS_FOR_ENUM macro to enable flag_set "
                  "ops for your enum class.");
    return flag_set::flag_set<E>(lhs) & rhs;
}

template <class E>
constexpr auto operator^(E lhs, E rhs) noexcept
{
    static_assert(flag_set::use_flags_v<E>,
                  "Please use USE_FLAGS_FOR_ENUM macro to enable flag_set "
                  "ops for your enum class.");
    return flag_set::flag_set<E>(lhs) ^ rhs;
}
