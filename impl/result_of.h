#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

namespace impl {

// This implementation of result_of is borrowed directly from Origin by Andrew Sutton.

// invoke encapsulates all the ways in which a function can be invoked, according to 20.8.2
// of the C++11 standard.
// These are:
// (t1.*f)(t2, ..., tN)    where f is a pointer to a member function of a class T and t1 is an
//                         object whose type is T or T&, or D or D& if D is derived from T.
// ((*t1).*f)(t2, ..., tN) where f is a pointer to a member function of a class T and t1
//                         is not one of the types described in the previous item.
// t1.*f                   where f is a pointer to member data of a class T and t1 is an object
//                         of type T or T&, or D or D& if D is derived from T.
// (*t1).*f                where f is a pointer to member data of a class T and t1 is not of
//                         one of the types described in the previous item.
// f(t1, t2, ..., tN)      in all other cases.
//
// invoke provides overloads of a function fn which tests each invocation and returns its result type.
// invoke also provides an overload returning substitution_failure the argument to fn matches
// none of the invocations.

struct invoke {
  // Matches none of the invocations.
  static substitution_failure fn(...);

  // (t1.*f)(t2, ..., Tn)
  template<typename F, typename C, typename... Args>
    static auto fn(F f, C&& c, Args&&... args)
      -> decltype((std::forward<C>(c).*f)(std::forward<Args>(args)...));

  // ((*t1).*f)(t2, ..., tN)
  template<typename F, typename C, typename... Args>
    static auto fn(F f, C&& c, Args&&... args)
      -> decltype(((*std::forward<C>(c)).*f)(std::forward<Args>(args)...));

  // t1.*f
  template<typename F, typename C>
    static auto fn(F f, C&& c)
      -> decltype(std::forward<C>(c).*f);

  // (*t1).*f
  template<typename F, typename C>
    static auto fn(F f, C&& c)
      -> decltype((*std::forward<C>(c)).*f);

  // f(t1, t2, ..., tN)
  template<typename F, typename... Args>
    static auto fn(F&& f, Args... args)
      -> decltype(std::forward<F>(f)(std::forward<Args>(args)...));
};

// An interface for invoke::fn()
template<typename F, typename... Args>
  struct invoke_result {
    using type = decltype(invoke::fn(std::declval<F>(), std::declval<Args>()...));
  };

template<typename F>
  struct invoke_result<F> {
    using type = decltype(invoke::fn(std::declval<F>()));
  };

template<typename F, typename... Args>
  using Invoke = typename invoke_result<F, Args...>::type;

// result_of amounts to invoke_result restricted to a call expression type.

template<typename T>
  struct result_of {
    using type = substitution_failure;
  };

template<typename F, typename... Args>
  struct result_of<F(Args...)> {
    using type = Invoke<F, Args...>;
  };

// I'm not sure why this is necessary, but Andrew Sutton says it is.

template<typename... Args>
  struct result_of<void(Args...)> {
    using type = substitution_failure;
  };

}	// namespace impl
