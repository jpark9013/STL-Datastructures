//
// Created by jpark9013 on 1/20/22.
//

#pragma once

#ifndef STL_ARRAY_H
#define STL_ARRAY_H

#include "numeric.h"
#include "vector.h"

namespace stl {

// in retrospect, it may have been a better decision to inherit vector from array rather than vice versa
template<typename T, size_t N>
class array : vector<T> {

  private:

  using typename vector<T>::reference;
  using typename vector<T>::const_reference;

  public:

  using typename vector<T>::iterator;
  using typename vector<T>::const_iterator;

  constexpr array() noexcept;

  using vector<T>::at;
  using vector<T>::operator [];
  using vector<T>::front;
  using vector<T>::back;
  using vector<T>::data;

  using vector<T>::begin;
  using vector<T>::cbegin;
  using vector<T>::end;
  using vector<T>::cend;
  using vector<T>::rbegin;
  using vector<T>::crbegin;
  using vector<T>::rend;
  using vector<T>::crend;

  using vector<T>::empty;
  using vector<T>::size;
  using vector<T>::max_size;

  constexpr void fill(const_reference x);
  using vector<T>::swap;

  using vector<T>::operator ==;
  using vector<T>::operator <=>;
};

}

#endif //STL_ARRAY_H
