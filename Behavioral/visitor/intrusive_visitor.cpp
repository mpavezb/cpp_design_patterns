// visitor examples for design patterns c++ book
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/**
 * Hierarchy of mathematical operations.
 *
 * We would like to add printing behavior.
 */
struct Expression {
  virtual ~Expression() = default;

  // intrusive implementation!.
  virtual void print(ostringstream &oss) = 0;
};

struct DoubleExpression : Expression {
  double value;
  explicit DoubleExpression(const double value) : value{value} {}

  // intrusive implementation.!
  void print(ostringstream &oss) override { oss << value; }
};

struct AdditionExpression : Expression {
  Expression *left, *right;

  AdditionExpression(Expression *const left, Expression *const right)
      : left{left}, right{right} {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }

  // intrusive implementation!.
  void print(ostringstream &oss) override {
    oss << "(";
    left->print(oss);
    oss << "+";
    right->print(oss);
    oss << ")";
  }
};

int main() {
  //  1 + 2 + 3
  //    __+__
  //   1    _+_
  //       2   3
  //

  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
  ostringstream oss;
  e->print(oss);
  cout << oss.str() << endl;

  return 0;
}
