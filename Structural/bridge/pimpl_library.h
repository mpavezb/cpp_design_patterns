#include <memory>

template <typename T> class pimpl {
private:
  std::unique_ptr<T> impl;

public:
  pimpl();
  ~pimpl();

  // forwarding constructor
  template <typename... Args> pimpl(Args &&... args);

  T *operator->();
  T &operator*();
};
