#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Field
{
  string name;
  string type;

  // Hide constructors
  friend class CodeBuilder;
  Field(const string &name, const string &type): name{name}, type{type} {} 

public:
  friend ostream& operator<<(ostream& os, const Field& obj)
  {
    return os << obj.type << " " << obj.name << ";";
  }
};

class Class
{
  string name;
  vector<Field> fields;

  // Hide constructors
  friend class CodeBuilder;
  Class() {}
  Class(string name): name(name) {}

public:
  void add(Field field)
  {
    fields.push_back(field);
  }
  
  friend ostream& operator<<(ostream& os, const Class& obj)
  {
    os << "class " << obj.name << endl
       << "{" << endl;

    for (auto&& field: obj.fields)
      os << "  " << field << endl;

    os << "};";
    return os;
  }
};


class CodeBuilder
{
  Class code;
public:
  CodeBuilder(const string& class_name)
  {
    code.name = class_name;
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    code.add(Field(name, type));
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    return os << obj.code;
  }
};


int main()
{
  auto cb = CodeBuilder{"Person"}
                .add_field("name", "string")
                .add_field("age", "int");
  cout << cb;
  
  return 0;
}
