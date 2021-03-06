#ifndef _VECTOR_OPS_H_
#define _VECTOR_OPS_H_

#include "utils.h"

namespace ndarray {

template <typename T> struct is_node { static const bool value = false; };

template <typename T> struct store_type {
  using type = typename std::conditional<std::is_fundamental<T>::value ||
                                             std::is_pointer<T>::value,
                                         T, const T &>::type;
};

// Binary Ops
struct add_op {};

template <typename T1, typename T2>
struct is_node<utils::tuple<add_op, T1, T2>> {
  static const bool value = true;
};

template <typename T1, typename T2>
struct store_type<utils::tuple<add_op, T1, T2>> {
  using type = utils::tuple<add_op, T1, T2>;
};

template <typename T1, typename T2>
typename std::enable_if<is_node<T1>::value || is_node<T2>::value,
                        utils::tuple<add_op, typename store_type<T1>::type,
                                     typename store_type<T2>::type>>::type
operator+(const T1 &a, const T2 &b) {
  return utils::tuple<add_op, typename store_type<T1>::type,
                      typename store_type<T2>::type>(add_op(), a, b);
}

struct sub_op {};

template <typename T1, typename T2>
struct is_node<utils::tuple<sub_op, T1, T2>> {
  static const bool value = true;
};

template <typename T1, typename T2>
struct store_type<utils::tuple<sub_op, T1, T2>> {
  using type = utils::tuple<sub_op, T1, T2>;
};

template <typename T1, typename T2>
typename std::enable_if<is_node<T1>::value || is_node<T2>::value,
                        utils::tuple<sub_op, typename store_type<T1>::type,
                                     typename store_type<T2>::type>>::type
operator-(const T1 &a, const T2 &b) {
  return utils::tuple<sub_op, typename store_type<T1>::type,
                      typename store_type<T2>::type>(sub_op(), a, b);
}

// Unary Ops
struct sqrt_op {};

template <typename T1>
struct is_node<utils::tuple<sqrt_op, T1>> {
  static const bool value = true;
};

template <typename T1>
struct store_type<utils::tuple<sqrt_op, T1>> {
  using type = utils::tuple<sqrt_op, T1>;
};

template <typename T1>
typename std::enable_if<is_node<T1>::value,
                        utils::tuple<sqrt_op, typename store_type<T1>::type>>::type
sqrt(const T1 &a) {
  return utils::tuple<sqrt_op, typename store_type<T1>::type>(sqrt_op(), a);
}

} // end of namespace ndarray

#endif // _VECTOR_OPS_H_
