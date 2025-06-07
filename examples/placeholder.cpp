// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Alternatively: #include <beman/bounds_test/bounds_test.hpp>
import beman.bounds_test;

namespace bt = beman::bounds_test;

int main(int argc, char** /* argv */) {
  return bt::can_convert_modular<unsigned>(argc);
}
