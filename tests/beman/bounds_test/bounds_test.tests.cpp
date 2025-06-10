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

template <typename T>
using nl = std::numeric_limits<T>;

#define SIGNED_TYPES_PROMOTE     signed char, short
#define SIGNED_TYPES_NOPROMOTE   int, long, long long
#define SIGNED_TYPES             SIGNED_TYPES_PROMOTE, SIGNED_TYPES_NOPROMOTE
#define UNSIGNED_TYPES_PROMOTE   unsigned char, unsigned short
#define UNSIGNED_TYPES_NOPROMOTE unsigned int, unsigned long, unsigned long long
#define UNSIGNED_TYPES           UNSIGNED_TYPES_PROMOTE, UNSIGNED_TYPES_NOPROMOTE
#define ALL_TYPES                SIGNED_TYPES, UNSIGNED_TYPES

TEST_CASE("can_convert calls a standard library function", "[bt::can_convert]") {
  STATIC_REQUIRE(bt::can_convert<int>(0));
}

TEST_CASE("can_convert_modular always returns true", "[bt::can_convert_modular]") {
  STATIC_REQUIRE(bt::can_convert_modular<int>(0));
}

TEMPLATE_TEST_CASE("can_increment", "[bt::can_increment]", ALL_TYPES) {
  STATIC_REQUIRE(bt::can_increment(nl<TestType>::min()));
  STATIC_REQUIRE_FALSE(bt::can_increment(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_decrement", "[bt::can_decrement]", ALL_TYPES) {
  STATIC_REQUIRE_FALSE(bt::can_decrement(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_decrement(nl<TestType>::max()));
}

TEST_CASE("can_promote always returns true", "[bt::can_promote]") {
  STATIC_REQUIRE(bt::can_promote(0));
}

TEMPLATE_TEST_CASE("can_negate signed types that get promoted to int", "[bt::can_negate]", SIGNED_TYPES_PROMOTE) {
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{-1}));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(TestType{1}));
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate signed types that don't get promoted to int",
                   "[bt::can_negate]",
                   SIGNED_TYPES_NOPROMOTE) {
  STATIC_REQUIRE_FALSE(bt::can_negate(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{-1}));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(TestType{1}));
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate unsigned types that get promoted to int", "[bt::can_negate]", UNSIGNED_TYPES_PROMOTE) {
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_negate(TestType{0}));
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_negate unsigned types that don't get promoted to int",
                   "[bt::can_negate]",
                   UNSIGNED_TYPES_NOPROMOTE) {
  STATIC_REQUIRE(bt::can_negate(nl<TestType>::min()));
  STATIC_REQUIRE_FALSE(bt::can_negate(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_increment_modular unsigned", "[bt::can_increment_modular]", UNSIGNED_TYPES) {
  STATIC_REQUIRE(bt::can_increment_modular(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_increment_modular(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_increment_modular signed", "[bt::can_increment_modular]", SIGNED_TYPES) {
  STATIC_REQUIRE(bt::can_increment_modular(nl<TestType>::min()));
  STATIC_REQUIRE_FALSE(bt::can_increment_modular(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_decrement_modular unsigned", "[bt::can_decrement_modular]", UNSIGNED_TYPES) {
  STATIC_REQUIRE(bt::can_decrement_modular(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_decrement_modular(nl<TestType>::max()));
}

TEMPLATE_TEST_CASE("can_decrement_modular signed", "[bt::can_decrement_modular]", SIGNED_TYPES) {
  STATIC_REQUIRE_FALSE(bt::can_decrement_modular(nl<TestType>::min()));
  STATIC_REQUIRE(bt::can_decrement_modular(nl<TestType>::max()));
}

TEST_CASE("can_promote_modular always returns true", "[bt::can_promote_modular]") {
  STATIC_REQUIRE(bt::can_promote_modular(0));
}

TEST_CASE("can_negate_modular for unsigned types always returns true", "[bt::can_negate_modular]") {
  STATIC_REQUIRE(bt::can_negate_modular(0));
}

TEMPLATE_TEST_CASE("can_add unsigned", "[bt::can_add]", UNSIGNED_TYPES) {
  using result_t = decltype(TestType{} + TestType{});
  constexpr auto lmax = nl<result_t>::max();
  STATIC_REQUIRE(bt::can_add(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmax}, TestType{0}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmax}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_add signed", "[bt::can_add]", SIGNED_TYPES) {
  using result_t = decltype(TestType{} + TestType{});
  constexpr auto lmin = nl<result_t>::min();
  constexpr auto lmax = nl<result_t>::max();
  STATIC_REQUIRE(bt::can_add(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmax}, TestType{-1}));
  STATIC_REQUIRE(bt::can_add(result_t{lmin}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmax}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add(result_t{lmin}, TestType{-1}));
}

TEMPLATE_TEST_CASE("can_add_in_place unsigned", "[bt::can_add_in_place]", UNSIGNED_TYPES) {
  constexpr auto lmax = nl<TestType>::max();
  STATIC_REQUIRE(bt::can_add_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmax}, TestType{0}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmax}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_add_in_place signed", "[bt::can_add_in_place]", SIGNED_TYPES) {
  constexpr auto lmin = nl<TestType>::min();
  constexpr auto lmax = nl<TestType>::max();
  STATIC_REQUIRE(bt::can_add_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmax}, TestType{-1}));
  STATIC_REQUIRE(bt::can_add_in_place(TestType{lmin}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmax}, TestType{1}));
  STATIC_REQUIRE(!bt::can_add_in_place(TestType{lmin}, TestType{-1}));
}

TEMPLATE_TEST_CASE("can_subtract unsigned", "[bt::can_subtract]", UNSIGNED_TYPES) {
  using result_t = decltype(TestType{} - TestType{});
  constexpr auto lmin = nl<result_t>::min();
  STATIC_REQUIRE(bt::can_subtract(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmin}, TestType{0}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract signed", "[bt::can_subtract]", SIGNED_TYPES) {
  using result_t = decltype(TestType{} - TestType{});
  constexpr auto lmin = nl<result_t>::min();
  constexpr auto lmax = nl<result_t>::max();
  STATIC_REQUIRE(bt::can_subtract(result_t{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract(result_t{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmax}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract(result_t{lmin}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmax}, TestType{-1}));
  STATIC_REQUIRE(!bt::can_subtract(result_t{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract_in_place unsigned", "[bt::can_subtract_in_place]", UNSIGNED_TYPES) {
  constexpr auto lmin = nl<TestType>::min();
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{0}, TestType{0}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{1}, TestType{1}));
  STATIC_REQUIRE(bt::can_subtract_in_place(TestType{lmin}, TestType{0}));
  STATIC_REQUIRE(!bt::can_subtract_in_place(TestType{lmin}, TestType{1}));
}

TEMPLATE_TEST_CASE("can_subtract_in_place signed", "[bt::can_subtract_in_place]", SIGNED_TYPES) {
  constexpr auto lmin = nl<TestType>::min();
  constexpr auto lmax = nl<TestType>::max();
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
