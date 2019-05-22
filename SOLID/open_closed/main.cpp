#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
  string name;
  Color color;
  Size size;
};

/* 
BAD SOLUTION
1. We would need to modify the class to create other filters.
2. This kind of filter will grow super quickly when combining filtering axes!.
*/
struct ProductFilter
{
  vector<Product*> by_color(vector<Product*> items, Color color)
  {
    vector<Product*> result;
    for (auto& i: items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }

  vector<Product*> by_size_and_color(vector<Product*> items, Size size, Color color)
  {
    vector<Product*> result;
    for (auto& i: items)
      if (i->size == size && i->color == color)
        result.push_back(i);
    return result;
  }
};

/* GOOD SOLUTION 
- Each new filter can be implemented on its own and small class.
- We would never have to modify existing code.
*/

/* Specification Interface */
template <typename T> struct AndSpecification;
template <typename T> struct Specification
{
  virtual ~Specification() = default;  
  virtual bool is_satisfied(T* item) const = 0;
};

/* Filter Interface */
template <typename T> struct Filter
{
  virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

/* ProductFilter based on the Specification logic */
struct BetterFilter: Filter<Product>
{
  vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) override
  {
    vector<Product*> result;
    for (auto& item: items)
      if (spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};

template <typename T> AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
  return { first, second };
}

struct ColorSpecification: Specification<Product>
{
  Color color;

  ColorSpecification(Color color) : color(color) {}

  bool is_satisfied(Product *item) const override
  {
    return item->color == color;
  }
};

struct SizeSpecification: Specification<Product>
{
  Size size;

  SizeSpecification(Size size) : size(size) {}

  bool is_satisfied(Product *item) const override
  {
    return item->size == size;
  }
};

/* AND Specification */
template <typename T> struct AndSpecification: Specification<T>
{
  const Specification<T>& first;
  const Specification<T>& second;

  AndSpecification(const Specification<T> &first, const Specification<T> &second): first(first), second(second)
  {}

  bool is_satisfied(T *item) const override
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

int main()
{
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const vector<Product*> items { &apple, &tree, &house };

  cout << endl << "ProductFilter:" << endl;
  ProductFilter pf;
  auto green_things = pf.by_color(items, Color::green);
  for (auto& item: green_things)
    cout << item->name << " is green\n";

  cout << endl << "Betterfilter:" << endl;
  BetterFilter bf;
  ColorSpecification green(Color::green);
  for (auto& item: bf.filter(items, green))
    cout << item->name << " is green'\n";

  cout << endl << "And Specification:" << endl;
  SizeSpecification large(Size::large);
  AndSpecification<Product> green_and_large(green, large);
  for (auto& item: bf.filter(items, green_and_large))
    cout << item->name << " is green and large\n";

  cout << endl << "Simple AndSpecification:" << endl;
  auto spec = green && large;
  for (auto& item: bf.filter(items, spec))
    cout << item->name << " is green and large\n";
  
  return 0;
}
