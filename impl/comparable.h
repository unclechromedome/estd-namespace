#ifndef CONSTRAINTS_H
#error This file cannot be included directly. Include constraints.h
#endif	// CONSTRAINTS_H

namespace impl {

template<typename T, typename U>
  struct is_equality_comparable
    : boolean_constant<
           Common<T, U>()
        && Equality_comparable<T>()
	&& Equality_comparable<U>()
	&& Equality_comparable<Common_type<T, U>>()
	&& Has_equal<T, U>()     && Boolean<Equal_result<T, U>>()
	&& Has_equal<U, T>()     && Boolean<Equal_result<U, T>>()
	&& Has_not_equal<T, U>() && Boolean<Not_equal_result<T, U>>()
	&& Has_not_equal<U, T>() && Boolean<Not_equal_result<U, T>>()
      > { };

template<typename T>
  struct is_equality_comparable<T, T>
    : boolean_constant<
	   Has_equal<T>()     && Boolean<Equal_result<T>>()
        && Has_not_equal<T>() && Boolean<Not_equal_result<T>>()
      > { };

template<typename T, typename U>
  struct is_weakly_ordered
    : boolean_constant<
           Common<T, U>()
        && Weakly_ordered<T>()
	&& Weakly_ordered<U>()
	&& Weakly_ordered<Common_type<T, U>>()
	&& Has_less<T, U>()          && Boolean<Less_result<T, U>>()
	&& Has_less<U, T>()          && Boolean<Less_result<U, T>>()
	&& Has_greater<T, U>()       && Boolean<Greater_result<T, U>>()
	&& Has_greater<U, T>()       && Boolean<Greater_result<U, T>>()
	&& Has_less_equal<T, U>()    && Boolean<Less_equal_result<T, U>>()
	&& Has_less_equal<U, T>()    && Boolean<Less_equal_result<U, T>>()
        && Has_greater_equal<T, U>() && Boolean<Greater_equal_result<T, U>>()
        && Has_greater_equal<U, T>() && Boolean<Greater_equal_result<U, T>>()
      > { };

template<typename T>
  struct is_weakly_ordered<T, T>
    : boolean_constant<
	   Has_less<T>()          && Boolean<Less_result<T>>()
	&& Has_greater<T>()       && Boolean<Greater_result<T>>()
	&& Has_less_equal<T>()    && Boolean<Less_equal_result<T>>()
        && Has_greater_equal<T>() && Boolean<Greater_equal_result<T>>()
      > { };

}	// namespace impl
