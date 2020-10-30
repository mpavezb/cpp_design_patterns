#include <algorithm>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

template <typename T> struct Observer;

template <typename T> struct SaferObservable {
  std::vector<Observer<T> *> observers;
  typedef std::mutex mutex_t;
  mutex_t mtx;

public:
  void notify(T &source, const std::string &field_name) {
    std::scoped_lock<mutex_t> lock{mtx};
    for (auto observer : observers)
      observer->field_changed(source, field_name);
  }

  void subscribe(Observer<T> &observer) {
    std::scoped_lock<mutex_t> lock{mtx};
    observers.push_back(&observer);
  }

  void unsubscribe(Observer<T> &observer) {
    // possible deadlock if this is called while in notify!
    std::scoped_lock<mutex_t> lock{mtx};
    observers.erase(remove(observers.begin(), observers.end(), &observer),
                    observers.end());
  }
};
