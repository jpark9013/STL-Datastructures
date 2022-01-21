//
// Created by jpark9013 on 1/20/22.
//

#ifndef STL_FUNCTIONAL_H
#define STL_FUNCTIONAL_H

namespace stl {

// credit to Evgeny Panasyuk for the code here (https://stackoverflow.com/a/14741161)
// (Some cleanup and .cpp/.h transformation  done)
// I only need std::function for some constructors, like priority queue

namespace {

template<typename Result, typename ...Args>
struct abstract_function {
  virtual Result operator () (Args... args) = 0;
  virtual abstract_function *clone() const = 0;
  virtual ~abstract_function() = default;
};

template<typename Func, typename Result, typename ...Args>
class concrete_function : public abstract_function<Result, Args...> {

  private:

  Func f;

  public:

  explicit concrete_function(const Func &x) : f(x) {}
  Result operator () (Args... args) override {
    return f(args...);
  }
  concrete_function *clone() const override {
    return new concrete_function{f};
  }
};

template<typename Func>
struct func_filter {
  typedef Func type;
};

template<typename Result, typename ...Args>
struct func_filter<Result(Args...)> {
  typedef Result (*type)(Args...);
};

template<typename signature>
class function;

}  // anonymous namespace

template<typename Result, typename ...Args>
class function<Result(Args...)> {

  private:

  abstract_function<Result, Args...> *f;

  public:

  function();

  template<typename Func>
  explicit function(const Func &x);

  function(const function &rhs);

  template<typename Func>
  function& operator = (const Func &x);
  Result operator () (Args... args);

  ~function();
};

}

#endif //STL_FUNCTIONAL_H
