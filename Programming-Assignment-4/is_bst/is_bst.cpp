#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};


bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  for (int i = 0; i < tree.size(); ++i) {
    Node current = tree[i];
    if (current.left!=-1 && tree[current.left].key > current.key) {
        return false;
    } else if (current.right!=-1 && tree[current.right].key < current.key) {
        return false;
    } else if (current.left!=-1 && tree[current.left].right!=-1 && tree[tree[current.left].right].key > current.key) {
        return false;
    }  else if (current.right!=-1 && tree[current.right].left!=-1 && tree[tree[current.right].left].key < current.key) {
        return false;
    }
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
