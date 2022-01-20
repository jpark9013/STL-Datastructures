//
// Created by jpark9013 on 1/18/22.
//

#pragma once

#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include "numeric.h"

namespace stl {

template<typename T>
class vector {

  protected:

  typedef T& reference;
  typedef const T& const_reference;

  T *arr = nullptr;
  size_t cap = 0;
  size_t sz = 0;
  size_t alloc = 2;  // what to multiply the arr length by

  void build(size_t n, const_reference x);
  void swap_arr(T *other);
  void set_capacity(size_t x, bool lower);
  void reallocate();

  public:

  typedef T* iterator;
  typedef const T* const_iterator;

  constexpr vector() noexcept;
  constexpr explicit vector(size_t n);
  constexpr explicit vector(size_t n, const_reference x);

  template<typename it>
  constexpr vector(it first, it last);

  constexpr vector(const vector &other);

  constexpr ~vector();

  vector<T>& operator = (const vector<T> &other);

  // assign totally destroys the current array inside the vector and replaces it
  constexpr void assign(size_t n, const_reference x);

  template<typename it>
  constexpr void assign(it first, it last);

  constexpr void set_alloc(size_t n);
  constexpr size_t get_alloc();

  constexpr reference at(size_t ind);
  constexpr const_reference at(size_t ind) const;

  constexpr reference operator [] (size_t ind);
  constexpr const_reference operator [] (size_t ind) const;

  constexpr reference front();
  constexpr const_reference front() const;
  constexpr reference back();
  constexpr const_reference back() const;

  constexpr T* data() noexcept;
  constexpr const T* data() const noexcept;

  constexpr iterator begin() noexcept;
  constexpr const_iterator cbegin() const noexcept;
  constexpr iterator end() noexcept;
  constexpr const_iterator cend() const noexcept;
  constexpr iterator rbegin() noexcept;
  constexpr const_iterator crbegin() const noexcept;
  constexpr iterator rend() noexcept;
  constexpr const_iterator crend() const noexcept;

  [[nodiscard]] constexpr bool empty() const noexcept;

  [[nodiscard]] constexpr size_t size() const noexcept;
  [[nodiscard]] constexpr size_t max_size() const noexcept;

  constexpr void reserve(size_t new_cap);
  [[nodiscard]] constexpr size_t capacity() const noexcept;
  constexpr void shrink_to_fit();

  constexpr void clear() noexcept;
  constexpr void insert(size_t ind, const_reference x);  // insert before ind

  template<typename it>
  constexpr void insert(size_t ind, it first, it last);

  // both of these use assert since they're O(n)
  constexpr void erase(size_t ind);  // erases element at ind index
  constexpr void erase(size_t first, size_t last);  // erases from range [first, last]

  constexpr void push_back(const_reference x);
  constexpr void emplace_back(T x);
  constexpr void pop_back(size_t n = 1);
  constexpr void resize(size_t n, const_reference x = T());

  template<typename OutputStream>
  friend OutputStream& operator << (OutputStream &out, const vector<T> &x);

  // constexpr friend bool operator == (const vector<T> &a, const vector<T> &b);
  // constexpr friend auto operator <=> (const vector<T> &a, const vector<T> &b);

  constexpr void swap(vector<T> &other);

  // returns number of erased elements (both erase_value and erase_if)
  template<typename U>
  constexpr size_t erase_value(const U &x);

  // erases value if pred is true
  template<typename Pred>
  constexpr size_t erase_if(Pred pred);
};

} // namespace stl

#endif //STL_VECTOR_H
