//
// Created by jpark9013 on 1/20/22.
//

#include "array.h"

#include "numeric.h"

#include <cstring>

namespace stl {

template<typename T, size_t N>
constexpr array<T, N>::array() noexcept : vector<T>(N) {

}

template<typename T, size_t N>
constexpr void array<T, N>::fill(const_reference x) {
  memset(this->arr, x, sizeof(T) * N);
}

}
