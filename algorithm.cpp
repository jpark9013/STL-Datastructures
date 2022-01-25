//
// Created by jpark9013 on 1/18/22.
//

#include "algorithm.h"

#include "iterator.h"
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
  T *c = &a;
  T *d = &b;
  a = *d;
  b = *c;
}

namespace {

template<typename T>
class Sort {

  private:

  T *arr;

  template<typename it, typename Compare>
  constexpr void _sort(it first, it last, Compare comp, size_t l, size_t r) {
    size_t d = r - l + 1;
    if (d <= 1) {
      return;
    }
    if (d == 2) {
      if (comp(*last, *first)) {
        swap(*first, *last);
      }
      return;
    }
    size_t mid = l + (d - 1) / 2;
    it a = next(first, mid - l);
    it b = next(a, 1);
    _sort(first, a, comp, l, mid);
    _sort(b, last, comp, mid + 1, r);
    // [first, a] is sorted
    // [b, last] is also sorted
    // so we need to merge both lists
    it ptr_1 = first, ptr_2 = b;
    bool valid_1 = true, valid_2 = true;
    // debug(vec, l, r);
    for (size_t i = l; i <= r; i++) {
      if (!valid_1) {
        arr[i] = *ptr_2;
        ptr_2++;
      } else if (!valid_2) {
        arr[i] = *ptr_1;
        ptr_1++;
      } else {
        if (comp(*ptr_2, *ptr_1)) {
          arr[i] = *ptr_2;
          if (ptr_2 == last) {
            valid_2 = false;
          }
          ptr_2++;
        } else {
          arr[i] = *ptr_1;
          if (ptr_1 == a) {
            valid_1 = false;
          }
          ptr_1++;
        }
      }
    }
    for (size_t i = l; i <= r; i++) {
      *first = arr[i];
      first++;
    }
  }

  public:

  Sort() = default;

  template<typename it, typename Compare>
  constexpr void _sort(it first, it last, Compare comp) {
    last--;
    size_t dis = distance(first, last);
    if (dis == 0) {
      return;
    }
    arr = new T[dis + 1];
    _sort(first, last, comp, 0, dis);
  }

  ~Sort() {
    delete[] arr;
  }
};

} // anonymous namespace

template<typename it>
constexpr void sort(it first, it last) {
  if (first == last) {
    return;
  }
  using T = decltype(*first);
  sort(first, last, [](const T &a, const T &b){return a < b;});
}

template<typename it, typename Compare>
constexpr void sort(it first, it last, Compare comp) {
  if (first == last) {
    return;
  }
  auto t = *first;
  Sort<decltype(t)> s;
  s._sort(first, last, comp);
}

} // namespace stl
