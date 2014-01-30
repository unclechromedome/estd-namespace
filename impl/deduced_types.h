#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

// In the event that a type doesn't have an associated type (e.g., value_type),
// we can try to deduce type trait we're looking for.

// Note that default_t is used for argument dependent lookup (ADL).
// It causes Estd to be searched for these functions.

// How it works.
// This is essentially the same technique used in operators.h - just unwrapped.
// If the check() function is going to appear outside a struct, then it has to be renamed
// for each test. The functions deduce_value_type(), deduce_size_type(), etc., perform the
// same role as a check() function.
// Note how these functions are *only* used in a decltype in get_deduced_value_type,
// get_deduced_size_type, etc.
// The reason for "unwrapping" things in this way is to allow a user to provide
// overloads for the deduce_X() functions, thereby providing his own extensions to this facility.
// For instance, if a user provides an overload to deduce_value_type(), then his extensions
// will be accessed through the Value_type<T> interface.
//
// If the conventional struct were used, a user couldn't overload the check() function
// without modifying library code.

namespace impl {

// Deduce value type.

substitution_failure deduce_value_type(...);

// If we can dereference the type, then the value type is the result of that dereference
// with any reference and cv-qualifiers removed.
template<typename T>
  auto deduce_value_type(default_t, const T&)
    -> Enable_if<Has_dereference<T>(), Remove_cv<Remove_reference<Dereference_result<T>>>>;

template<typename T,
         bool = Has_associated_value_type<T>()>
  struct get_deduced_value_type;

template<typename T>
  struct get_deduced_value_type<T, true> {
    using type = Associated_value_type<T>;
  };

template<typename T>
  struct get_deduced_value_type<T, false> {
    using type = decltype(deduce_value_type(default_t{}, std::declval<T>()));
  };

// Deduce size type.
// Try the following in order:
// member size_type
// member size()
// if Difference_type is defined, the unsigned version of that
// substitution_failure in every other case.

substitution_failure deduce_size_type(...);

template<typename T>
  auto deduce_size_type(default_t, const T& x)
    -> Enable_if<Has_member_size<T>(), Member_size_result<T>>;

template<typename T>
  auto deduce_size_type(default_t, const T& x)
    -> Enable_if<!Has_member_size<T>() && Has_difference_type<T>,
                 Make_unsigned<Difference_type<T>>()>;

template<typename T,
         bool = Has_associated_size_type<T>()>
  struct get_deduced_size_type;

template<typename T>
  struct get_deduced_size_type<T, true> {
    using type = Associated_size_type<T>;
  };

template<typename T>
  struct get_deduced_size_type<T, false> {
    using type = decltype(deduce_size_type(default_t{}, std::declval<T>()));
  };

// Deduce difference type.

substitution_failure deduce_difference_type(...);

// The difference type for pointers is std::ptrdiff_t.
template<typename T>
  std::ptrdiff_t deduce_difference_type(default_t, T*);

// The difference type for integral types is the signed representation of the next larger type.
template<typename T>
  auto deduce_difference_type(default_t, T)
    -> Enable_if<Integral<T>(), One_size_up<Make_signed<T>>>;

// The difference type for floating point types is that type.
template<typename T>
  auto deduce_difference_type(default_t, T)
    -> Enable_if<Floating_point<T>(), T>;

// For user defined types with a pre-increment operator, provide std::ptrdiff_t as a default guess.
template<typename T>
  auto deduce_difference_type(default_t, T)
    -> Enable_if<Class<T>() && Has_pre_increment<T>(), std::ptrdiff_t>;

template<typename T,
         bool = Has_associated_difference_type<T>()>
  struct get_deduced_difference_type;

template<typename T>
  struct get_deduced_difference_type<T, true> {
    using type = Associated_difference_type<T>;
  };

template<typename T>
  struct get_deduced_difference_type<T, false> {
    using type = decltype(deduce_difference_type(default_t{}, std::declval<T>()));
  };

// Deduce reference type.

substitution_failure deduce_reference(...);

// Default for any type supporting the dereference operator.
template<typename T>
  auto deduce_reference(default_t, T&& x) -> decltype(*x);

template<typename T,
         bool = Has_associated_reference<T>(),
	 bool = Has_associated_const_reference<T>()>
  struct get_deduced_reference;

// If a type provides both associated reference and const_reference,
// choose the appropriate one based on the constness of T.
template<typename T>
  struct get_deduced_reference<T, true, true> {
    using type = Conditional<
		   Const<Remove_reference<T>>(),
		   Associated_const_reference<T>,
		   Associated_reference<T>
                 >;
  };

template<typename T>
  struct get_deduced_reference<T, true, false> {
    using type = Associated_reference<T>;
  };

template<typename T>
  struct get_deduced_reference<T, false, true> {
    using type = Associated_const_reference<T>;
  };

template<typename T>
  struct get_deduced_reference<T, false, false> {
    using type = decltype(deduce_reference(default_t{}, std::declval<T>()));
  };

// Deduce pointer.

substitution_failure deduce_pointer(...);

// Default for any type supporting the dereference operator.
template<typename T>
  auto deduce_pointer(default_t, T&& x)
    -> Enable_if<Reference<decltype(*x)>(), decltype(&*x)>;

template<typename T,
         bool = Has_associated_pointer<T>(),
	 bool = Has_associated_const_pointer<T>()>
  struct get_deduced_pointer;

template<typename T>
  struct get_deduced_pointer<T, true, true> {
    using type = Conditional<
		   Const<Remove_reference<T>>(),
		   Associated_const_pointer<T>,
		   Associated_pointer<T>
                 >;
  };

template<typename T>
  struct get_deduced_pointer<T, true, false> {
    using type = Associated_pointer<T>;
  };

template<typename T>
  struct get_deduced_pointer<T, false, true> {
    using type = Associated_const_pointer<T>;
  };

template<typename T>
  struct get_deduced_pointer<T, false, false> {
    using type = decltype(deduce_pointer(default_t{}, std::declval<T>()));
  };

}	// namespace impl
