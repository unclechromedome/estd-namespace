#ifndef ESTD_H
#define ESTD_H

// Please see the README file regarding licensing information.

// estd.h by Chris French.
// A lot of this code comes from the Origin library.
// However, the result it a bit different, because my focus was implementing
// the constraints checks on pg. 716 of The C++ Programming Language, Fourth Edition.
//
// I did make some minor additions that were not in Origin, such as Associated_key_type<>
// and Associated_mapped_type<>.
//
// I also fixed some bugs existing in Origin as of January 2014.
// For example, is_equality_comparable had
//   Has_not_equal<T, U>() && Boolean<Equal_result<T, U>>,
// which should be
//   Has_not_equal<T, U>() && Boolean<Not_equal_result<T, U>>.
// Also, in Origin, Weakly_ordered is defined in terms of Totally_ordered when it was clearly
// meant to be defined recursively in terms of Weakly_ordered.
//
// In the iterator constraints checks, I added Has_iterator_category<I>
// before doing something like Derived<Iterator_category<I>, std::forward_iterator_tag>.
//
// In addition, I addressed a couple of Andrew Sutton's FIXMEs. In particular,
// Size_type<> now uses the unsigned version of Difference_type<> if there is no size_type or size(),
// and Difference_type<> now returns the next larger size for integral types.
//
// None of this is of my own innovation. It is a result of what I have learned from The C++ Programming
// Language, the Origin library, and the type_traits file provided with GCC 4.8.
// My modifications and fixes are minor compared to the scope of the Origin library.

#include "traits.h"
#include "constraints.h"

#endif	// ESTD_H
