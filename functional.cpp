//
// Created by jpark9013 on 1/20/22.
//

#include "functional.h"

namespace stl {

// credit to Evgeny Panasyuk for the code here (https://stackoverflow.com/a/14741161)
// (Some cleanup and .cpp/.h transformation  done)
// I only need std::function for some constructors, like priority queue

template<typename Result, typename ...Args>
function<Result(Args...)>::function() : f(nullptr) {

}

template<typename Result, typename ...Args>
template<typename Func>
function<Result(Args...)>::function(const Func &x) :
f(new concrete_function<typename func_filter<Func>::type, Result, Args...>(x)) {

}

template<typename Result, typename ...Args>
function<Result(Args...)>::function(const function &rhs) : f(rhs.f ? rhs.f->clone() : nullptr) {

}

template<typename Result, typename ...Args>
template<typename Func>
function<Result(Args...)>& function<Result(Args...)>::operator = (const Func &x) {
  auto *temp = new concrete_function<typename func_filter<Func>::type, Result, Args...>(x);
  delete f;
  f = temp;
  return *this;
}

template<typename Result, typename ...Args>
Result function<Result(Args...)>::operator () (Args... args) {
  if (f) {
    return (*f)(args...);
  } else {
    return Result{};
  }
}

template<typename Result, typename ...Args>
function<Result(Args...)>::~function() {
  delete f;
};

} // namespace stl