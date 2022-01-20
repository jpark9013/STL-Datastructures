//
// Created by jpark9013 on 1/18/22.
//

#include "vector.h"

#include "algorithm.h"
#include "numeric.h"

#include <cassert>
#include <cstring>

namespace stl {

template<typename T>
void vector<T>::build(size_t n, const T &x) {
  cap = n;
  arr = new T[sz];
  memset(arr, x, sizeof(T) * sz);
}

// important: doesn't set capacity, size etc. only changes the array pointing to
template<typename T>
void vector<T>::swap_arr(T *other) {
  delete[] arr;
  arr = other;
}

template<typename T>
void vector<T>::set_capacity(size_t x, bool lower) {
  if (!lower && x <= cap) {
    return;
  } else {
    // can't set capacity lower than sz
    if (x < sz) {
      return;
    }
    cap = min(x, cap);
  }
  T *temp = new T[x];
  memcpy(temp, arr, cap);
  swap_arr(temp);
  cap = x;
}

template<typename T>
void vector<T>::reallocate() {
  set_capacity(cap * alloc, false);
}

template<typename T>
constexpr vector<T>::vector() noexcept = default;

template<typename T>
constexpr vector<T>::vector(size_t n) : sz(n) {
  build(n, T());
}

template<typename T>
constexpr vector<T>::vector(size_t n, const T &x) : sz(n) {
  build(n, x);
}

template<typename T>
template<typename it>
constexpr vector<T>::vector(it first, it last) : sz(distance(first, last)), cap(sz) {
  arr = new T[sz];
  size_t ind = 0;
  while (first != last) {
    arr[ind] = *first;
    ind++;
    first++;
  }
}

template<typename T>
constexpr vector<T>::vector(const vector<T> &other) {
  (*this) = other;
}

template<typename T>
constexpr vector<T>::~vector<T>() = default;

template<typename T>
vector<T>& vector<T>::operator = (const vector<T> &other) = default;

template<typename T>
constexpr void vector<T>::assign(size_t n, const_reference x) {
  delete[] arr;
  sz = n;
  build(n, x);
}

template<typename T>
template<typename it>
constexpr void vector<T>::assign(it first, it last) {
  size_t n = distance(first, last);
  delete[] arr;
  arr = new T[n];
  sz = n;
  cap = n;
  T *ptr = arr;
  while (first != last) {
    *ptr = *first;
    ptr++;
    first++;
  }
}

template<typename T>
constexpr typename vector<T>::reference vector<T>::at(size_t ind) {
  assert(ind < sz);
  return arr[ind];
}

template<typename T>
constexpr void vector<T>::set_alloc(size_t n) {
  alloc = n;  // check later ig?
  assert(alloc != 0);
}

template<typename T>
constexpr size_t vector<T>::get_alloc() {
  return alloc;
}

template<typename T>
constexpr typename vector<T>::const_reference vector<T>::at(size_t ind) const {
  assert(ind < sz);
  return arr[ind];
}

template<typename T>
constexpr typename vector<T>::reference vector<T>::operator [] (size_t ind) {
  return arr[ind];
}

template<typename T>
constexpr typename vector<T>::const_reference vector<T>::operator [] (size_t ind) const {
  return arr[ind];
}

template<typename T>
constexpr typename vector<T>::reference vector<T>::front() {
  return arr[0];
}

template<typename T>
constexpr typename vector<T>::const_reference vector<T>::front() const {
  return arr[0];
}

template<typename T>
constexpr typename vector<T>::reference vector<T>::back() {
  return arr[sz - 1];
}

template<typename T>
constexpr typename vector<T>::const_reference vector<T>::back() const {
  return arr[sz - 1];
}

template<typename T>
constexpr T* vector<T>::data() noexcept {
  return arr;
}

template<typename T>
constexpr const T* vector<T>::data() const noexcept {
  return arr;
}

template<typename T>
constexpr typename vector<T>::iterator vector<T>::begin() noexcept {
  return arr;
}

template<typename T>
constexpr typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return arr;
}

template<typename T>
constexpr typename vector<T>::iterator vector<T>::end() noexcept {
  return arr + sz;
}

template<typename T>
constexpr typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return arr + sz;
}

template<typename T>
constexpr typename vector<T>::iterator vector<T>::rbegin() noexcept {
  return arr + sz - 1;
}

template<typename T>
constexpr typename vector<T>::const_iterator vector<T>::crbegin() const noexcept {
  return arr + sz - 1;
}

template<typename T>
constexpr typename vector<T>::iterator vector<T>::rend() noexcept {
  return arr - 1;
}

template<typename T>
constexpr typename vector<T>::const_iterator vector<T>::crend() const noexcept {
  return arr - 1;
}

template<typename T>
constexpr bool vector<T>::empty() const noexcept {
  return sz == 0;
}

template<typename T>
constexpr size_t vector<T>::size() const noexcept {
  return sz;
}

template<typename T>
constexpr size_t vector<T>::max_size() const noexcept {
  return size_t(-1);
}

