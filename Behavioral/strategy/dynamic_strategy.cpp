#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/**
 * This Example shows how the strategy pattern can be used to dynamically select
 * the text processor (markdown or html) for list creation.
 *
 * HTLM:
 * <ul>
 *  <li> Foo
 *  <li> Bar
 * <ul>
 *
 * Markdown:
 * * Foo
 * * Bar
 */

enum class OutputFormat { Markdown, Html };

struct ListStrategy {
  virtual ~ListStrategy() = default;

  // Common Behavior
  virtual void add_list_item(ostringstream &, const string &){};
  virtual void start(ostringstream &){};
  virtual void end(ostringstream &){};
};

struct MarkdownListStrategy : ListStrategy {
  // specific behavior
  void add_list_item(ostringstream &oss, const string &item) override {
    oss << " * " << item << endl;
  }

  // NOTE: dynamic polymorphism allows us to not implement the start() and end()
  // methods.
};

struct HtmlListStrategy : ListStrategy {
  // specific behavior
  void start(ostringstream &oss) override { oss << "<ul>" << endl; }
  void end(ostringstream &oss) override { oss << "</ul>" << endl; }
  void add_list_item(ostringstream &oss, const string &item) override {
    oss << "<li>" << item << "</li>" << endl;
  }
};

struct TextProcessor {
  void clear() {
    oss.str("");
    oss.clear();
  }

  void append_list(const vector<string> &items) {
    // User calls the general interface, independent of the actual
    // implementation.
    list_strategy->start(oss);
    for (auto &item : items)
      list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
  }

  void set_output_format(const OutputFormat format) {
    switch (format) {
    case OutputFormat::Markdown:
      list_strategy = make_unique<MarkdownListStrategy>();
      break;
    case OutputFormat::Html:
      list_strategy = make_unique<HtmlListStrategy>();
      break;
    default:
      throw runtime_error("Unsupported strategy.");
    }
  }
  string str() const { return oss.str(); }

private:
  ostringstream oss;

  // Pointer or reference to allow dynamic polymorphism
  unique_ptr<ListStrategy> list_strategy;
};

int main() {
  // markdown
  TextProcessor tp;
  tp.set_output_format(OutputFormat::Markdown);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  // html
  tp.clear();
  tp.set_output_format(OutputFormat::Html);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  return 0;
}
