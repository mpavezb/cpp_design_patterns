#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class HtmlElement
{
  friend class HtmlBuilder;
  
  std::string name, text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  /* Hide Constructors, so we force the use of a builder. */
  HtmlElement() {}
  
  HtmlElement(const std::string &name, const std::string &text)
    : name(name), text(text) {}

public:
  std::string str(int indent = 0) const
  {
    ostringstream oss;
    string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
      oss << string(indent_size*(indent + 1), ' ') << text << endl;
    
    for (const auto& e: elements)
      oss << e.str(indent + 1);
    
    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }
};

class HtmlBuilder
{
  HtmlElement root;

public:
  HtmlBuilder(std::string root_name)
  {
    root.name = root_name;
  }

  /* Return reference to enable chaining.
     Here we decided to use a Reference API, but 
     this can also be done with a Pointer API.   */
  HtmlBuilder& add_child(std::string child_name, std::string child_text)
  {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return *this;
  }
  
  std::string str() const {
    return root.str();
  }

  // Allows conversion to HtmlElement
  operator HtmlElement() const {
    return root;
  }

  // We can also provide a clearer API for the same purpose.
  HtmlElement build() {
    // This is the last expected operation, so we can move the root.
    return std::move(root);
  }

  /* Ideally this method should be called from a HtmlElement */
  static HtmlBuilder create(std::string root_name)
  {
    return {root_name};
  }
};

int main()
{
  // Force the usage of builders.
  // HtmlElement cannot be built using their constructor!.
  // HtmlElement e; // INVALID
  
  cout << "Fluent Builder." << endl;
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello").add_child("li", "world");
  cout << builder.str() << endl;

  cout << "Fluent Builder - Create Syntax." << endl;
  // This version uses the HtmlElement operator() for
  // conversion from a Builder.
  // Problem: It is not clear for the user this can be done!
  HtmlElement elem = HtmlBuilder::create("ul")
    .add_child("li", "hello")
    .add_child("li", "world");
  cout << elem.str() << endl;

  // Create and Build syntax.
  cout << "Fluent Builder - Create and Build syntax." << endl;
  auto elem2 = HtmlBuilder::create("ul")
    .add_child("li", "using create")
    .add_child("li", "and build syntax")
    .build(); // Explicit creation.
  cout << elem2.str() << endl;
  
  return 0;
}
