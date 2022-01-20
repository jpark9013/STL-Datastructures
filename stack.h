//
// Created by jpark9013 on 1/20/22.
//

#pragma once

#ifndef STL_STACK_H
#define STL_STACK_H

#include "vector.h"

namespace stl {

template<typename T>
class stack : vector<T> {

  private:

  using typename vector<T>::reference;
  using typename vector<T>::const_reference;

  public:

  using vector<T>::vector;
  using vector<T>::operator =;

  const_reference top() const;

  using vector<T>::empty;
  using vector<T>::size;

  void push(const T& x);
  void pop();

  using vector<T>::operator ==;
  using vector<T>::operator <=>;
  using vector<T>::swap;
};

} // namespace stl

#endif //STL_STACK_H
