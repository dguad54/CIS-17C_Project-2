#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <vector>
using namespace std;
struct TreeNode {
    string winner;
    vector<TreeNode*> children;
};

#endif  // TREENODE_H
