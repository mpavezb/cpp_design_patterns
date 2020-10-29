#include <coroutine>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template <typename T> struct BinaryTree;

// todo: refactor to refer to parent instead of entire tree
template <typename T> struct Node {
  T value = T();
  Node<T> *left = nullptr;
  Node<T> *right = nullptr;
  Node<T> *parent = nullptr;
  BinaryTree<T> *tree = nullptr; // Pointer to the whole tree

  explicit Node(const T &value) : value(value) {}

  Node(const T &value, Node<T> *const left, Node<T> *const right)
      : value(value), left(left), right(right) {
    this->left->tree = this->right->tree = tree;
    this->left->parent = this->right->parent = this;
  }

  void set_tree(BinaryTree<T> *t) {
    tree = t;
    if (left)
      left->set_tree(t);
    if (right)
      right->set_tree(t);
  }

  ~Node() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

template <typename T> struct BinaryTree {
  Node<T> *root = nullptr; // only knows about the root

  explicit BinaryTree(Node<T> *const root) : root{root} {
    root->set_tree(this);
  }

  ~BinaryTree() {
    if (root)
      delete root;
  }

  // todo: postorder iterator using recursive coroutines
  generator<Node<T> *> post_order() { return post_order_impl(root); }

private:
  // or use a recursive_generator
  // generator<Node<T> *> post_order_impl(Node<T> *node) {
  //   if (node) {
  //     for (auto x : post_order_impl(node->left))
  //       co_yield x;
  //     for (auto y : post_order_impl(node->right))
  //       co_yield y;
  //     co_yield node;
  //   }
  // }
};

int main() {
  // in order traversal
  //         me
  //       |     |
  //   mother   father
  //    |  |
  //  m'm  m'f

  BinaryTree<string> family{new Node<string>{
      "me",
      new Node<string>{"mother", new Node<string>{"mother's mother"},
                       new Node<string>{"mother's father"}},
      new Node<string>{"father"}}};

  cout << "=== postorder travesal with coroutines:\n";

  // use coroutines (yields pointers!)
  // postorder: m'm, m'f m f me
  // for (auto it : family.post_order()) {
  //   cout << it->value << endl;
  // }

  return 0;
}
