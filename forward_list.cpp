//
// Created by jpark9013 on 1/21/22.
//

#include "forward_list.h"

#include "algorithm.h"

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
template<typename Type>
forward_list<T>::node_iterator<Type>::node_iterator() = default;

template<typename T>
template<typename Type>
forward_list<T>::node_iterator<Type>::node_iterator(const struct node &n) : node_ptr(&n) {

}

template<typename T>
template<typename Type>
forward_list<T>::node_iterator<Type>::node_iterator(struct node *n) : node_ptr(n) {

}

template<typename T>
template<typename Type>
Type& forward_list<T>::node_iterator<Type>::operator * () {
  return node_ptr->value;
}

template<typename T>
template<typename Type>
typename forward_list<T>::template node_iterator<Type>& forward_list<T>::node_iterator<Type>::operator ++ () {
  node_ptr = node_ptr->next;
  return *this;
}

template<typename T>
template<typename Type>
typename forward_list<T>::template node_iterator<Type> forward_list<T>::node_iterator<Type>::operator ++ (int) & {
  node_iterator<Type> ret = *this;
  node_ptr = node_ptr->next;
  return ret;
}

template<typename T, typename Type>
bool operator == (
    const typename forward_list<T>::template node_iterator<Type> &a,
    const typename forward_list<T>::template node_iterator<Type> &b
) {
 return a.node_ptr == b.node_ptr;
}

template<typename T>
bool forward_list<T>::node::erase_after() {
  if (next == nullptr) {
    return false;
  }
  // do some rearranging to ensure that the node_ptr after next isn't deleted as well
  node *a = next;
  next = next->next;
  a->next = nullptr;
  delete a;
  return true;
}

// destroys every node except before_first_ptr
// and sets sz to 0
template<typename T>
void forward_list<T>::destroy() {
  delete first_ptr;
  first_ptr = nullptr;
  end_ptr = nullptr;
}

template<typename T>
forward_list<T>::forward_list() = default;

template<typename T>
forward_list<T>::forward_list(size_t n) {
  assign(n, T());
}

template<typename T>
forward_list<T>::forward_list(size_t n, const_reference x) {
  assign(n, x);
}

template<typename T>
template<typename it>
forward_list<T>::forward_list(it first, it last) {
  assign(first, last);
}

template<typename T>
forward_list<T>::~forward_list() {
  destroy();
  delete before_first_ptr;
}

template<typename T>
void forward_list<T>::assign(size_t n, const_reference x) {
  destroy();
  for (size_t i = 0; i < n; i++) {
    push_front(x);
  }
  sz = n;
}

template<typename T>
template<typename it>
void forward_list<T>::assign(it first, it last) {
  destroy();
  while (first != last) {
    push_front(*first);
    first++;
    sz++;
  }
}

template<typename T>
typename forward_list<T>::reference forward_list<T>::front() {
  return first_ptr->value;
}

template<typename T>
typename forward_list<T>::const_reference forward_list<T>::front() const {
  return first_ptr->value;
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::before_begin() noexcept {
  before_first_ptr->next = first_ptr;
  return iterator(before_first_ptr);
}

template<typename T>
[[maybe_unused]] typename forward_list<T>::const_iterator forward_list<T>::cbefore_begin() noexcept {
  before_first_ptr->next = first_ptr;
  return const_iterator(before_first_ptr);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::begin() noexcept {
  return iterator(first_ptr);
}

template<typename T>
typename forward_list<T>::const_iterator forward_list<T>::cbegin() const noexcept {
  return const_iterator(first_ptr);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::end() noexcept {
  return iterator(nullptr);
}

template<typename T>
typename forward_list<T>::const_iterator forward_list<T>::cend() const noexcept {
  return const_iterator(nullptr);
}

template<typename T>
bool forward_list<T>::empty() const noexcept {
  return sz == 0;
}

template<typename T>
size_t forward_list<T>::max_size() const noexcept {
  return size_t(-1);
}

template<typename T>
size_t forward_list<T>::size() const noexcept {
  return sz;
}

template<typename T>
void forward_list<T>::clear() noexcept {
  destroy();
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::insert_after(iterator pos, const T &x) {
  return insert_after(pos, 1, x);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::insert_after(iterator pos, size_t n, const T &x) {
  node *ptr = pos.node_ptr;
  node *next = ptr->next;
  for (size_t i = 0; i < n; i++) {
    ptr->next = new node(x);
    ptr = ptr->next;
    sz++;
  }
  ptr->next = next;
  first_ptr = before_first_ptr->next;
  return iterator(ptr);
}

template<typename T>
template<typename it>
typename forward_list<T>::iterator forward_list<T>::insert_after(iterator pos, it first, it last) {
  node *ptr = pos.node_ptr;
  node *next = ptr->next;
  while (first != last) {
    ptr->next = new node(*first);
    ptr = ptr->next;
    first++;
    sz++;
  }
  ptr->next = next;
  first_ptr = before_first_ptr->next;
  return iterator(pos);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::erase_after(iterator pos) {
  sz -= pos.node_ptr->erase_after();
  return iterator(pos.node_ptr->next);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::erase_after(iterator first, iterator last) {
  node *ptr = first.node_ptr;
  while (ptr->next != last.node_ptr) {
    sz -= ptr->erase_after();
  }
  return last;
}

template<typename T>
void forward_list<T>::push_front(const T &x) {
  if (sz == 0) {
    // same as push_back
    push_back(x);
  } else {
    // first_ptr should not be nullptr
    node *next = first_ptr;
    first_ptr = new node(x);
    first_ptr->next = next;
    sz++;
  }
}

template<typename T>
void forward_list<T>::push_back(const T &x) {
  if (sz == 0) {
    // set before_first_ptr
    first_ptr = new node(x);
    end_ptr = first_ptr;
  } else {
    // just set end_ptr differently
    end_ptr->next = new node(x);
    end_ptr = end_ptr->next;
  }
  sz++;
}

template<typename T>
void forward_list<T>::pop_front() {
  sz -= before_first_ptr->erase_after();
}

template<typename T>
void forward_list<T>::resize(size_t n) {
  resize(n, T());
}

template<typename T>
void forward_list<T>::resize(size_t n, const T &x) {
  if (n >= sz) {
    for (size_t i = sz; i < n; i++) {
      push_back(x);
    }
    return;
  } else {
    // not really sure how to implement this in less than linear time
    forward_list<T> temp;
    for (size_t i = 0; i < n; i++) {
      temp.push_back(x);
    }
    this->swap(temp);
  }
}

template<typename T>
void forward_list<T>::swap(forward_list<T> &other) noexcept {
  stl::swap(before_first_ptr, other.before_first_ptr);
  stl::swap(first_ptr, other.first_ptr);
  stl::swap(end_ptr, other.end_ptr);
  stl::swap(sz, other.sz);
}

} // namespace stl
