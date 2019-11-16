#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void naive_html_builder() {
  auto text = "hello";
  string output;
  output += "<p>";
  output += text;
  output += "</p>";
  cout << output << endl;

  string words[] = {"hello", "world"};
  ostringstream oss;
  oss << "<ul>" << endl;
  for (auto w : words)
    oss << "  <li>" << w << "</li>" << endl;
  oss << "</ul>" << endl;
  cout << oss.str() << endl;
}

struct HtmlElement {
  string name, text;
  vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}

  HtmlElement(const string &name, const string &text)
      : name(name), text(text) {}

  /* Common way to handle identation logic. */
  string str(int indent = 0) const {
    ostringstream oss;
    string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
      oss << string(indent_size * (indent + 1), ' ') << text << endl;

    for (const auto &e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }
};

struct HtmlBuilder {
  HtmlElement root;

  HtmlBuilder(string root_name) { root.name = root_name; }

  void add_child(string child_name, string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
  }

  string str() const { return root.str(); }
};

int main() {
  cout << "Naive Builder:" << endl;
  naive_html_builder();

  cout << "Builder Pattern: " << endl;
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "world");
  cout << builder.str() << endl;

  return 0;
}
