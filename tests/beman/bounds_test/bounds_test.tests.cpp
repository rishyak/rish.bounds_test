// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>

#ifdef __INTELLISENSE__
#include <beman/bounds_test/bounds_test.hpp>
#else
import beman.bounds_test;
#endif

namespace bt = beman::bounds_test;

TEST_CASE("can_convert calls a standard library function", "[bt::can_convert]") {
  STATIC_REQUIRE(bt::can_convert<int>(0));
}

TEST_CASE("can_convert_modular always returns true", "[bt::can_convert_modular]") {
  STATIC_REQUIRE(bt::can_convert_modular<int>(0));
}

TEST_CASE("can_promote always returns true", "[bt::can_promote]") {
  STATIC_REQUIRE(bt::can_promote(0));
}

TEST_CASE("can_negate signed types", "[bt::can_negate]") {
  STATIC_REQUIRE(bt::can_negate<std::int64_t>(0));
  STATIC_REQUIRE(bt::can_negate<std::int64_t>(42));
  STATIC_REQUIRE(bt::can_negate<std::int64_t>(-42));
  STATIC_REQUIRE_FALSE(bt::can_negate<std::int64_t>(std::numeric_limits<std::int64_t>::min()));
  STATIC_REQUIRE(bt::can_negate<int>(0));
  STATIC_REQUIRE(bt::can_negate<int>(42));
  STATIC_REQUIRE(bt::can_negate<int>(-42));
  STATIC_REQUIRE_FALSE(bt::can_negate<int>(std::numeric_limits<int>::min()));
  // get promoted to int
  STATIC_REQUIRE(bt::can_negate<std::int16_t>(0));
  STATIC_REQUIRE(bt::can_negate<std::int16_t>(42));
  STATIC_REQUIRE(bt::can_negate<std::int16_t>(-42));
  STATIC_REQUIRE(bt::can_negate<std::int8_t>(std::numeric_limits<char>::min()));
}

TEST_CASE("can_negate unsigned types narrower than int", "[bt::can_negate]") {
  STATIC_REQUIRE(bt::can_negate<std::uint8_t>(0));
  STATIC_REQUIRE(bt::can_negate<std::uint8_t>(1));
  STATIC_REQUIRE(bt::can_negate<std::uint16_t>(255));
}

TEST_CASE("unsigned types wider than int", "[bt::can_negate]") {
  STATIC_REQUIRE(bt::can_negate<unsigned int>(0));
  STATIC_REQUIRE_FALSE(bt::can_negate<unsigned int>(1));
}

TEST_CASE("can_promote_modular always returns true", "[bt::can_promote_modular]") {
  STATIC_REQUIRE(true);
}

TEST_CASE("can_negate_modular for unsigned types always returns true", "[bt::can_negate_modular]") {
  STATIC_REQUIRE(true);
}

TEST_CASE("can_negate_modular behaviour differs only for unsigned", "[comparison][bt::can_negate_modular]") {
  constexpr unsigned int x = 5;
  STATIC_REQUIRE_FALSE(bt::can_negate<unsigned int>(x));
  STATIC_REQUIRE(bt::can_negate_modular<unsigned int>(x));
  constexpr int y = std::numeric_limits<int>::min();
  STATIC_REQUIRE_FALSE(bt::can_negate<int>(y));
  STATIC_REQUIRE_FALSE(bt::can_negate_modular<int>(y));
}

TEST_CASE("can_add unsigned", "[bt::can_add]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    using U = decltype(a + a);
    constexpr auto lmax = std::numeric_limits<U>::max();
    STATIC_REQUIRE(bt::can_add(U{0}, T{0}));
    STATIC_REQUIRE(bt::can_add(U{1}, T{1}));
    STATIC_REQUIRE(bt::can_add(U{lmax}, T{0}));
    STATIC_REQUIRE(!bt::can_add(U{lmax}, T{1}));
  };
  f(std::uint8_t{});
  f(std::uint16_t{});
  f(std::uint32_t{});
  f(std::uint64_t{});
}

TEST_CASE("can_add signed", "[bt::can_add]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    using U = decltype(a + a);
    constexpr auto lmin = std::numeric_limits<U>::min();
    constexpr auto lmax = std::numeric_limits<U>::max();
    STATIC_REQUIRE(bt::can_add(U{0}, T{0}));
    STATIC_REQUIRE(bt::can_add(U{1}, T{1}));
    STATIC_REQUIRE(bt::can_add(U{lmax}, T{-1}));
    STATIC_REQUIRE(bt::can_add(U{lmin}, T{1}));
    STATIC_REQUIRE(!bt::can_add(U{lmax}, T{1}));
    STATIC_REQUIRE(!bt::can_add(U{lmin}, T{-1}));
  };
  f(std::int8_t{});
  f(std::int16_t{});
  f(std::int32_t{});
  f(std::int64_t{});
}

