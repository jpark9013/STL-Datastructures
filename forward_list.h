//
// Created by jpark9013 on 1/21/22.
//

#pragma once

#ifndef STL_FORWARD_LIST_H
#define STL_FORWARD_LIST_H

namespace stl {

// honestly, this class is so useless
// just use list, vector, or deque instead
template<typename T>
class forward_list {

  private:

  typedef T& reference;
  typedef const T& const_reference;

  struct node {
    T value;
    node *next = nullptr;

    node();
    explicit node(const T &x);

    ~node();

    // unsafe, not checking if next is already allocated
    void attach(const T &x);
    void attach(const node &n);

    void erase_after();
  };

  // points to first, last node in the forward list respectively
  // (front is in last just because of C++'s weird naming conventions)
  node *first = nullptr;
  node *last = nullptr;

  public:

  typedef node* iterator;
  typedef const node* const_iterator;

  // constructor
  // destructor

  reference front();
  const_reference front() const;

  void push_front(const T &x);
};

} // namespace stl

#endif //STL_FORWARD_LIST_H
