// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_BOUNDS_TEST_IDENTITY_HPP
#define BEMAN_BOUNDS_TEST_IDENTITY_HPP

namespace beman::bounds_test {

template <typename T>
T placeholder(T a) {
    return a;
};

} // namespace beman::bounds_test

#endif // BEMAN_BOUNDS_TEST_IDENTITY_HPP
