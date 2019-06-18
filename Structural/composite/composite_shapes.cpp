#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct GraphicObject
{
  virtual void draw() = 0;
};

struct Circle: GraphicObject
{
  void draw() override
  {
    cout << "Circle" << endl;
  }
};

struct Group: GraphicObject
{
  string name;
  vector<GraphicObject*> objects;

  Group(string name): name(name) {}
  
  void draw() override
  {
    cout << "Group " << name.c_str() << " contains { " << endl;
    for (auto&& o: objects)
      o->draw();
    cout << "}" << endl;
  }
};
  
int main()
{
  Group root("root");
  Circle c1, c2;
  root.objects.push_back(&c1);

  Group subgroup("sub");
  subgroup.objects.push_back(&c2);

  root.objects.push_back(&subgroup);

  root.draw();
  return 0;
}
