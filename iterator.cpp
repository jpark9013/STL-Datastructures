//
// Created by jpark9013 on 1/24/22.
//

#include "iterator.h"

namespace stl {

template<typename it>
it next(it iterator, size_t x) {
  for (size_t i = 0; i < x; i++) {
    iterator++;
  }
  return iterator;
}

} // namespace stl
