#include <functional>
#include <iostream>

using namespace std;

///////////////////////////////////////////////////
// simple function decorator
struct Logger {
  function<void()> func;
  string name;

  Logger(const function<void()> &func, const string &name)
      : func(func), name(name) {}

  void operator()() const {
    cout << "Entering " << name << endl;
    func();
    cout << "Exiting " << name << endl;
  }
};

///////////////////////////////////////////////////////
// templated function decorator
template <typename Func> struct TemplateLogger {
  Func func;
  string name;

  TemplateLogger(const Func &func, const string &name)
      : func(func), name(name) {}

  void operator()() const {
    cout << "Entering " << name << endl;
    func();
    cout << "Exiting " << name << endl;
  }
};

// we need this helper function, so we can deduce the type of the argument
template <typename Func>
auto make_template_logger(Func func, const string &name) {
  return TemplateLogger<Func>{func, name};
}

////////////////////////////////////////////////////////////
// templated function decorator with args

double add(double a, double b) {
  cout << a << "+" << b << " = " << (a + b) << endl;
  return a + b;
}

template <typename> struct Logger3;

template <typename R, typename... Args> struct Logger3<R(Args...)> {
  function<R(Args...)> func;
  string name;

  Logger3(const function<R(Args...)> &func, const string &name)
      : func(func), name(name) {}

  R operator()(Args... args) {
    cout << "Entering " << name << endl;
    R result = func(args...);
    cout << "Exiting " << name << endl;
    return result;
  }
};

// helper function
template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string &name) {
  return Logger3<R(Args...)>(function<R(Args...)>(func), name);
}

int main() {
  Logger([]() { cout << "Hello" << endl; }, "HelloFunction")();

  auto logger =
      make_template_logger([]() { cout << "Hello" << endl; }, "HelloFunction");
  logger();

  auto logged_add = make_logger3(add, "Add");
  auto result = logged_add(2, 3);
  cout << "result = " << result << endl;
}
