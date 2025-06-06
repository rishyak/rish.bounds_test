# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

add_executable(beman.bounds_test.examples.placeholder)
target_sources(beman.bounds_test.examples.placeholder PRIVATE placeholder.cpp)
target_compile_features(beman.bounds_test.examples.placeholder
    PRIVATE cxx_std_20
)
target_link_libraries(
    beman.bounds_test.examples.placeholder
    PRIVATE beman::bounds_test
)
