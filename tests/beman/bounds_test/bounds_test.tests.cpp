// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <catch2/catch_test_macros.hpp>

import beman.bounds_test;

namespace bt = beman::bounds_test;

TEST_CASE("Still A Placeholder") {
  REQUIRE(bt::can_convert_modular<unsigned>(1));
}
