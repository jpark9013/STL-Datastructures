//
// Created by jpark9013 on 1/21/22.
//

#pragma once

#ifndef STL_FORWARD_LIST_H
#define STL_FORWARD_LIST_H

#include "numeric.h"

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

    bool erase_after();
  };

  // points to first node, last node in the forward list respectively
  node *first_ptr = nullptr;
  node *end_ptr = nullptr;
  node *before_first_ptr = new node();
  size_t sz = 0;

  void destroy();

  // need to use template here in order to replicate const
  template<typename Type>
  class node_iterator {

    private:

    // we need this to access node_ptr
    friend class forward_list;

    // if nullptr, then we assume it's the pointer before the first element
    // nullptr is also the .end() return value, so the user has to be careful to not do ++ to .end()
    // (obviously, they shouldn't be doing that in the first place)
    node *node_ptr = nullptr;

    public:

    node_iterator();
    explicit node_iterator(const struct node &n);
    explicit node_iterator(struct node *n);

    Type& operator * ();

    node_iterator& operator ++ ();
    node_iterator operator ++ (int) &;

    // friend bool operator == (const node_iterator<Type> &a, const node_iterator<Type> &b);
  };

  public:

  using iterator = node_iterator<T>;
  using const_iterator = node_iterator<const T>;

  forward_list();
  explicit forward_list(size_t n);
  forward_list(size_t n, const_reference x);

  template<typename it>
  forward_list(it first, it last);

  // afaik, assign does the same thing as the constructors (it destroys the existing contents as well)
  void assign(size_t n, const_reference x);

  template<typename it>
  void assign(it first, it last);

  ~forward_list();

  reference front();
  const_reference front() const;

  // creates a temporary node object to provide the pointer before the first official node
  iterator before_begin() noexcept;
  [[maybe_unused]] const_iterator cbefore_begin() noexcept;
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_t max_size() const noexcept;
  size_t size() const noexcept;

  void clear() noexcept;
  iterator insert_after(iterator pos, const T &x);
  iterator insert_after(iterator pos, size_t n, const T &x);

  template<typename it>
  iterator insert_after(iterator pos, it first, it last);

  iterator erase_after(iterator pos); // erases the one after pos
  iterator erase_after(iterator first, iterator last);  // erases (first, last)
  void push_front(const T &x);
  void push_back(const T &x);
  void pop_front();
  void resize(size_t n);
  void resize(size_t n, const T &x);
  void swap(forward_list<T> &other) noexcept;

  // splice_after puts the second forward_list ahead of the first one and replaces *this
  void splice_after(forward_list<T> &other);
  void splice_after(forward_list<T> &&other);  // O(1) only bc move semantics

};

} // namespace stl

#endif //STL_FORWARD_LIST_H
