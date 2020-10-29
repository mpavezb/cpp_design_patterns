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

  explicit BinaryTree(Node<T> *const root) : root{root}, pre_order{*this} {
    root->set_tree(this);
  }

  ~BinaryTree() {
    if (root)
      delete root;
  }

  // V1: Implement an iterator with operations ++() and *().
  // This iterator is to be used always. User cannot choose traversal strategy.
  template <typename U> struct PreOrderIterator {
    Node<U> *current;

    explicit PreOrderIterator(Node<U> *current) : current(current) {}

    bool operator!=(const PreOrderIterator<U> &other) {
      return current != other.current;
    }

    // V1: no recursion! --> complex implementation.
    PreOrderIterator<U> &operator++() {
      if (current->right) {
        current = current->right;
        while (current->left)
          current = current->left;
      } else {
        Node<T> *p = current->parent;
        while (p && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    Node<U> &operator*() { return *current; }
  }; // struct PreOrderIterator

  typedef PreOrderIterator<T> iterator;

  // V1: begin() and end() based on default iterator.
  iterator end() { return iterator{nullptr}; }

  iterator begin() {
    Node<T> *n = root;

    if (n)
      while (n->left)
        n = n->left;
    return iterator{n};
  }

  // V2: Expose multiple iterator objects to use as traversal.
  class PreOrderTraversal {
    BinaryTree<T> &tree;

  public:
    explicit PreOrderTraversal(BinaryTree<T> &tree) : tree{tree} {}
    iterator begin() { return tree.begin(); }
    iterator end() { return tree.end(); }
  } pre_order;
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

  // V1: User CANNOT choose traversal strategy.
  // pre order traversal
  for (auto it = family.begin(); it != family.end(); ++it) {
    cout << (*it).value << "\n";
  }
  // this is the same
  for (const auto &it : family) {
    cout << it.value << "\n";
  }

  cout << "=== and now, through a dedicated object:\n";

  // V2: User can choose traversal strategy
  for (const auto &it : family.pre_order) {
    cout << it.value << "\n";
  }

  return 0;
}
