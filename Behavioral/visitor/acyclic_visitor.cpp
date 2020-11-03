#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// cyclic visitor: based on function overloading
//                 works only on a stable hierarchy
// acyclic visitor: based on RTTI
//                  no hierarchy limitations, but slower

// -----------------------------------------------------------------------------
// Visitor bases
// -----------------------------------------------------------------------------
template <typename Visitable> struct Visitor {
  virtual void visit(Visitable &obj) = 0;
};

// VisitorBase is use as a marker interface, for the hierarchy to accept.
// The accept methods are then forced to dynamic_cast to Visitor<T> type.
struct VisitorBase {
  virtual ~VisitorBase() = default;
};

// -----------------------------------------------------------------------------
// HIERARCHY
// -----------------------------------------------------------------------------
struct Expression {
  virtual ~Expression() = default;

  // The VisitorBase object is expected to have type Visitor<T>
  //                               vvv
  virtual void accept(VisitorBase &obj) {
    using EV = Visitor<Expression>; // <--- Visitor for Expression
    if (auto ev = dynamic_cast<EV *>(&obj))
      ev->visit(*this);
  }
};

struct DoubleExpression : Expression {
  double value;

  explicit DoubleExpression(double value) : value(value) {}

  virtual void accept(VisitorBase &obj) override {
    using DEV = Visitor<DoubleExpression>; // <--- Visitor for DoubleExpression
    if (auto ev = dynamic_cast<DEV *>(&obj))
      ev->visit(*this);
  }
};

struct AdditionExpression : Expression {
  Expression *left, *right;

  AdditionExpression(Expression *left, Expression *right)
      : left(left), right(right) {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }

  virtual void accept(VisitorBase &obj) override {
    using AEV =
        Visitor<AdditionExpression>; // <--- Visitor for AdditionExpression
    if (auto ev = dynamic_cast<AEV *>(&obj))
      ev->visit(*this);
  }
};

// -----------------------------------------------------------------------------
// Actual Visitor
// -----------------------------------------------------------------------------
// This approach provides additional flexibility, as the visitor is not forced
// to inherit from all types of visitables.
// Then, the hierarchy does not need to be rigid: Cases can be added
// incrementally, instead of having to create accept() methods everywhere.
struct ExpressionPrinter
    : VisitorBase,         // <--- Inherit from marker interface
      Visitor<Expression>, // <-- can be used as a fallback.
      // Visitor<DoubleExpression>, // <-- can be removed!
      Visitor<AdditionExpression> {
  void visit(Expression &) override {
    // Not a fallback!
    oss << "<this will not be displayed>";
  }

  // Can be removed!
  // void visit(DoubleExpression &obj) override { oss << obj.value; }

  void visit(AdditionExpression &obj) override {
    oss << "(";
    obj.left->accept(*this);
    oss << "+";
    obj.right->accept(*this);
    oss << ")";
  }

  string str() const { return oss.str(); }

private:
  ostringstream oss;
};

int main() {
  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ExpressionPrinter ep;
  ep.visit(*e);
  cout << ep.str() << "\n";

  return 0;
}
