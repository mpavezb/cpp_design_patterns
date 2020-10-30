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
};

struct DoubleExpression : Expression {
  double value;
  explicit DoubleExpression(const double value) : value{value} {}
};

struct AdditionExpression : Expression {
  Expression *left, *right;

  AdditionExpression(Expression *const left, Expression *const right)
      : left{left}, right{right} {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }
};

// Printer machine is external! GOOD
// But sequence of if-else + dynamic_cast cannot be avoided.
struct ExpressionPrinter {

  // THIS CANNOT BE IMPLEMENTED, AS WE DO NOT KNOW THE TYPE OF THE EXPRESSION AT
  // COMPILE TIME!
  //
  // void print(DoubleExpression *de, ostringstream &oss) const {
  //   oss << de->value;
  // }
  // void print(AdditionExpression *ae, ostringstream &oss) const {
  //   oss << "(";
  //   print(ae->left, oss);
  //   oss << "+";
  //   print(ae->right, oss);
  //   oss << ")";
  // }

  ostringstream oss;

  void print(Expression *e) {
    if (auto de = dynamic_cast<DoubleExpression *>(e)) {
      oss << de->value;
    } else if (auto ae = dynamic_cast<AdditionExpression *>(e)) {
      oss << "(";
      print(ae->left);
      oss << "+";
      print(ae->right);
      oss << ")";
    }
  }

  string str() const { return oss.str(); }
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

  ExpressionPrinter ep;
  ep.print(e);
  cout << ep.str() << endl;
}
