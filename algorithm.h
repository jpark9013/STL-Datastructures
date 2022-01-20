//
// Created by jpark9013 on 1/18/22.
//

#pragma once

#ifndef STL_ALGORITHM_H
#define STL_ALGORITHM_H

#include "numeric.h"

namespace stl {

template<typename it>
int64_t distance(it first, it last);

template<typename it1, typename it2>
bool lexiographical_compare(it1 first1, it1 last1, it2 first2, it2 last2);

// requires < operator on class T to be defined
template<typename T>
const T& min(const T &a, const T &b);

// comp must return true if a < b
template<typename T, typename Comp>
const T& min(const T &a, const T &b, Comp comp);

template<typename T>
const T& max(const T &a, const T &b);

// comp must return true if a < b (< isn't a typo)
template<typename T, typename Comp>
const T& max(const T &a, const T &b, Comp comp);

template<typename T>
constexpr void swap(T &a, T &b) noexcept;

} // namespace stl

#endif //STL_ALGORITHM_H
