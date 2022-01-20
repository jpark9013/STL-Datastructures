//
// Created by jpark9013 on 1/18/22.
//

#include "algorithm.h"
#include "numeric.h"

namespace stl {

template<typename it>
int64_t distance(it first, it last) {
  int64_t x = 0;
  while (first != last) {
    first++;
    x++;
  }
  return x;
}

template<typename it1, typename it2>
bool lexiographical_compare(it1 first1, it1 last1, it2 first2, it2 last2) {
  int64_t a = distance(first1, last1);
  int64_t b = distance(first2, last2);
  if (a > b) {
    return false;
  } else if (a < b) {
    return true;
  }

  while (first1 != last1) {
    if (*first1 > *first2) {
      return false;
    } else if (*first1 < *first2) {
      return true;
    }
    first1++;
    first2++;
  }

  return false;
}

template<typename T>
const T& min(const T &a, const T &b) {
  return a < b ? a : b;
}

template<typename T, typename Comp>
const T& min(const T &a, const T &b, Comp comp) {
  return comp(a, b) ? a : b;
}

template<typename T>
const T& max(const T &a, const T &b) {
  return a > b ? a : b;
}

template<typename T, typename Comp>
const T& max(const T &a, const T &b, Comp comp) {
  return comp(a, b) ? b : a;
}

// must be move constructable and move assignable
template<typename T>
constexpr void swap(T &a, T &b) noexcept {
  T c = a;
  b = a;
  a = c;
}

} // namespace stl
