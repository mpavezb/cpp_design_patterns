#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> names{"john", "jane", "jill", "jack"};
  vector<string>::iterator it = names.begin(); // or begin(names)
  cout << "first name is " << *it << "\n";

  ++it; // advance the iterator
  it->append(string(" goodall"));
  cout << "second name is " << *it << "\n";

  while (++it != names.end()) {
    cout << "another name: " << *it << "\n";
  }

  // traversing the entire vector backwards
  // note global rbegin/rend, note ++ not --
  // expand auto here
  for (auto ri = rbegin(names); ri != rend(names); ++ri) {
    cout << *ri;
    if (ri + 1 != rend(names)) // iterator arithmetic
      cout << ", ";
  }
  cout << endl;

  // constant iterators
  vector<string>::const_reverse_iterator jack = crbegin(names);
  cout << "first reverse name is " << *jack << "\n";
  // won't work
  //*jack += "test";

  return 0;
}
