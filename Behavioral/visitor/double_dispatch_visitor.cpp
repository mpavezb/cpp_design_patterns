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

// =============================================================================
// Double dispatch handlers
// - Extra code, but reasonable.
// - Can easily handle multiple concerns.

struct SubtractionExpression;
struct DoubleExpression;
struct AdditionExpression;

// general visitor.
struct ExpressionVisitor {
  virtual void visit(DoubleExpression *de) = 0;
  virtual void visit(AdditionExpression *ae) = 0;
  virtual void visit(SubtractionExpression *se) = 0;
};

// First concern: Print
struct ExpressionPrinter : ExpressionVisitor {
  ostringstream oss;
  string str() const { return oss.str(); }
  void visit(DoubleExpression *de) override;
  void visit(AdditionExpression *ae) override;
  void visit(SubtractionExpression *se) override;
};

// Second concern: Evaluate
struct ExpressionEvaluator : ExpressionVisitor {
  double result;
  void visit(DoubleExpression *de) override;
  void visit(AdditionExpression *ae) override;
  void visit(SubtractionExpression *se) override;
};

// =============================================================================
// Hierarchy: Expression, number + addition + subtraction
struct Expression {
  virtual ~Expression() = default;

  // every component must accept visitors.
  // all implementations are the same!
  virtual void accept(ExpressionVisitor *visitor) = 0;
};

struct DoubleExpression : Expression {
  double value;
  explicit DoubleExpression(const double value) : value{value} {}

  // This implementation is the same on every component, and cannot be
  // extracted!.
  //
  // The important part is the type of the `this` pointer.
  // It forces using the specific visit() overload.
  void accept(ExpressionVisitor *visitor) override { visitor->visit(this); }
};

struct AdditionExpression : Expression {
  Expression *left, *right;

  AdditionExpression(Expression *const left, Expression *const right)
      : left{left}, right{right} {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }

  void accept(ExpressionVisitor *visitor) override { visitor->visit(this); }
};

struct SubtractionExpression : Expression {
  Expression *left, *right;

  SubtractionExpression(Expression *const left, Expression *const right)
      : left{left}, right{right} {}

  ~SubtractionExpression() {
    delete left;
    delete right;
  }

  void accept(ExpressionVisitor *visitor) override { visitor->visit(this); }
};

// =============================================================================
// The visitors must implement special handling for each component.
void ExpressionPrinter::visit(DoubleExpression *de) { oss << de->value; }

void ExpressionPrinter::visit(AdditionExpression *e) {
  // We only want to print braces if the right side is a SubtractionExpression.
  bool need_braces = dynamic_cast<SubtractionExpression *>(e->right);
  e->left->accept(this);
  oss << "-";
  if (need_braces)
    oss << "(";
  e->right->accept(this);
  if (need_braces)
    oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression *se) {
  // We only want to print braces if the right side is a SubtractionExpression.
  bool need_braces = dynamic_cast<SubtractionExpression *>(se->right);
  if (need_braces)
    oss << "(";
  se->left->accept(this);
  oss << "-";
  se->right->accept(this);
  if (need_braces)
    oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression *de) { result = de->value; }

void ExpressionEvaluator::visit(AdditionExpression *ae) {
  ae->left->accept(this);
  auto temp = result;
  ae->right->accept(this);
  result += temp;
}

void ExpressionEvaluator::visit(SubtractionExpression *se) {
  se->left->accept(this);
  auto temp = result;
  se->right->accept(this);
  result -= temp;
}

int main() {
  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new SubtractionExpression{new DoubleExpression{2},
                                new DoubleExpression{3}}};

  ExpressionPrinter printer;
  ExpressionEvaluator evaluator;
  printer.visit(e);
  evaluator.visit(e);
  cout << printer.str() << " = " << evaluator.result << endl;

  return 0;
}
