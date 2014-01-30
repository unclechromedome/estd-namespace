#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "traits.h"
#include <iterator>

namespace Estd {

template<typename... Args>
  constexpr bool Common()
  {
    return Substitution_succeeded<Common_type<Args...>>();
  }

template<typename T>
  constexpr bool Boolean()
  {
    return Convertible<T, bool>();
  }

// Forward declarations.
namespace impl {

template<typename T, typename U>
  struct is_equality_comparable;

template<typename T, typename U>
  struct is_weakly_ordered;

}	// namespace impl

template<typename T, typename U = T>
  constexpr bool Equality_comparable()
  {
    return impl::is_equality_comparable<T, U>::value;
  }

template<typename T, typename U = T>
  constexpr bool Weakly_ordered()
  {
    return impl::is_weakly_ordered<T, U>::value;
  }

template<typename T, typename U = T>
  constexpr bool Totally_ordered()
  {
    return Weakly_ordered<T>() && Equality_comparable<T>();
  }

// Implementation of is_equality_comparable and is_weakly_ordered.
#include "impl/comparable.h"

template<typename T>
  constexpr bool Movable()
  {
    return Destructible<T>()
        && Move_constructible<T>()
	&& Move_assignable<T>();
  }

template<typename T>
  constexpr bool Copyable()
  {
    return Movable<T>()
        && Copy_constructible<T>()
	&& Copy_assignable<T>();
  }

template<typename T>
  constexpr bool Semiregular()
  {
    return Copyable<T>() && Destructible<T>();
  }

template<typename T>
  constexpr bool Regular()
  {
    return Semiregular<T>() && Equality_comparable<T>();
  }

template<typename T>
  constexpr bool Ordered()
  {
    return Regular<T>() && Totally_ordered<T>();
  }

template<typename F, typename... Args>
  constexpr bool Predicate()
  {
    return Copy_constructible<F>()
        && Has_call<F(Args...)>()
	&& Boolean<Result_of<F(Args...)>>();
  }

template<typename T, typename U = default_t>
  constexpr bool Streamable()
  {
    return Input_streamable<T, U>() && Output_streamable<T, U>();
  }

#include "impl/iterator.h"

template<typename I>
  using Iterator_category = typename impl::iterator_category_traits<I>::type;

template<typename I>
  constexpr bool Has_iterator_category()
  {
    return Substitution_succeeded<Iterator_category<I>>();
  }

template<typename I>
  constexpr bool Readable()
  {
    using Ref = Require_lvalue_reference<Add_const<Value_type<I>>>;

    return Has_value_type<I>()
        && Has_dereference<I>()
	&& Convertible<Dereference_result<I>, Ref>();
  }

template<typename I, typename T>
  constexpr bool Writable()
  {
    return Assignable<Dereference_result<I>, T>();
  }

template<typename I>
  constexpr bool Incrementable()
  {
    return Regular<I>()
           
        // Difference_type<I> must be signed.
	&& Has_difference_type<I>()
	&& Signed<Difference_type<I>>()

	// ++i must return I&
	&& Has_pre_increment<I>()
	&& Same<Pre_increment_result<I>, I&>()

	// i++ must return I
	&& Has_post_increment<I>()
	&& Same<Post_increment_result<I>, I>();
  }

template<typename I>
 constexpr bool Decrementable()
 {
   return Incrementable<I>()

       // --i must return I&
       && Has_pre_decrement<I>()
       && Same<Pre_decrement_result<I>, I&>()

       // i-- must return I
       && Has_post_decrement<I>()
       && Same<Post_decrement_result<I>, I>();
 }

template<typename I, typename T>
  constexpr bool Iterator_kind()
  {
    return Has_iterator_category<I>()
        && Derived<Iterator_category<I>, T>();
  }

template<typename I>
  constexpr bool Input_iterator()
  {
    return Readable<I>()
        && Incrementable<I>()
	&& Iterator_kind<I, std::input_iterator_tag>();
  }

template<typename I, typename T>
  constexpr bool Output_iterator()
  {
    return Writable<I>()
	
	// We only care that these operators are present.
	// We don't care about the type they yield, because often the operations are meaningless.
        && Has_pre_increment<I>()
	&& Has_post_increment<I>()

	// But we do care if I really is an output iterator.
	&& Iterator_kind<I, std::output_iterator_tag>();
  }

template<typename I>
  constexpr bool Forward_iterator()
  {
    return Readable<I>()
        && Incrementable<I>()
	&& Iterator_kind<I, std::forward_iterator_tag>();
  }

template<typename I>
  constexpr bool Bidirectional_iterator()
  {
    return Readable<I>()
        && Decrementable<I>()
	&& Iterator_kind<I, std::bidirectional_iterator_tag>();
  }

template<typename I>
  constexpr bool Random_access_iterator()
  {
    using N = Difference_type<I>;

    return Readable<I>()
        && Decrementable<I>()

	// i[n] must return I's associated reference type.
	&& Has_subscript<I, N>()
	&& Same<Subscript_result<I, N>, Reference_of<I>>()

	// i += n must return I&.
	&& Has_plus_assign<I, N>()
	&& Same<Plus_assign_result<I, N>, I&>()

	// i -= n must return I&.
	&& Has_minus_assign<I, N>()
	&& Same<Minus_assign_result<I, N>, I&>()

	// i + n must return I.
	&& Has_plus<I, N>()
	&& Same<Plus_result<I, N>, I>()

	// n + i must return I.
	&& Has_plus<N, I>()
	&& Same<Plus_result<N, I>, I>()

	// i - n must return I.
	&& Has_minus<I, N>()
	&& Same<Minus_result<I, N>, I>()

	// n - i must return I.
	&& Has_minus<N, I>()
	&& Same<Minus_result<N, I>, I>()

	// i - j must return N.
	&& Has_minus<I>()
	&& Same<Minus_result<I>, N>()

	&& Iterator_kind<I, std::random_access_iterator_tag>();
  }

template<typename T>
  using Begin_result = typename impl::get_begin_result<T>::type;

template<typename T>
  constexpr bool Has_begin()
  {
    return Substitution_succeeded<Begin_result<T>>();
  }

template<typename T>
  using End_result = typename impl::get_end_result<T>::type;

template<typename T>
  constexpr bool Has_end()
  {
    return Substitution_succeeded<End_result<T>>();
  }

template<typename T>
  using Iterator_of = Begin_result<T>;

template<typename T>
  constexpr bool Iterator()
  {
    return Incrementable<T>()
        && Has_dereference<T>()
	&& Has_iterator_category<T>();
  }

template<typename T>
  constexpr bool Range()
  {
    return Has_begin<T>()
        && Has_end<T>()
	&& Same<Begin_result<T>(), End_result<T>()>()
	&& Iterator<Iterator_of<T>>();
  }

}	// namespace Estd

#endif	// CONSTRAINTS_H
