// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
module;

#include <beman/bounds_test/bounds_test.hpp>

export module beman.bounds_test;

export namespace beman::bounds_test {

/* clang-format off */
using ::beman::bounds_test::can_convert;
using ::beman::bounds_test::can_convert_modular;

using ::beman::bounds_test::can_increment;
using ::beman::bounds_test::can_decrement;
using ::beman::bounds_test::can_promote;
using ::beman::bounds_test::can_negate;
using ::beman::bounds_test::can_bitwise_not;

using ::beman::bounds_test::can_increment_modular;
using ::beman::bounds_test::can_decrement_modular;
using ::beman::bounds_test::can_promote_modular;
using ::beman::bounds_test::can_negate_modular;
using ::beman::bounds_test::can_bitwise_not_modular;

using ::beman::bounds_test::can_add;
using ::beman::bounds_test::can_subtract;
using ::beman::bounds_test::can_multiply;
using ::beman::bounds_test::can_divide;
using ::beman::bounds_test::can_take_remainder;
using ::beman::bounds_test::can_shift_left;
using ::beman::bounds_test::can_shift_right;
using ::beman::bounds_test::can_bitwise_and;
using ::beman::bounds_test::can_bitwise_xor;
using ::beman::bounds_test::can_bitwise_or;

using ::beman::bounds_test::can_compare;

using ::beman::bounds_test::can_add_modular;
using ::beman::bounds_test::can_subtract_modular;
using ::beman::bounds_test::can_multiply_modular;
using ::beman::bounds_test::can_shift_left_modular;
using ::beman::bounds_test::can_shift_right_modular;
using ::beman::bounds_test::can_bitwise_and_modular;
using ::beman::bounds_test::can_bitwise_xor_modular;
using ::beman::bounds_test::can_bitwise_or_modular;

using ::beman::bounds_test::can_add_in_place;
using ::beman::bounds_test::can_subtract_in_place;
using ::beman::bounds_test::can_multiply_in_place;
using ::beman::bounds_test::can_divide_in_place;
using ::beman::bounds_test::can_take_remainder_in_place;
using ::beman::bounds_test::can_shift_left_in_place;
using ::beman::bounds_test::can_shift_right_in_place;
using ::beman::bounds_test::can_bitwise_and_in_place;
using ::beman::bounds_test::can_bitwise_xor_in_place;
using ::beman::bounds_test::can_bitwise_or_in_place;

using ::beman::bounds_test::can_add_in_place_modular;
using ::beman::bounds_test::can_subtract_in_place_modular;
using ::beman::bounds_test::can_multiply_in_place_modular;
using ::beman::bounds_test::can_shift_left_in_place_modular;
using ::beman::bounds_test::can_shift_right_in_place_modular;
using ::beman::bounds_test::can_bitwise_and_in_place_modular;
using ::beman::bounds_test::can_bitwise_xor_in_place_modular;
using ::beman::bounds_test::can_bitwise_or_in_place_modular;
/* clang-format on */

} // namespace beman::bounds_test
