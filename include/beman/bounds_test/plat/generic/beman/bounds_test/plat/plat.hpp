// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP
#define BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP

#include <concepts>
#include <limits>
#include <type_traits>

#include <beman/bounds_test/plat/common.hpp>

namespace beman::bounds_test::detail {

constexpr bool can_add(auto a, auto b, auto c) noexcept {
  using T = decltype(c);
  constexpr auto lmin = std::numeric_limits<T>::min();
  constexpr auto lmax = std::numeric_limits<T>::max();

  if constexpr (!std::signed_integral<T>) return a <= lmax - b;
  if (b > 0) return a <= lmax - b;
  return a >= lmin - b;
}

constexpr bool can_sub(auto a, auto b, auto c) noexcept {
  using T = decltype(c);
  constexpr auto lmin = std::numeric_limits<T>::min();
  constexpr auto lmax = std::numeric_limits<T>::max();

  if constexpr (!std::signed_integral<T>) return a >= lmin + b;
  if (b < 0) return a <= lmax + b;
  return a >= lmin + b;
}

constexpr bool can_mul(auto a, auto b, auto c) noexcept {
  using T = decltype(c);
  constexpr auto lmin = std::numeric_limits<T>::min();
  constexpr auto lmax = std::numeric_limits<T>::max();

  if (!(a && b)) return true;
  if constexpr (!std::signed_integral<T>) return a <= lmax / b;
  if (a == -1 && b == lmin) return false;
  if (b == -1 && a == lmin) return false;
  if (a > 0) return b > 0 ? a <= lmax / b : b >= lmin / a;
  return b > 0 ? a >= lmin / b : b >= lmax / a;
}

} // namespace beman::bounds_test::detail

#endif // BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP
