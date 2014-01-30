#ifndef META_SUPPORT_H
#define META_SUPPORT_H

#include <type_traits>

namespace Estd {

// GCC implements std::integral_constant, and it is used in Origin.
// However, I can't find it either in the book or in the standard.
// So I give an implementation of it here.
template<typename T, T v>
  struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T, v>;
    constexpr operator value_type() { return value; }
  };

// Adaptations from Origin for convenience.

template<bool B>
  using boolean_constant = integral_constant<bool, B>;

template<std::size_t N>
  using size_constant = integral_constant<std::size_t, N>;

// From pg. 800

struct substitution_failure { };

template<typename T>
  struct substitution_succeeded
    : std::true_type { };

template<>
  struct substitution_succeeded<substitution_failure>
    : std::false_type { };

// Adapted from Origin.

template<typename T>
  constexpr bool Substitution_succeeded()
  {
    return substitution_succeeded<T>::value;
  }

}	// namespace Estd

#endif	// META_SUPPORT_H
