#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
using namespace std;

class Tree {
private:
    TreeNode* root;

public:
    Tree();

    TreeNode* createNode(const string& winnerName);

    void insert(TreeNode* parent, TreeNode* child);

    void setRoot(TreeNode* node);

    TreeNode* getRoot();

    void displayTree(TreeNode* node, int level = 0);
};

#endif  // TREE_H
