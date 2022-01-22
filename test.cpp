//
// Created by jpark9013 on 1/18/22.
//

#include "vector.h"

#include <iostream>

void test() {
  stl::vector<int> vec(5);
  for (int i = 0; i < 5; i++) {
    vec[i] = i;
  }
  for (int i : vec) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main() {
  test();
  return 0;
}