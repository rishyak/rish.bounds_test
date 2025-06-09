// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP
#define BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP

#include <concepts>
#include <limits>

namespace beman::bounds_test::detail {

constexpr bool can_div(auto a, auto b, auto c) noexcept {
  using T = decltype(c);
  if constexpr (std::signed_integral<T>) {
    if (a == std::numeric_limits<T>::min() && b == -1) return false;
  }
  return b;
}

} // namespace beman::bounds_test::detail

#endif // BEMAN_BOUNDS_TEST_PLAT_COMMON_HPP
