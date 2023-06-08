#include "Tree.h"
#include <iostream>
using namespace std;
Tree::Tree() {
    root = nullptr;
}

TreeNode* Tree::createNode(const string& winnerName) {
    TreeNode* newNode = new TreeNode;
    newNode->winner = winnerName;
    return newNode;
}

void Tree::insert(TreeNode* parent, TreeNode* child) {
    parent->children.push_back(child);
}

void Tree::setRoot(TreeNode* node) {
    root = node;
}

TreeNode* Tree::getRoot() {
    return root;
}

void Tree::displayTree(TreeNode* node, int level) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        cout << "  ";
    }

    cout << "|_" << node->winner << endl;

    for (TreeNode* child : node->children) {
        displayTree(child, level + 1);
    }
}
