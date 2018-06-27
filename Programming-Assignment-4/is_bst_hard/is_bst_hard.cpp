#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

/* Проверка того факта, что текущее дерево ограничено снизу min_ и сверху max_ */
bool is_bst_util(const int root_idx, const vector<Node>& tree, long long min_, long long max_) {
  /* пустое дерево - бинарное дерево поиска */
  if (root_idx==-1)
     return true;

  /* проверка ограничения */
  if (tree[root_idx].key < min_ || tree[root_idx].key > max_)
     return false;

  /* проверяем рекурсивно левую и правую ветвь дерева
  в левой части элементы меньше чем корень, а в правой больше или равны. */
  return
    is_bst_util(tree[root_idx].left, tree, min_, tree[root_idx].key - 1) &&
    is_bst_util(tree[root_idx].right, tree, tree[root_idx].key, max_);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  return is_bst_util(tree.size()>0 ? 0 : -1, tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main() {
    #if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif
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
