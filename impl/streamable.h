#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

// These type functions work in the same way as the ones in operators.h
// Note that in the specializations of is_output_streamable and is_input_streamable
// we had to "switch" the parameters. This is because a default parameter has to be
// a trailing argument.

namespace impl {

// Is s << t a valid stream output expression?
template<typename S, typename T>
  struct get_output_stream_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, const Y& y) -> decltype(x << y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<S&>(), std::declval<const T&>()));
  };

template<typename S, typename T>
  struct is_output_streamable
    : boolean_constant<
        Substitution_succeeded<typename get_output_stream_result<S, T>::type>()
      > { };

// We only use default_t here because we need two template arguments.
template<typename T>
  struct is_output_streamable<T, default_t>
    : is_output_streamable<std::ostream, T> { };

// Is s >> t a valid stream input expression?
template<typename S, typename T>
  struct get_input_stream_result {
  private:
    template<typename X, typename Y>
      static auto check(X& x, Y& y) -> decltype(x >> y);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<S&>(), std::declval<T&>()));
  };

template<typename S, typename T>
  struct is_input_streamable
    : boolean_constant<
        Substitution_succeeded<typename get_input_stream_result<S, T>::type>()
      > { };

template<typename T>
  struct is_input_streamable<T, default_t>
    : is_input_streamable<std::istream, T> { };

}	// namespace impl
