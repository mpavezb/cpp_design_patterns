#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Tag
{
  string name, text;
  vector<Tag> children;
  vector<pair<string,string>> attributes;

  
  friend ostream& operator<<(ostream& os, const Tag& tag)
  {
    os << "<" << tag.name;

    // write attributes
    for (const auto& att: tag.attributes)
      os << " " << att.first << "=\"" << att.second << "\"";

    // end or recursively put the children
    if (tag.children.size() == 0 && tag.text.length() == 0)
      os << "/>" << endl;
    else
    {
      os << ">" << endl;

      if (tag.text.length())
        os << tag.text << endl;

      for (const auto& child: tag.children)
        os << child;

      os << "</" << tag.name << ">" << endl;
    }
    return os;
  }

protected:
  Tag(const string &name, const string &text): name(name), text(text) {}

  Tag(const string &name, const vector<Tag> &children): name(name), children(children) {}  
};

// Paragraph
struct P: Tag
{
  P(const string &text): Tag("p", text) {}
  P(initializer_list<Tag> children): Tag("p", children) {}
};

// Image Tag
struct Image: Tag
{
  explicit Image(const string& url): Tag{"img", ""}
  {
    attributes.emplace_back(make_pair("src", url));
  }
};

int main()
{
  cout <<

    P {
      Image { "http://google.com" }
    }
  
    << endl;
  return 0;
}
