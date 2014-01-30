#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

// The technique for determining the result type of an expression comes from pg. 800.
// However, the actual code used here comes from the Origin library.

// How it works.
// Consider:
// 
// template<typename T, typename U>
//   struct get_plus_result {
//   private:
//     template<typename X, typename Y>
//       static auto check(X&& x, Y&& y) -> decltype(x + y);
// 
//     static substitution_failure check(...);
// 
//   public:
//     using type = decltype(check(std::declval<T>(), std::declval<U>()));
//   };
// 
// First of all, note that check() needs no body because it is *only* called within a decltype.
// decltype does not evaluate its argument.
// The rest depends on the idea of substitution failure. If x + y is a valid expression, then the
// template version of check() gets generated and participates in overload resolution. Since
// it's an exact match for the arguments, it gets selected. The type member gets the type of the
// result of the expression.
// If x + y is nonsense, the template check() doesn't get generated, and all the compiler sees
// is the non-template check() returning substitution_failure. So type gets set to substitution_failure.
// 
// When I first saw this in Origin, I wondered why the template check() paramaters were rvalue references.
// This is because declval() is defined as
// 
//   template<typename T>
//     Add_rvalue_reference<T> declval() noexcept;
// 
// i.e., declval() returns an rvalue reference.
// 
// In the case where an rvalue reference is not semantically correct (see the definition of
// get_plus_assign_result), we might use X& in check() and then std::declval<T&>() in the call to check().
// 
// The type of a check() paramater and the form of its corresponding declval argument should match the
// semantics of the expression used as the decltype argument in the return type of the check() function.

namespace impl {

// These are mostly just listed in order of precedence (pp 255-257)

// Is t[u] a valid expression?
template<typename T, typename U>
  struct get_subscript_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x[y]);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t++ a valid expression?
template<typename T>
  struct get_post_increment_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x++);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>()));
  };

// Is t-- a valid expression?
template<typename T>
  struct get_post_decrement_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x--);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>()));
  };

// Is ++t a valid expression?
template<typename T>
  struct get_pre_increment_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(--x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>()));
  };

// Is --t a valid expression?
template<typename T>
  struct get_pre_decrement_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(--x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>()));
  };

// Is ~t a valid expression?
template<typename T>
  struct get_complement_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(~x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is !t a valid expression?
template<typename T>
  struct get_not_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(!x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is -t a valid expression?
template<typename T>
  struct get_unary_minus_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(-x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is +t a valid expression?
template<typename T>
  struct get_unary_plus_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(+x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is &t a valid expression?
template<typename T>
  struct get_address_of_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(&x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is *t a valid expression?
template<typename T>
  struct get_dereference_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(*x);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Is t * u a valid expression?
template<typename T, typename U>
  struct get_multiply_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x * y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t / u a valid expression?
template<typename T, typename U>
  struct get_divide_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x / y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t % u a valid expression?
template<typename T, typename U>
  struct get_modulo_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x % y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t + u a valid expression?
template<typename T, typename U>
  struct get_plus_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x + y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t - u a valid expression?
template<typename T, typename U>
  struct get_minus_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x - y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t << u a valid expression?
template<typename T, typename U>
  struct get_left_shift_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x << y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t >> u a valid expression?
template<typename T, typename U>
  struct get_right_shift_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x >> y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t < u a valid expression?
template<typename T, typename U>
  struct get_less_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x < y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t > u a valid expression?
template<typename T, typename U>
  struct get_greater_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x > y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t <= u a valid expression?
template<typename T, typename U>
  struct get_less_equal_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x <= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t >= u a valid expression?
template<typename T, typename U>
  struct get_greater_equal_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x >= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t == u a valid expression?
template<typename T, typename U>
  struct get_equal_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x == y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t != u a valid expression?
template<typename T, typename U>
  struct get_not_equal_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x != y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t & u a valid expression?
template<typename T, typename U>
  struct get_bitwise_and_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x & y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t ^ u a valid expression?
template<typename T, typename U>
  struct get_bitwise_xor_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x ^ y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t | u a valid expression?
template<typename T, typename U>
  struct get_bitwise_or_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x | y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t && u a valid expression?
template<typename T, typename U>
  struct get_and_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x && y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t || u a valid expression?
template<typename T, typename U>
  struct get_or_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x || y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Is t *= u a valid expression?
template<typename T, typename U>
  struct get_multiply_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x *= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t /= u a valid expression?
template<typename T, typename U>
  struct get_divide_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x /= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t %= u a valid expression?
template<typename T, typename U>
  struct get_modulo_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x %= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t += u a valid expression?
template<typename T, typename U>
  struct get_plus_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x += y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t -= u a valid expression?
template<typename T, typename U>
  struct get_minus_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x -= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t <<= u a valid expression?
template<typename T, typename U>
  struct get_left_shift_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x <<= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t >>= u a valid expression?
template<typename T, typename U>
  struct get_right_shift_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x >>= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t &= u a valid expression?
template<typename T, typename U>
  struct get_bitwise_and_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x &= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t |= u a valid expression?
template<typename T, typename U>
  struct get_bitwise_or_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x |= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is t ^= u a valid expression?
template<typename T, typename U>
  struct get_bitwise_xor_assign_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y&& y) -> decltype(x ^= y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T&>(), std::declval<U>()));
  };

// Is static_cast<U>(t) a valid expression?
template<typename T, typename U>
  struct get_static_cast_result {
  private:
    template<typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(static_cast<Y>(x));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

}	// namespace impl
