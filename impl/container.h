#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

// Container member types - pg. 896.

// These type functions all work in the same way as the ones defined in operators.h
// However, even though check() typically has a const X& parameter, we don't use
// a std::declval<const T&>. This is because it is semantically correct to
// pass a class as a const T& and use it as a T; if we were doing more than just
// getting a return type, we would do this to prevent copying.

namespace impl {

template<typename T>
  struct get_associated_value_type {
  private:
    template<typename X>
      static typename X::value_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_allocator_type {
  private:
    template<typename X>
      static typename X::allocator_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_size_type {
  private:
    template<typename X>
      static typename X::size_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_difference_type {
  private:
    template<typename X>
      static typename X::difference_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_iterator {
  private:
    template<typename X>
      static typename X::iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_const_iterator {
  private:
    template<typename X>
      static typename X::const_iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_reverse_iterator {
  private:
    template<typename X>
      static typename X::reverse_iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_const_reverse_iterator {
  private:
    template<typename X>
      static typename X::const_reverse_iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_reference {
  private:
    template<typename X>
      static typename X::reference check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_const_reference {
  private:
    template<typename X>
      static typename X::const_reference check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_pointer {
  private:
    template<typename X>
      static typename X::pointer check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_const_pointer {
  private:
    template<typename X>
      static typename X::const_pointer check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_key_type {
  private:
    template<typename X>
      static typename X::key_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_mapped_type {
  private:
    template<typename X>
      static typename X::mapped_type check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_key_compare {
  private:
    template<typename X>
      static typename X::key_compare check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_hasher {
  private:
    template<typename X>
      static typename X::hasher check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_key_equal {
  private:
    template<typename X>
      static typename X::key_equal check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_local_iterator {
  private:
    template<typename X>
      static typename X::local_iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_associated_const_local_iterator {
  private:
    template<typename X>
      static typename X::const_local_iterator check(const X&);
    
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

// Size and capacity - pg. 898

template<typename T>
  struct get_member_size_result {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.size());

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct has_member_empty {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.empty());

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_max_size {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.max_size());

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_capacity {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.capacity());

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_reserve {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.reserve(std::declval<int>()));

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_resize {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.resize(std::declval<int>()));

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_shrink_to_fit {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.shrink_to_fit());

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

template<typename T>
  struct has_member_clear {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.clear());

    static substitution_failure check(...);

    using type = decltype(check(std::declval<T>()));

  public:
    static constexpr bool value = Substitution_succeeded<type>();
  };

// Element access - pg. 900

template<typename T>
  struct get_member_front_result {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.front());
  
    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_member_back_result {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.back());

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_member_at_result {
  private:
    template<typename X>
      static auto check(const X& x) -> decltype(x.at(std::declval<int>()));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

}	// namespace impl
