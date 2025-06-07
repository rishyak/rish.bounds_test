// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>

// import beman.bounds_test;
#include <beman/bounds_test/bounds_test.hpp>

namespace bt = beman::bounds_test;

TEST_CASE("can_convert_modular always returns true", "[bt::can_convert_modular]") {
  STATIC_REQUIRE(bt::can_convert_modular<std::int8_t>(1));
  STATIC_REQUIRE(bt::can_convert_modular<std::uint64_t>(1));
}

TEST_CASE("can_promote always returns true", "[bt::can_promote]") {
  STATIC_REQUIRE(bt::can_promote<int>(0));
  STATIC_REQUIRE(bt::can_promote<unsigned>(123u));
  STATIC_REQUIRE(bt::can_promote<short>(-32768));
  STATIC_REQUIRE(bt::can_promote<std::uint8_t>(255));
  STATIC_REQUIRE(bt::can_promote<long long>(std::numeric_limits<long long>::min()));
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
  STATIC_REQUIRE(bt::can_promote_modular<int>(0));
  STATIC_REQUIRE(bt::can_promote_modular<unsigned>(123u));
  STATIC_REQUIRE(bt::can_promote_modular<short>(-32768));
  STATIC_REQUIRE(bt::can_promote_modular<std::uint8_t>(255));
  STATIC_REQUIRE(bt::can_promote_modular<long long>(std::numeric_limits<long long>::min()));
}

TEST_CASE("can_negate_modular for unsigned types", "[bt::can_negate_modular]") {
  STATIC_REQUIRE(bt::can_negate_modular<unsigned int>(0u));
  STATIC_REQUIRE(bt::can_negate_modular<unsigned int>(1u));
  STATIC_REQUIRE(bt::can_negate_modular<std::uint16_t>(1234));
}

TEST_CASE("can_negate_modular behaviour differs only for unsigned", "[comparison][bt::can_negate_modular]") {
  unsigned int x = 5;
  REQUIRE_FALSE(bt::can_negate<unsigned int>(x));
  REQUIRE(bt::can_negate_modular<unsigned int>(x));
  int y = std::numeric_limits<int>::min();
  REQUIRE_FALSE(bt::can_negate<int>(y));
  REQUIRE_FALSE(bt::can_negate_modular<int>(y));
}
