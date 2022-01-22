//
// Created by jpark9013 on 1/20/22.
//

#ifndef STL_PRIORITY_QUEUE_H
#define STL_PRIORITY_QUEUE_H

#include "functional.h"
#include "vector.h"

namespace stl {

template<typename T>
class priority_queue {

  private:

  typedef const T& const_reference;
  typedef T& reference;

  vector<T> tree;
  function<bool(T, T)> comp;

  // get left child
  size_t left(size_t x);

  // get right child
  size_t right(size_t x);

  // get parent node (one level up)
  size_t parent(size_t x);

  void heapify_up(size_t ind);
  void heapify_down(size_t ind);

  public:

  priority_queue();
  // if _comp(a, b) is true, then _comp(b, a) must be false and vice versa
  explicit priority_queue(function<bool(T, T)> _comp);

  ~priority_queue();

  priority_queue& operator = (const priority_queue &other);

  const_reference top() const;

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  void push(const T &x);
  void pop();

  void swap(priority_queue<T> &other) noexcept;
};

} // namespace stl

#endif //STL_PRIORITY_QUEUE_H
