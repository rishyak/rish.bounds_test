// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <catch2/catch_all.hpp>
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

TEMPLATE_TEST_CASE("can_negate signed types that get promoted to int", "[bt::can_negate]", std::int8_t, std::int16_t) {
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{-1}));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(TestType{1}));
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate signed types that don't get promoted to int",
                   "[bt::can_negate]",
                   std::int32_t,
                   std::int64_t) {
  STATIC_REQUIRE_FALSE(bt::can_negate(std::numeric_limits<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{-1}));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(TestType{1}));
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate unsigned types that get promoted to int",
                   "[bt::can_negate]",
                   std::uint8_t,
                   std::uint16_t) {
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate unsigned types that don't get promoted to int",
                   "[bt::can_negate]",
                   std::uint32_t,
                   std::uint64_t) {
  STATIC_REQUIRE(bt::can_negate(std::numeric_limits<TestType>::min()));
  STATIC_REQUIRE_FALSE(bt::can_negate(std::numeric_limits<TestType>::max()));
}

TEST_CASE("can_promote_modular always returns true", "[bt::can_promote_modular]") {
  STATIC_REQUIRE(bt::can_promote_modular(0));
}

TEST_CASE("can_negate_modular for unsigned types always returns true", "[bt::can_negate_modular]") {
  STATIC_REQUIRE(bt::can_negate_modular(0));
}

TEMPLATE_TEST_CASE("can_add unsigned", "[bt::can_add]", std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t) {
  using result_t = decltype(TestType{} + TestType{});
  constexpr auto lmax = std::numeric_limits<result_t>::max();
  STATIC_REQUIRE(bt::can_add(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmax}, TestType{0}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmax}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_add signed", "[bt::can_add]", std::int8_t, std::int16_t, std::int32_t, std::int64_t) {
  using result_t = decltype(TestType{} + TestType{});
  constexpr auto lmin = std::numeric_limits<result_t>::min();
  constexpr auto lmax = std::numeric_limits<result_t>::max();
  STATIC_REQUIRE(bt::can_add(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmax}, TestType{-1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmin}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmax}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmin}, TestType{-1}));
}

TEMPLATE_TEST_CASE("can_add_in_place unsigned",
                   "[bt::can_add_in_place]",
                   std::uint8_t,
                   std::uint16_t,
                   std::uint32_t,
                   std::uint64_t) {
  constexpr auto lmax = std::numeric_limits<TestType>::max();
  STATIC_REQUIRE(bt::can_add_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmax}, TestType{0}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmax}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_add_in_place signed",
                   "[bt::can_add_in_place]",
                   std::int8_t,
                   std::int16_t,
                   std::int32_t,
                   std::int64_t) {
  constexpr auto lmin = std::numeric_limits<TestType>::min();
  constexpr auto lmax = std::numeric_limits<TestType>::max();
  STATIC_REQUIRE(bt::can_add_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmax}, TestType{-1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmin}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmax}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmin}, TestType{-1}));
}

TEMPLATE_TEST_CASE("can_subtract unsigned",
                   "[bt::can_subtract]",
                   std::uint8_t,
                   std::uint16_t,
                   std::uint32_t,
                   std::uint64_t) {
  using result_t = decltype(TestType{} - TestType{});
  constexpr auto lmin = std::numeric_limits<result_t>::min();
  STATIC_REQUIRE(bt::can_subtract(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmin}, TestType{0}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract signed",
                   "[bt::can_subtract]",
                   std::int8_t,
                   std::int16_t,
                   std::int32_t,
                   std::int64_t) {
  using result_t = decltype(TestType{} - TestType{});
  constexpr auto lmin = std::numeric_limits<result_t>::min();
  constexpr auto lmax = std::numeric_limits<result_t>::max();
  STATIC_REQUIRE(bt::can_subtract(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmax}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmin}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmax}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract_in_place unsigned",
                   "[bt::can_subtract_in_place]",
                   std::uint8_t,
                   std::uint16_t,
                   std::uint32_t,
                   std::uint64_t) {
  constexpr auto lmin = std::numeric_limits<TestType>::min();
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{lmin}, TestType{0}));
  STATIC_REQUIRE(!bt::can_subtract_in_place(TestType{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract_in_place signed",
                   "[bt::can_subtract_in_place]",
                   std::int8_t,
                   std::int16_t,
                   std::int32_t,
                   std::int64_t) {
  constexpr auto lmin = std::numeric_limits<TestType>::min();
  constexpr auto lmax = std::numeric_limits<TestType>::max();
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{lmax}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{lmin}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract_in_place(TestType{lmax}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract_in_place(TestType{lmin}, TestType{1}));
}

TEST_CASE("can_take_remainder is can_divide", "[bt::can_take_remainder]") {
  STATIC_REQUIRE_FALSE(bt::can_take_remainder(0, 0));
}

TEST_CASE("can_take_remainder_in_place is can_divide_in_place", "[bt::can_take_remainder_in_place]") {
  STATIC_REQUIRE_FALSE(bt::can_take_remainder_in_place<int>(0, 0));
}
