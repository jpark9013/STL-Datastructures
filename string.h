//
// Created by jpark9013 on 1/20/22.
//

#pragma once

#ifndef STL_STRING_H
#define STL_STRING_H

#include "vector.h"

namespace stl {

class string : vector<char> {

  public:

  [[maybe_unused]] static const size_t npos = -1;

  // more constructors
  using vector<char>::vector;
  using vector<char>::operator =;
  using vector<char>::assign;
  constexpr string(const string &other);

  // possibly implement this later
  // [[nodiscard]] constexpr const char* c_str() const noexcept;

  using vector<char>::begin;
  using vector<char>::cbegin;
  using vector<char>::end;
  using vector<char>::cend;
  using vector<char>::rbegin;
  using vector<char>::crbegin;
  using vector<char>::rend;
  using vector<char>::crend;

  using vector<char>::empty;
  using vector<char>::size;
  [[nodiscard]] constexpr size_t length() const noexcept;
  using vector<char>::max_size;
  using vector<char>::reserve;
  using vector<char>::capacity;
  using vector<char>::shrink_to_fit;

  using vector<char>::clear;
  using vector<char>::insert;
  using vector<char>::erase;
  using vector<char>::push_back;
  using vector<char>::pop_back;

  // TODO: (also don't forget to use memcmp or strcmp)
  // append, += later
  // compare
  // starts_with
  // ends_with
  // contains
  // replace
  // substr
  // copy
  // find
  // rfind
  // find_first_of
  // find_first_not_of
  // find_last_of
  // find_last_not_of
  // operator +

  // operator == (cpp)
  // operator <=> (cpp)

  using vector<char>::swap;
  using vector<char>::erase_value;
  using vector<char>::erase_if;

  // TODO:
  // operator <<
  // operator >>

  // stoi, stol, stoll
  // stoul, stoull
  // stof, stod, stold
  // to_string
};

} // namespace stl

#endif //STL_STRING_H
