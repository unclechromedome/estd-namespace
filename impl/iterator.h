namespace impl {

// Iterator traits - pg. 957
// The other iterator traits are also container properties, and are found there.
// Thus, we only need to handle iterator_category here.

// The technique used here is the same as the one in operators.h

template<typename T>
  struct get_associated_iterator_category {
  private:
    template<typename X>
      static typename X::iterator_category check(const X&);

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct iterator_category_traits {
    using type = typename get_associated_iterator_category<T>::type;
  };

// Specialization for pointers.
template<typename T>
  struct iterator_category_traits<T*> {
    using type = std::random_access_iterator_tag;
  };

// Make sure we can get iterator_category through reference types.
template<typename T>
  struct iterator_category_traits<T&>
    : iterator_category_traits<T> { };

template<typename T>
  struct iterator_category_traits<T&&>
    : iterator_category_traits<T> { };

template<typename T>
  struct get_std_begin_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(std::begin(x));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  constexpr bool Has_std_begin()
  {
    return Substitution_succeeded<typename get_std_begin_result<T>::type>();
  }

template<typename T>
  struct get_std_end_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(std::end(x));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  constexpr bool Has_std_end()
  {
    return Substitution_succeeded<typename get_std_end_result<T>::type>();
  }

template<typename T>
  struct get_adl_begin_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(begin(x));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T>
  struct get_adl_end_result {
  private:
    template<typename X>
      static auto check(X&& x) -> decltype(end(x));

    static substitution_failure check(...);

  public:
    using type = decltype(check(std::declval<T>()));
  };

template<typename T,
         bool = Has_std_begin<T>()>
  struct get_begin_result;

template<typename T>
  struct get_begin_result<T, true> {
    using type = typename get_std_begin_result<T>::type;
  };

template<typename T>
  struct get_begin_result<T, false> {
    using type = typename get_adl_begin_result<T>::type;
  };

template<typename T,
         bool = Has_std_end<T>()>
  struct get_end_result;

template<typename T>
  struct get_end_result<T, true> {
    using type = typename get_std_end_result<T>::type;
  };

template<typename T>
  struct get_end_result<T, false> {
    using type = typename get_adl_end_result<T>::type;
  };

}	// namespace impl
