// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP
#define BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP

#include <beman/bounds_test/plat/common.hpp>

namespace beman::bounds_test::detail {

constexpr bool can_add(auto a, auto b, auto c) noexcept {
  return !__builtin_add_overflow(a, b, &c);
}

constexpr bool can_sub(auto a, auto b, auto c) noexcept {
  return !__builtin_sub_overflow(a, b, &c);
}

constexpr bool can_mul(auto a, auto b, auto c) noexcept {
  return !__builtin_mul_overflow(a, b, &c);
}

} // namespace beman::bounds_test::detail

#endif // BEMAN_BOUNDS_TEST_PLAT_PLAT_HPP
