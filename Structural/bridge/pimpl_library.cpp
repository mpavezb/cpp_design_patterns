#include "pimpl_library.h"
#include <utility>

// -----------------------------------------------------------------------------
// PIMPL LIBRARY
// -----------------------------------------------------------------------------

template <typename T> pimpl<T>::pimpl() : impl{new T{}} {}

template <typename T> pimpl<T>::~pimpl() {
  // destruction is handled by unique_ptr
}

template <typename T>
template <typename... Args>
pimpl<T>::pimpl(Args &&... args) : impl{new T{std::forward<Args>(args)...}} {}

template <typename T> T *pimpl<T>::operator->() { return impl.get(); }

template <typename T> T &pimpl<T>::operator*() { return *impl.get(); }

// -----------------------------------------------------------------------------
// USAGE
// -----------------------------------------------------------------------------

// in .h
class Foo {
  class Impl;
  pimpl<Impl> impl; // This provides all details we need, We just need to
                    // implement the FooImpl class.
};

// keep Foo::Impl in .cpp.
class Foo::Impl {};
