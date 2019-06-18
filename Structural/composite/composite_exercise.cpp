#include <string>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class ContainsIntegers
{
public:
  virtual int sum() const = 0;
};

class SingleValue: public ContainsIntegers
{
  int value{0};

public:

  SingleValue() = default;
  
  explicit SingleValue(const int value): value(value)
  {
    cout << "Created SingleValue(" << value << ")" << endl;
  }

  int sum() const override {
    return value;
  }
};

class ManyValues: public vector<int>, public ContainsIntegers
{
public:
  ManyValues()
  {
    cout << "Created ManyValues" << endl;
  }
  
  void add(int value)
  {
    cout << "Adding (" << value << ") to others." << endl;
    push_back(value);
  }

  int sum() const override
  {
    return accumulate(begin(), end(), 0);
  }
};


int sum(const vector<ContainsIntegers*> items)
{
  int total {0};
  for (auto item: items)
    total += item->sum();
  return total;
};


int main()
{
  SingleValue single{1};
  ManyValues many;
  many.add(2);
  many.add(3);

  int total = sum({&single, &many});
  cout << "The sum is (" << total << ") and should be (6)" << endl;
  return 0;
}
