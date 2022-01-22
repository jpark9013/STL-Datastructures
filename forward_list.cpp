//
// Created by jpark9013 on 1/21/22.
//

#include "forward_list.h"

namespace stl {

template<typename T>
forward_list<T>::node::node() = default;

template<typename T>
forward_list<T>::node::node(const T &x) : value(x) {

}

template<typename T>
forward_list<T>::node::~node() {
  delete next;
}

template<typename T>
void forward_list<T>::node::attach(const T &x) {
  next = new node(x);
}

template<typename T>
void forward_list<T>::node::attach(const node &n) {
  next = &n;
}

template<typename T>
void forward_list<T>::node::erase_after() {
  if (next == nullptr) {
    return;
  }
  // do some rearranging to ensure that the node after next isn't deleted as well
  node *a = next;
  next = next->next;
  a->next = nullptr;
  delete a;
}

template<typename T>
typename forward_list<T>::reference forward_list<T>::front() {
  return last->value;
}

template<typename T>
typename forward_list<T>::const_reference forward_list<T>::front() const {
  return last->value;
}

template<typename T>
void forward_list<T>::push_front(const T &x) {
  if (last == nullptr) {
    // size of linked list is 0, aka first == nullptr
    last = new node(x);
    first = last;
  } else {
    last->next = new node(x);
    last = last->next;
  }
}

} // namespace stl