// Strictly O(n) per call
template<typename T>
constexpr void vector<T>::reserve(size_t new_cap) {
  set_capacity(new_cap, false);
}

template<typename T>
constexpr size_t vector<T>::capacity() const noexcept {
  return cap;
}

// tries to reduce capacity() to size() if possible
// strictly O(n)
template<typename T>
constexpr void vector<T>::shrink_to_fit() {
  set_capacity(sz, true);
}

// leaves capacity unchanged
template<typename T>
constexpr void vector<T>::clear() noexcept {
  sz = 0;
}

template<typename T>
constexpr void vector<T>::insert(size_t ind, const_reference x) {
  assert(ind < sz);
  T *temp = new T[cap + 1];
  // left memcpy
  memcpy(temp, arr, ind);
  // insert x
  temp[ind] = x;
  // right memcpy
  memcpy(temp + ind + 1, arr + ind, cap - ind);
  swap_arr(temp);
  cap++;
  sz++;
}

template<typename T>
template<typename it>
constexpr void vector<T>::insert(size_t ind, it first, it last) {
  assert(ind < sz);
  size_t d = distance(first, last);
  T *temp = new T[cap + d];
  // left memcpy
  memcpy(temp, arr, ind);
  // insert the things
  T *ptr = temp + ind;
  while (first != last) {
    *ptr = *first;
    first++;
    ptr++;
  }
  // right memcpy
  memcpy(temp + ind + d, arr + ind, cap - ind);
  swap_arr(temp);
  cap += d;
  sz += d;
}

template<typename T>
constexpr void vector<T>::erase(size_t ind) {
  assert(ind < sz);
  // left memcpy
  T *temp = new T[cap - 1];
  memcpy(temp, arr, ind);
  // right memcpy
  memcpy(temp + ind, arr + ind + 1, cap - ind - 1);
  swap_arr(temp);
  cap--;
  sz--;
}

template<typename T>
constexpr void vector<T>::erase(size_t first, size_t last) {
  assert(first < sz && last < sz && first <= last);
  size_t new_cap = cap - last + first - 1;
  T *temp = new T[new_cap];
  // left memcpy
  memcpy(temp, arr, first);
  // right memcpy
  memcpy(temp, arr + last + 1, new_cap - first);
  swap_arr(temp);
  cap = new_cap;
  sz -= last - first + 1;
}

template<typename T>
constexpr void vector<T>::push_back(const_reference x) {
  if (cap == 0) {
    cap = 1;
    sz = 1;
    arr = new T[cap];
  } else if (sz == cap) {
    reallocate();
    sz++;
  } else {
    sz++;
  }
  arr[sz - 1] = x;
}

template<typename T>
constexpr void vector<T>::emplace_back(T x) {
  push_back(x);
}

template<typename T>
constexpr void vector<T>::pop_back(size_t n) {
  // Include this assert here, even though this function overall is O(1) :)
  assert(sz >= n);
  sz -= n;
}

template<typename T>
constexpr void vector<T>::resize(size_t n, const_reference x) {
  if (n > sz) {
    while (cap < n) {
      reallocate();
    }
    memset(arr + sz, x, sizeof(T) * (n - sz));
  }
  sz = n;
}

template<typename OutputStream, typename T>
OutputStream& operator << (OutputStream &out, const vector<T> &x) {
  out << '[';
  bool flag = false;
  for (typename vector<T>::const_iterator it = x.cbegin(); it != x.cend(); it++) {
    out << x;
    if (flag) {
      out << ", ";
    }
    flag = true;
  }
  out << ']';
  return out;
}

template<typename T>
constexpr bool operator == (const vector<T> &a, const vector<T> &b) {
  size_t n = a.size();
  if (n != b.size()) {
    return false;
  }
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

template<typename T>
constexpr auto operator <=> (const vector<T> &a, const vector<T> &b) {
  size_t n = a.size();
  size_t m = b.size();
  if (n > m) {
    return 1;
  } else if (n < m) {
    return -1;
  }

  for (size_t i = 0; i < n; i++) {
    if (a[i] > b[i]) {
      return 1;
    } else if (a[i] < b[i]) {
      return -1;
    }
  }

  return 0;
}

template<typename T>
constexpr void vector<T>::swap(const vector<T> &other) {
  stl::swap(arr, other.arr);
  stl::swap(sz, other.sz);
  stl::swap(cap, other.cap);
}

template<typename T>
template<typename U>
constexpr size_t vector<T>::erase_value(const U &x) {
  vector<T> temp;
  for (auto it = begin(); it != end(); it++) {
    if (*it != x) {
      temp.push_back(*it);
    }
  }

  this->swap(temp);
  return size() - temp.size();
}

template<typename T>
template<typename Pred>
constexpr size_t vector<T>::erase_if(Pred pred) {
  vector<T> temp;
  for (auto it = begin(); it != end(); it++) {
    if (!pred(*it)) {
      temp.push_back(*it);
    }
  }

  this->swap(temp);
  return size() - temp.size();
}

} // namespace stl