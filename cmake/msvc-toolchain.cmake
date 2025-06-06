# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

# This toolchain file is not meant to be used directly,
# but to be invoked by CMake preset and GitHub CI.
#
# This toolchain file configures for MSVC family of compiler.
#
# BEMAN_BUILDSYS_SANITIZER:
# This optional CMake parameter is not meant for public use and is subject to
# change.
# Possible values:
# - MaxSan: configures cl to use all available non-conflicting sanitizers.
#
# Note that in other toolchain files, TSan is also a possible value for
# BEMAN_BUILDSYS_SANITIZER, however, MSVC does not support thread sanitizer,
# thus this value is omitted.

include_guard(GLOBAL)

set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
