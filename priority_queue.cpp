//
// Created by jpark9013 on 1/20/22.
//

#include "algorithm.h"
#include "priority_queue.h"

namespace stl {

template<typename T>
size_t priority_queue<T>::left(size_t x) {
  return 2 * x + 1;
}

template<typename T>
size_t priority_queue<T>::right(size_t x) {
  return 2 * x + 2;
}

template<typename T>
size_t priority_queue<T>::parent(size_t x) {
  // ex:
  // x = 2 -> return 0
  // x = 5 -> return 2
  return (x - 1) / 2;
}

template<typename T>
void priority_queue<T>::heapify_up(size_t ind) {
  if (!ind) {
    return;
  }
  size_t p = parent(ind);
  if (comp(tree[ind], tree[p])) {
    swap(tree[ind], tree[p]);
    heapify_up(p);
  }
}

template<typename T>
void priority_queue<T>::heapify_down(size_t ind) {
  size_t l = left(ind);
  size_t r = right(ind);

  size_t cur = ind;

  if (l < size() && comp(tree[l], tree[cur])) {
    cur = l;
  }
  if (r < size() && comp(tree[r], tree[cur])) {
    cur = r;
  }

  if (cur == ind) {
    return;
  }

  swap(tree[ind], tree[cur]);
  heapify_down(cur);
}

template<typename T>
priority_queue<T>::priority_queue() = default;

template<typename T>
priority_queue<T>::priority_queue(function<bool(T, T)> _comp) : comp(_comp) {

}

template<typename T>
priority_queue<T>::~priority_queue() = default;

template<typename T>
priority_queue<T>& priority_queue<T>::operator = (const priority_queue<T> &other) = default;

template<typename T>
typename priority_queue<T>::const_reference priority_queue<T>::top() const {
  return tree[0];
}

template<typename T>
bool priority_queue<T>::empty() const {
  return tree.empty();
}

template<typename T>
size_t priority_queue<T>::size() const {
  return tree.size();
}

template<typename T>
void priority_queue<T>::push(const T &x) {
  tree.push_back(x);
  heapify_up(size() - 1);
}

template<typename T>
void priority_queue<T>::pop() {
  // need to remove an element in O(1) then swap 0th index with that element
  // easiest would be the back element
  tree[0] = tree.back();
  tree.pop_back();
  heapify_down(0);
}

template<typename T>
void priority_queue<T>::swap(priority_queue<T> &other) noexcept {
  tree.swap(other.tree);
  stl::swap(comp, other.comp);
}

}
