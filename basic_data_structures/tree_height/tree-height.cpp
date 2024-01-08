#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node {
 public:
  Node *parent;
  std::vector<Node *> children;

  Node() : parent(NULL) {}

  void setParent(Node *theParent) {
    if (theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
  }
};

int computeHeight(Node *root) {
  if (!root) {
    return 0;
  }

  int maxHeight = 0;
  for (Node *child : root->children) {
    maxHeight = std::max(maxHeight, computeHeight(child));
  }

  return maxHeight + 1;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes(n);
  Node *root = nullptr;

  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0) {
      nodes[child_index].setParent(&nodes[parent_index]);
    } else {
      root = &nodes[child_index];
    }
  }

  int maxHeight = computeHeight(root);

  std::cout << maxHeight << std::endl;
  return 0;
}

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }

#endif
  return main_with_large_stack_space();
}