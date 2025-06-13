// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP
#define BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP

#include <concepts>
#include <limits>
#include <type_traits>

namespace beman::bounds_test::detail {

constexpr bool can_div(auto a, auto b, auto c) noexcept {
  using T = decltype(c);
  if constexpr (std::signed_integral<T>) {
    if (a == std::numeric_limits<T>::min() && b == -1) return false;
  }
  return b;
}

constexpr bool can_shift(auto /* a */, auto b, auto c) noexcept {
  if constexpr (std::signed_integral<decltype(b)>)
    if (b < 0) return false;
  return b < std::numeric_limits<std::make_unsigned_t<decltype(c)>>::digits;
}

} // namespace beman::bounds_test::detail

#endif // BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP
