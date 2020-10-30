#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T> struct Observer;

template <typename T> struct Observable {
  // vector is not a thread safe class
  std::vector<Observer<T> *> observers;

public:
  void notify(T &source, const std::string &field_name) {
    // reading the vector.
    for (auto observer : observers)
      observer->field_changed(source, field_name);
  }

  void subscribe(Observer<T> &observer) {
    // adding to the vector.
    observers.push_back(&observer);
  }

  void unsubscribe(Observer<T> &observer) {
    // removing from the vector.
    observers.erase(remove(observers.begin(), observers.end(), &observer),
                    observers.end());
  }
};
