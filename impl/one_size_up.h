#ifndef TRAITS_H
#error This file cannot be included directly. Include traits.h
#endif	// TRAITS_H

namespace impl {

// one_size_up
// Take an integral type and return the type with the next larger size.
// Returns substitution_failure if the type is not integral.

template<typename T,
         bool = Integral<T>(),
	 bool = Signed<T>()>
  struct one_size_up {
    using type = substitution_failure;
  };

template<typename T>
  struct one_size_up<T, true, true> {
  private:
    static constexpr bool b1 = sizeof(T) < sizeof(signed short);
    static constexpr bool b2 = sizeof(T) < sizeof(signed int);
    static constexpr bool b3 = sizeof(T) < sizeof(signed long);
    static constexpr bool b4 = sizeof(T) < sizeof(signed long long);

    using type4 = Conditional<b4, signed long long, T>;
    using type3 = Conditional<b3, signed long, type4>;
    using type2 = Conditional<b2, signed int, type3>;
    using type1 = Conditional<b1, signed short, type2>;

  public:
    using type = type1;
  };

template<typename T>
  struct one_size_up<T, true, false> {
  private:
    static constexpr bool b1 = sizeof(T) < sizeof(unsigned short);
    static constexpr bool b2 = sizeof(T) < sizeof(unsigned int);
    static constexpr bool b3 = sizeof(T) < sizeof(unsigned long);
    static constexpr bool b4 = sizeof(T) < sizeof(unsigned long long);

    using type4 = Conditional<b4, unsigned long long, T>;
    using type3 = Conditional<b3, unsigned long, type4>;
    using type2 = Conditional<b2, unsigned int, type3>;
    using type1 = Conditional<b1, unsigned short, type2>;

  public:
    using type = type1;
  };

template<typename T>
  using One_size_up = typename one_size_up<T>::type;

}	// namespace impl
