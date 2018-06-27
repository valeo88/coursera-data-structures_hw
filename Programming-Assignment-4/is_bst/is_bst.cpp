#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

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

/* Проверка того факта, что текущее дерево ограничено снизу min_ и сверху max_ */
bool is_bst_util(const int root_idx, const vector<Node>& tree, int min_, int max_) {
  /* пустое дерево - бинарное дерево поиска */
  if (root_idx==-1)
     return true;

  /* проверка ограничения */
  if (tree[root_idx].key < min_ || tree[root_idx].key > max_)
     return false;

  /* проверяем рекурсивно левую и правую ветвь дерева
  в левой части элементы меньше чем корень, а в правой больше. */
  return
    is_bst_util(tree[root_idx].left, tree, min_, tree[root_idx].key) &&
    is_bst_util(tree[root_idx].right, tree, tree[root_idx].key, max_);
}


bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  return is_bst_util(tree.size()>0 ? 0 : -1, tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
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
