// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_BOUNDS_TEST_HPP
#define BEMAN_BOUNDS_TEST_BOUNDS_TEST_HPP

#include <concepts>
#include <limits>
#include <type_traits>

namespace beman::bounds_test {

template <std::integral R, std::integral A>
constexpr bool can_convert(A a) noexcept;

template <std::integral R, std::integral A>
constexpr bool can_convert_modular(A) noexcept {
  return true;
}

template <std::integral A>
constexpr bool can_increment(A a) noexcept {
  if constexpr (std::is_unsigned_v<A>)
    return can_increment_modular(a);
  else
    return can_add(a, static_cast<A>(1));
}

template <std::integral A>
constexpr bool can_decrement(A a) noexcept {
  if constexpr (std::is_unsigned_v<A>)
    return can_decrement_modular(a);
  else
    return can_subtract(a, static_cast<A>(1));
}

template <std::integral A>
constexpr bool can_promote(A) noexcept {
  return true;
}

template <std::integral A>
constexpr bool can_negate(A a) noexcept {
  using result_t = decltype(-a);
  if constexpr (std::is_unsigned_v<result_t>)
    return a == 0;
  else
    return a != std::numeric_limits<result_t>::min();
}

template <std::integral A>
constexpr bool can_bitwise_not(A a) noexcept;

template <std::integral A>
constexpr bool can_increment_modular(A a) noexcept {
  return can_add_modular(a, static_cast<A>(1));
}

template <std::integral A>
constexpr bool can_decrement_modular(A a) noexcept {
  return can_subtract_modular(a, static_cast<A>(1));
}

template <std::integral A>
constexpr bool can_promote_modular(A) noexcept {
  return true;
}

template <std::integral A>
constexpr bool can_negate_modular(A a) noexcept {
  using result_t = decltype(-a);
  if constexpr (std::is_unsigned_v<result_t>)
    return true;
  else
    return a != std::numeric_limits<result_t>::min();
}

template <std::integral A>
constexpr bool can_bitwise_not_modular(A a) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_add(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_multiply(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_divide(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_take_remainder(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_compare(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_add_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_multiply_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_add_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_multiply_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_divide_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_take_remainder_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_add_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_multiply_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_in_place_modular(A a, B b) noexcept;

} // namespace beman::bounds_test

#endif // BEMAN_BOUNDS_TEST_BOUNDS_TEST_HPP
