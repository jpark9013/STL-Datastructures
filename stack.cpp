//
// Created by jpark9013 on 1/20/22.
//

#include "stack.h"

namespace stl {

template<typename T>
typename stack<T>::const_reference stack<T>::top() const {
  return this->back();
}

template<typename T>
void stack<T>::push(const T &x) {
  this->push_back(x);
}

template<typename T>
void stack<T>::pop() {
  this->pop_back(1);
}

} // namespace stl
