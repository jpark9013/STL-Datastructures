//
// Created by jpark9013 on 1/20/22.
//

#include "string.h"

namespace stl {

constexpr string::string(const string &other) = default;

constexpr size_t string::length() const noexcept {
  return sz;
}

} // namespace stl
