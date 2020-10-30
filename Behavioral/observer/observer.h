#include <string>

template <typename T> struct Observer {
  // Observers must implement the field_changed() callback
  virtual void field_changed(T &source, const std::string &field_name) = 0;
};
