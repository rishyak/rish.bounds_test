// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <catch2/catch_test_macros.hpp>

import beman.bounds_test;

namespace bt = beman::bounds_test;

TEST_CASE("Placeholder") {
    bt::placeholder(1);
    REQUIRE(1);
}
