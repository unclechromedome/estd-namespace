#ifndef TRAITS_H
#define TRAITS_H

#include "default_t.h"
#include "meta_support.h"
#include <type_traits>
#include <utility>
#include <iosfwd>

namespace Estd {

// Primary type predicates - pp. 1018-1019

template<typename T>
  constexpr bool Void()
  {
    return std::is_void<T>::value;
  }

template<typename T>
  constexpr bool Integral()
  {
    return std::is_integral<T>::value;
  }

template<typename T>
  constexpr bool Floating_point()
  {
    return std::is_floating_point<T>::value;
  }

template<typename T>
  constexpr bool Array()
  {
    return std::is_array<T>::value;
  }

template<typename T>
  constexpr bool Pointer()
  {
    return std::is_pointer<T>::value;
  }

template<typename T>
  constexpr bool Lvalue_reference()
  {
    return std::is_lvalue_reference<T>::value;
  }

template<typename T>
  constexpr bool Rvalue_reference()
  {
    return std::is_rvalue_reference<T>::value;
  }

template<typename T>
  constexpr bool Member_object_pointer()
  {
    return std::is_member_object_pointer<T>::value;
  }

template<typename T>
  constexpr bool Member_function_pointer()
  {
    return std::is_member_function_pointer<T>::value;
  }

template<typename T>
  constexpr bool Enum()
  {
    return std::is_enum<T>::value;
  }

template<typename T>
  constexpr bool Union()
  {
    std::is_union<T>::value;
  }

template<typename T>
  constexpr bool Class()
  {
    return std::is_class<T>::value;
  }

// We use Function_type() here so that we may reserve Function() for another concept.
template<typename T>
  constexpr bool Function_type()
  {
    return std::is_function<T>::value;
  }

// Composite type predicates - pg. 1019

template<typename T>
  constexpr bool Reference()
  {
    return std::is_reference<T>::value;
  }

template<typename T>
  constexpr bool Arithmetic()
  {
    return std::is_arithmetic<T>::value;
  }

template<typename T>
  constexpr bool Fundamental()
  {
    return std::is_fundamental<T>::value;
  }

template<typename T>
  constexpr bool Object()
  {
    return std::is_object<T>::value;
  }

template<typename T>
  constexpr bool Scalar()
  {
    return std::is_scalar<T>::value;
  }

template<typename T>
  constexpr bool Compound()
  {
    return std::is_compound<T>::value;
  }

template<typename T>
  constexpr bool Member_pointer()
  {
    return std::is_member_pointer<T>::value;
  }

// Type property predicates - pp. 1020-1022

template<typename T>
  constexpr bool Const()
  {
    return std::is_const<T>::value;
  }

template<typename T>
  constexpr bool Volatile()
  {
    return std::is_volatile<T>::value;
  }

template<typename T>
  constexpr bool Trivial()
  {
    return std::is_trivial<T>::value;
  }

/*
 * This is commented out because it is unimplemented in GCC 4.8.
 *
 * template<typename T>
 *   constexpr bool Trivially_copyable()
 *   {
 *     return std::is_trivially_copyable<T>::value;
 *   }
 */

template<typename T>
  constexpr bool Standard_layout()
  {
    return std::is_standard_layout<T>::value;
  }

template<typename T>
  constexpr bool Pod()
  {
    return std::is_pod<T>::value;
  }

template<typename T>
  constexpr bool Literal_type()
  {
    return std::is_literal_type<T>::value;
  }

template<typename T>
  constexpr bool Empty()
  {
    return std::is_empty<T>::value;
  }

template<typename T>
  constexpr bool Polymorphic()
  {
    return std::is_polymorphic<T>::value;
  }

template<typename T>
  constexpr bool Abstract()
  {
    return std::is_abstract<T>::value;
  }

template<typename T>
  constexpr bool Signed()
  {
    return std::is_signed<T>::value;
  }

template<typename T>
  constexpr bool Unsigned()
  {
    return std::is_unsigned<T>::value;
  }

template<typename T>
  constexpr bool Constructible()
  {
    return std::is_constructible<T>::value;
  }

template<typename T>
  constexpr bool Default_constructible()
  {
    return std::is_default_constructible<T>::value;
  }

template<typename T>
  constexpr bool Copy_constructible()
  {
    return std::is_copy_constructible<T>::value;
  }

template<typename T>
  constexpr bool Move_constructible()
  {
    return std::is_move_constructible<T>::value;
  }

template<typename T, typename U>
  constexpr bool Assignable()
  {
    return std::is_assignable<T, U>::value;
  }

template<typename T>
  constexpr bool Copy_assignable()
  {
    return std::is_copy_assignable<T>::value;
  }

template<typename T>
  constexpr bool Move_assignable()
  {
    return std::is_move_assignable<T>::value;
  }

template<typename T>
  constexpr bool Destructible()
  {
    return std::is_destructible<T>::value;
  }

/*
 * These functions are commented out because they are unimplemented in GCC 4.8.
 *
 * template<typename T>
 *   constexpr bool Trivially_constructible()
 *   {
 *     return std::is_trivially_constructible<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_default_constructible()
 *   {
 *     return std::is_trivially_default_constructible<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_copy_constructible()
 *   {
 *     return std::is_trivially_copy_constructible<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_assignable()
 *   {
 *     return std::is_trivially_assignable<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_copy_assignable()
 *   {
 *     return std::is_trivially_copy_assignable<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_move_assignable()
 *   {
 *     return std::is_trivially_move_assignable<T>::value;
 *   }
 * 
 * template<typename T>
 *   constexpr bool Trivially_destructible()
 *   {
 *     return std::is_trivially_destructible<T>::value;
 *   }
 */

template<typename T>
  constexpr bool Nothrow_constructible()
  {
    return std::is_nothrow_constructible<T>::value;
  }

template<typename T>
  constexpr bool Nothrow_default_constructible()
  {
    return std::is_nothrow_default_constructible<T>::value;
  }

template<typename T>
  constexpr bool Nothrow_copy_constructible()
  {
    return std::is_nothrow_copy_constructible<T>::value;
  }

template<typename T>
  constexpr bool Nothrow_move_constructible()
  {
    return std::is_nothrow_move_constructible<T>::value;
  }

template<typename T, typename U>
  constexpr bool Nothrow_assignable()
  {
    return std::is_nothrow_assignable<T, U>::value;
  }

template<typename T>
  constexpr bool Nothrow_copy_assignable()
  {
    return std::is_nothrow_copy_constructible<T>::value;
  }

template<typename T>
  constexpr bool Nothrow_move_assignable()
  {
    return std::is_nothrow_move_assignable<T>::value;
  }

template<typename T>
  constexpr bool Nothrow_destructible()
  {
    return std::is_nothrow_destructible<T>::value;
  }

template<typename T>
  constexpr bool Has_virtual_destructor()
  {
    return std::has_virtual_destructor<T>::value;
  }

// Type property queries - pg. 1022

template<typename T>
  constexpr unsigned Alignment_of()
  {
    return std::alignment_of<T>::value;
  }

template<typename T>
  constexpr unsigned Rank()
  {
    return std::rank<T>::value;
  }

template<typename T, unsigned N = 0>
  constexpr unsigned Extent()
  {
    return std::extent<T, N>::value;
  }

template<typename T, typename U>
  constexpr bool Same()
  {
    return std::is_same<T, U>::value;
  }

template<typename T, typename U>
  constexpr bool Base_of()
  {
    return std::is_base_of<T, U>::value;
  }

// Extension from Origin.
template<typename T, typename U>
  constexpr bool Derived()
  {
    return std::is_base_of<U, T>::value;
  }

template<typename T, typename U>
  constexpr bool Convertible()
  {
    return std::is_convertible<T, U>::value;
  }

// Type generators - pg 1023-1025

template<typename T>
  using Remove_const = typename std::remove_const<T>::type;

template<typename T>
  using Remove_volatile = typename std::remove_volatile<T>::type;

template<typename T>
  using Remove_cv = typename std::remove_cv<T>::type;

template<typename T>
  using Add_const = typename std::add_const<T>::type;

template<typename T>
  using Add_volatile = typename std::add_volatile<T>::type;

template<typename T>
  using Add_cv = typename std::add_cv<T>::type;

template<typename T>
  using Remove_reference = typename std::remove_reference<T>::type;

template<typename T>
  using Add_lvalue_reference = typename std::add_lvalue_reference<T>::type;

template<typename T>
  using Add_rvalue_reference = typename std::add_rvalue_reference<T>::type;

// Origin workaround that makes sure that adding a reference to void gives substitution_failure.
namespace impl {

template<typename T>
  struct require_lvalue_reference
    : std::add_lvalue_reference<T> { };

template<>
  struct require_lvalue_reference<void> {
    using type = substitution_failure;
  };

template<typename T>
  struct require_rvalue_reference
    : std::add_rvalue_reference<T> { };

template<>
  struct require_rvalue_reference<void> {
    using type = substitution_failure;
  };

}	// namespace impl

template<typename T>
  using Require_lvalue_reference = typename impl::require_lvalue_reference<T>::type;

template<typename T>
  using Require_rvalue_reference = typename impl::require_rvalue_reference<T>::type;

template<typename T>
  using Decay = typename std::decay<T>::type;

// This is a workaround from Origin to make sure that Make_signed and Make_unsigned
// return substitution_failure if T is not an integral type.

namespace impl {

template<typename T,
         bool = Integral<T>()>
  struct make_signed
    : std::make_signed<T> { };

template<typename T>
  struct make_signed<T, false> {
    using type = substitution_failure;
  };

template<typename T,
         bool = Integral<T>()>
  struct make_unsigned
    : std::make_unsigned<T> { };

template<typename T>
  struct make_unsigned<T, false> {
    using type = substitution_failure;
  };

}	// namespace impl

template<typename T>
  using Make_signed = typename impl::make_signed<T>::type;

template<typename T>
  using Make_unsigned = typename impl::make_unsigned<T>::type;

template<typename T>
  using Remove_extent = typename std::remove_extent<T>::type;

template<typename T>
  using Remove_all_extents = typename std::remove_all_extents<T>::type;

// TODO: Alignments.

template<bool B, typename T = void>
  using Enable_if = typename std::enable_if<B, T>::type;

template<bool B, typename T, typename F>
  using Conditional = typename std::conditional<B, T, F>::type;

template<typename... Args>
  using Common_type = typename std::common_type<Args...>::type;

template<typename T>
  using Underlying_type = typename std::underlying_type<T>::type;

// I can't seem to get std::result_of in GCC to work correctly.
// I don't know if this is due to an error in my understanding, or in the implementation.
// I'm using Origin's implementation instead.
#include "impl/result_of.h"

// Result_of - C stands for callable type.
template<typename C>
  using Result_of = typename impl::result_of<C>::type;

template<typename F, typename... Args>
  constexpr bool Has_call()
  {
    return Substitution_succeeded<Result_of<F(Args...)>>();
  }

// Tests for operators; result types of operators.

#include "impl/operators.h"

template<typename T, typename U>
  using Subscript_result = typename impl::get_subscript_result<T, U>::type;

template<typename T, typename U>
  constexpr bool Has_subscript()
  {
    return Substitution_succeeded<Subscript_result<T, U>>();
  }

template<typename T>
  using Post_increment_result = typename impl::get_post_increment_result<T>::type;

template<typename T>
  constexpr bool Has_post_increment()
  {
    return Substitution_succeeded<Post_increment_result<T>>();
  }

template<typename T>
  using Post_decrement_result = typename impl::get_post_decrement_result<T>::type;

template<typename T>
  constexpr bool Has_post_decrement()
  {
    return Substitution_succeeded<Post_decrement_result<T>>();
  }

template<typename T>
  using Pre_increment_result = typename impl::get_pre_increment_result<T>::type;

template<typename T>
  constexpr bool Has_pre_increment()
  {
    return Substitution_succeeded<Pre_increment_result<T>>();
  }

template<typename T>
  using Pre_decrement_result = typename impl::get_pre_decrement_result<T>::type;

template<typename T>
  constexpr bool Has_pre_decrement()
  {
    return Substitution_succeeded<Pre_decrement_result<T>>();
  }

template<typename T>
  using Complement_result = typename impl::get_complement_result<T>::type;

template<typename T>
  constexpr bool Has_complement()
  {
    return Substitution_succeeded<Complement_result<T>>();
  }

template<typename T>
  using Not_result = typename impl::get_not_result<T>::type;

template<typename T>
  constexpr bool Has_not()
  {
    return Substitution_succeeded<Not_result<T>>();
  }

template<typename T>
  using Unary_minus_result = typename impl::get_unary_minus_result<T>::type;

template<typename T>
  constexpr bool Has_unary_minus()
  {
    return Substitution_succeeded<Unary_minus_result<T>>();
  }

template<typename T>
  using Unary_plus_result = typename impl::get_unary_plus_result<T>::type;

template<typename T>
  constexpr bool Has_unary_plus()
  {
    return Substitution_succeeded<Unary_plus_result<T>>();
  }

template<typename T>
  using Address_of_result = typename impl::get_address_of_result<T>::type;

template<typename T>
  constexpr bool Has_address_of()
  {
    return Substitution_succeeded<Address_of_result<T>>();
  }

template<typename T>
  using Dereference_result = typename impl::get_dereference_result<T>::type;

template<typename T>
  constexpr bool Has_dereference()
  {
    return Substitution_succeeded<Dereference_result<T>>();
  }

template<typename T, typename U = T>
  using Multiply_result = typename impl::get_multiply_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_multiply()
  {
    return Substitution_succeeded<Multiply_result<T, U>>();
  }

template<typename T, typename U = T>
  using Divide_result = typename impl::get_divide_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_divide()
  {
    return Substitution_succeeded<Divide_result<T, U>>();
  }

template<typename T, typename U = T>
  using Modulo_result = typename impl::get_modulo_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_modulo()
  {
    return Substitution_succeeded<Modulo_result<T, U>>();
  }

template<typename T, typename U = T>
  using Plus_result = typename impl::get_plus_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_plus()
  {
    return Substitution_succeeded<Plus_result<T, U>>();
  }

template<typename T, typename U = T>
  using Minus_result = typename impl::get_minus_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_minus()
  {
    return Substitution_succeeded<Minus_result<T, U>>();
  }

template<typename T, typename U = T>
  using Left_shift_result = typename impl::get_left_shift_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_left_shift()
  {
    return Substitution_succeeded<Left_shift_result<T, U>>();
  }

template<typename T, typename U = T>
  using Right_shift_result = typename impl::get_right_shift_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_right_shift()
  {
    return Substitution_succeeded<Right_shift_result<T, U>>();
  }

template<typename T, typename U = T>
  using Less_result = typename impl::get_less_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_less()
  {
    return Substitution_succeeded<Less_result<T, U>>();
  }

template<typename T, typename U = T>
  using Greater_result = typename impl::get_greater_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_greater()
  {
    return Substitution_succeeded<Greater_result<T, U>>();
  }

template<typename T, typename U = T>
  using Less_equal_result = typename impl::get_less_equal_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_less_equal()
  {
    return Substitution_succeeded<Less_equal_result<T, U>>();
  }

template<typename T, typename U = T>
  using Greater_equal_result = typename impl::get_greater_equal_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_greater_equal()
  {
    return Substitution_succeeded<Greater_equal_result<T, U>>();
  }

template<typename T, typename U = T>
  using Equal_result = typename impl::get_equal_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_equal()
  {
    return Substitution_succeeded<Equal_result<T, U>>();
  }

template<typename T, typename U = T>
  using Not_equal_result = typename impl::get_not_equal_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_not_equal()
  {
    return Substitution_succeeded<Not_equal_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_and_result = typename impl::get_bitwise_and_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_and()
  {
    return Substitution_succeeded<Bitwise_and_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_xor_result = typename impl::get_bitwise_xor_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_xor()
  {
    return Substitution_succeeded<Bitwise_xor_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_or_result = typename impl::get_bitwise_or_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_or()
  {
    return Substitution_succeeded<Bitwise_or_result<T, U>>();
  }

template<typename T, typename U = T>
  using And_result = typename impl::get_and_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_and()
  {
    return Substitution_succeeded<And_result<T, U>>();
  }

template<typename T, typename U = T>
  using Or_result = typename impl::get_or_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_or()
  {
    return Substitution_succeeded<Or_result<T, U>>();
  }

template<typename T, typename U = T>
  using Multiply_assign_result = typename impl::get_multiply_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_multiply_assign()
  {
    return Substitution_succeeded<Multiply_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Divide_assign_result = typename impl::get_divide_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_divide_assign()
  {
    return Substitution_succeeded<Divide_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Modulo_assign_result = typename impl::get_modulo_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_modulo_assign()
  {
    return Substitution_succeeded<Modulo_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Plus_assign_result = typename impl::get_plus_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_plus_assign()
  {
    return Substitution_succeeded<Plus_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Minus_assign_result = typename impl::get_minus_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_minus_assign()
  {
    return Substitution_succeeded<Minus_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Left_shift_assign_result = typename impl::get_left_shift_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_left_shift_assign()
  {
    return Substitution_succeeded<Left_shift_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Right_shift_assign_result = typename impl::get_right_shift_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_right_shift_assign()
  {
    return Substitution_succeeded<Right_shift_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_and_assign_result = typename impl::get_bitwise_and_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_and_assign()
  {
    return Substitution_succeeded<Bitwise_and_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_or_assign_result = typename impl::get_bitwise_or_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_or_assign()
  {
    return Substitution_succeeded<Bitwise_or_assign_result<T, U>>();
  }

template<typename T, typename U = T>
  using Bitwise_xor_assign_result = typename impl::get_bitwise_xor_assign_result<T, U>::type;

template<typename T, typename U = T>
  constexpr bool Has_bitwise_xor_assign()
  {
    return Substitution_succeeded<Bitwise_xor_assign_result<T, U>>();
  }

// Is static_cast<U>(t) a valid expression?
template<typename T, typename U>
  constexpr bool Static_castable()
  {
    return Substitution_succeeded<typename impl::get_static_cast_result<T, U>::type>();
  }

// Handle the overloaded stream operators.
#include "impl/streamable.h"

template<typename T, typename U = default_t>
  constexpr bool Output_streamable()
  {
    return impl::is_output_streamable<T, U>::value;
  }

template<typename T, typename U = default_t>
  constexpr bool Input_streamable()
  {
    return impl::is_input_streamable<T, U>::value;
  }

// Container support.
#include "impl/container.h"

template<typename T>
  using Associated_value_type = typename impl::get_associated_value_type<T>::type;

template<typename T>
  constexpr bool Has_associated_value_type()
  {
    return Substitution_succeeded<Associated_value_type<T>>();
  }

template<typename T>
  using Associated_allocator_type = typename impl::get_associated_allocator_type<T>::type;

template<typename T>
  constexpr bool Has_associated_allocator_type()
  {
    return Substitution_succeeded<Associated_allocator_type<T>>();
  }

template<typename T>
  using Associated_size_type = typename impl::get_associated_size_type<T>::type;

template<typename T>
  constexpr bool Has_associated_size_type()
  {
    return Substitution_succeeded<Associated_size_type<T>>();
  }

template<typename T>
  using Associated_difference_type = typename impl::get_associated_difference_type<T>::type;

template<typename T>
  constexpr bool Has_associated_difference_type()
  {
    return Substitution_succeeded<Associated_difference_type<T>>();
  }

template<typename T>
  using Associated_iterator = typename impl::get_associated_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_iterator()
  {
    return Substitution_succeeded<Associated_iterator<T>>();
  }

template<typename T>
  using Associated_const_iterator = typename impl::get_associated_const_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_const_iterator()
  {
    return Substitution_succeeded<Associated_const_iterator<T>>();
  }

template<typename T>
  using Associated_reverse_iterator = typename impl::get_associated_reverse_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_reverse_iterator()
  {
    return Substitution_succeeded<Associated_reverse_iterator<T>>();
  }

template<typename T>
  using Associated_const_reverse_iterator = typename impl::get_associated_const_reverse_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_const_reverse_iterator()
  {
    return Substitution_succeeded<Associated_const_reverse_iterator<T>>();
  }

template<typename T>
  using Associated_reference = typename impl::get_associated_reference<T>::type;

template<typename T>
  constexpr bool Has_associated_reference()
  {
    return Substitution_succeeded<Associated_reference<T>>();
  }

template<typename T>
  using Associated_const_reference = typename impl::get_associated_const_reference<T>::type;

template<typename T>
  constexpr bool Has_associated_const_reference()
  {
    return Substitution_succeeded<Associated_const_reference<T>>();
  }

template<typename T>
  using Associated_pointer = typename impl::get_associated_pointer<T>::type;

template<typename T>
  constexpr bool Has_associated_pointer()
  {
    return Substitution_succeeded<Associated_pointer<T>>();
  }

template<typename T>
  using Associated_const_pointer = typename impl::get_associated_const_pointer<T>::type;

template<typename T>
  constexpr bool Has_associated_const_pointer()
  {
    return Substitution_succeeded<Associated_const_pointer<T>>();
  }

template<typename T>
  using Associated_key_type = typename impl::get_associated_key_type<T>::type;

template<typename T>
  constexpr bool Has_associated_key_type()
  {
    return Substitution_succeeded<Associated_key_type<T>>();
  }

template<typename T>
  using Associated_mapped_type = typename impl::get_associated_mapped_type<T>::type;

template<typename T>
  constexpr bool Has_associated_mapped_type()
  {
    return Substitution_succeeded<Associated_mapped_type<T>>();
  }

template<typename T>
  using Associated_key_compare = typename impl::get_associated_key_compare<T>::type;

template<typename T>
  constexpr bool Has_associated_key_compare()
  {
    return Substitution_succeeded<Associated_key_compare<T>>();
  }

template<typename T>
  using Associated_hasher = typename impl::get_associated_hasher<T>::type;

template<typename T>
  constexpr bool Has_associated_hasher()
  {
    return Substitution_succeeded<Associated_hasher<T>>();
  }

template<typename T>
  using Associated_key_equal = typename impl::get_associated_key_equal<T>::type;

template<typename T>
  constexpr bool Has_associated_key_equal()
  {
    return Substitution_succeeded<Associated_key_equal<T>>();
  }

template<typename T>
  using Associated_local_iterator = typename impl::get_associated_local_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_local_iterator()
  {
    return Substitution_succeeded<Associated_local_iterator<T>>();
  }

template<typename T>
  using Associated_const_local_iterator = typename impl::get_associated_const_local_iterator<T>::type;

template<typename T>
  constexpr bool Has_associated_const_local_iterator()
  {
    return Substitution_succeeded<Associated_const_local_iterator<T>>();
  }

template<typename T>
  using Member_size_result = typename impl::get_member_size_result<T>::type;

template<typename T>
  constexpr bool Has_member_size()
  {
    return Substitution_succeeded<Member_size_result<T>>();
  }

template<typename T>
  constexpr bool Has_member_empty()
  {
    return impl::has_member_empty<T>::value;
  }

template<typename T>
  constexpr bool Has_member_max_size()
  {
    return impl::has_member_max_size<T>::value;
  }

template<typename T>
  constexpr bool Has_member_capacity()
  {
    return impl::has_member_capacity<T>::value;
  }

template<typename T>
  constexpr bool Has_member_reserve()
  {
    return impl::has_member_reserve<T>::value;
  }

template<typename T>
  constexpr bool Has_member_resize()
  {
    return impl::has_member_resize<T>::value;
  }

template<typename T>
  constexpr bool Has_member_shrink_to_fit()
  {
    return impl::has_member_shrink_to_fit<T>::value;
  }

template<typename T>
  constexpr bool Has_member_clear()
  {
    return impl::has_member_clear<T>::value;
  }

template<typename T>
  using Member_front = typename impl::get_member_front_result<T>::type;

template<typename T>
  constexpr bool Has_member_front()
  {
    return Substitution_succeeded<Member_front<T>>();
  }

template<typename T>
  using Member_back = typename impl::get_member_back_result<T>::type;

template<typename T>
  constexpr bool Has_member_back()
  {
    return Substitution_succeeded<Member_back<T>>();
  }

template<typename T>
  using Member_at = typename impl::get_member_at_result<T>::type;

template<typename T>
  constexpr bool Has_member_at()
  {
    return Substitution_succeeded<Member_at<T>>();
  }

// Forward declaration.
template<typename T>
  struct difference_type_traits;

template<typename T>
  using Difference_type = typename difference_type_traits<T>::type;

template<typename T>
  constexpr bool Has_difference_type()
  {
    return Substitution_succeeded<Difference_type<T>>();
  }

// Traits which include type deduction for cases in which associated types are not defined.
#include "impl/one_size_up.h"		// utitlity - get a type of next larger size.
#include "impl/deduced_types.h"

// A user who wants to bypass the deduction mechanism only needs to specialize difference_type_traits.
template<typename T>
  struct difference_type_traits {
    using type = typename impl::get_deduced_difference_type<T>::type;
  };

template<typename T>
  using Reference_of = typename impl::get_deduced_reference<T>::type;

template<typename T>
  constexpr bool Has_reference()
  {
    return Substitution_succeeded<Reference_of<T>>();
  }

template<typename T>
  using Size_type = typename impl::get_deduced_size_type<T>::type;

template<typename T>
  constexpr bool Has_size_type()
  {
    return Substitution_succeeded<Size_type<T>>();
  }

template<typename T>
  using Value_type = typename impl::get_deduced_value_type<T>::type;

template<typename T>
  constexpr bool Has_value_type()
  {
    return Substitution_succeeded<Value_type<T>>();
  }

template<typename T>
  using Pointer_of = typename impl::get_deduced_pointer<T>::type;

template<typename T>
  constexpr bool Has_pointer()
  {
    return Substitution_succeeded<Pointer_of<T>>();
  }

}	// namespace Estd

#endif	// TRAITS_H