TEST_CASE("can_add_in_place unsigned", "[bt::can_add_in_place]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    constexpr auto lmax = std::numeric_limits<T>::max();
    STATIC_REQUIRE(bt::can_add_in_place(T{0}, T{0}));
    STATIC_REQUIRE(bt::can_add_in_place(T{1}, T{1}));
    STATIC_REQUIRE(bt::can_add_in_place(T{lmax}, T{0}));
    STATIC_REQUIRE(!bt::can_add_in_place(T{lmax}, T{1}));
  };
  f(std::uint8_t{});
  f(std::uint16_t{});
  f(std::uint32_t{});
  f(std::uint64_t{});
}

TEST_CASE("can_add_in_place signed", "[bt::can_add_in_place]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    constexpr auto lmin = std::numeric_limits<T>::min();
    constexpr auto lmax = std::numeric_limits<T>::max();
    STATIC_REQUIRE(bt::can_add_in_place(T{0}, T{0}));
    STATIC_REQUIRE(bt::can_add_in_place(T{1}, T{1}));
    STATIC_REQUIRE(bt::can_add_in_place(T{lmax}, T{-1}));
    STATIC_REQUIRE(bt::can_add_in_place(T{lmin}, T{1}));
    STATIC_REQUIRE(!bt::can_add_in_place(T{lmax}, T{1}));
    STATIC_REQUIRE(!bt::can_add_in_place(T{lmin}, T{-1}));
  };
  f(std::int8_t{});
  f(std::int16_t{});
  f(std::int32_t{});
  f(std::int64_t{});
}

TEST_CASE("can_subtract unsigned", "[bt::can_subtract]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    using U = decltype(a - a);
    constexpr auto lmin = std::numeric_limits<U>::min();
    STATIC_REQUIRE(bt::can_subtract(U{0}, T{0}));
    STATIC_REQUIRE(bt::can_subtract(U{1}, T{1}));
    STATIC_REQUIRE(bt::can_subtract(U{lmin}, T{0}));
    STATIC_REQUIRE(!bt::can_subtract(U{lmin}, T{1}));
  };
  f(std::uint8_t{});
  f(std::uint16_t{});
  f(std::uint32_t{});
  f(std::uint64_t{});
}

TEST_CASE("can_subtract signed", "[bt::can_subtract]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    using U = decltype(a - a);
    constexpr auto lmin = std::numeric_limits<U>::min();
    constexpr auto lmax = std::numeric_limits<U>::max();
    STATIC_REQUIRE(bt::can_subtract(U{0}, T{0}));
    STATIC_REQUIRE(bt::can_subtract(U{1}, T{1}));
    STATIC_REQUIRE(bt::can_subtract(U{lmax}, T{1}));
    STATIC_REQUIRE(bt::can_subtract(U{lmin}, T{-1}));
    STATIC_REQUIRE(!bt::can_subtract(U{lmax}, T{-1}));
    STATIC_REQUIRE(!bt::can_subtract(U{lmin}, T{1}));
  };
  f(std::int8_t{});
  f(std::int16_t{});
  f(std::int32_t{});
  f(std::int64_t{});
}

TEST_CASE("can_subtract_in_place unsigned", "[bt::can_subtract_in_place]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    constexpr auto lmin = std::numeric_limits<T>::min();
    STATIC_REQUIRE(bt::can_subtract_in_place(T{0}, T{0}));
    STATIC_REQUIRE(bt::can_subtract_in_place(T{1}, T{1}));
    STATIC_REQUIRE(bt::can_subtract_in_place(T{lmin}, T{0}));
    STATIC_REQUIRE(!bt::can_subtract_in_place(T{lmin}, T{1}));
  };
  f(std::uint8_t{});
  f(std::uint16_t{});
  f(std::uint32_t{});
  f(std::uint64_t{});
}

TEST_CASE("can_subtract_in_place signed", "[bt::can_subtract_in_place]") {
  constexpr auto f = [](auto a) {
    using T = decltype(a);
    constexpr auto lmin = std::numeric_limits<T>::min();
    constexpr auto lmax = std::numeric_limits<T>::max();
    STATIC_REQUIRE(bt::can_subtract_in_place(T{0}, T{0}));
    STATIC_REQUIRE(bt::can_subtract_in_place(T{1}, T{1}));
    STATIC_REQUIRE(bt::can_subtract_in_place(T{lmax}, T{1}));
    STATIC_REQUIRE(bt::can_subtract_in_place(T{lmin}, T{-1}));
    STATIC_REQUIRE(!bt::can_subtract_in_place(T{lmax}, T{-1}));
    STATIC_REQUIRE(!bt::can_subtract_in_place(T{lmin}, T{1}));
  };
  f(std::int8_t{});
  f(std::int16_t{});
  f(std::int32_t{});
  f(std::int64_t{});
}

TEST_CASE("can_take_remainder is can_divide", "[bt::can_take_remainder]") {
  STATIC_REQUIRE_FALSE(bt::can_take_remainder(0, 0));
}

TEST_CASE("can_take_remainder_in_place is can_divide_in_place", "[bt::can_take_remainder_in_place]") {
  STATIC_REQUIRE_FALSE(bt::can_take_remainder_in_place<int>(0, 0));
}
