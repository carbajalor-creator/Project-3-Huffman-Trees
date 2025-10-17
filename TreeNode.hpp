//
// Created by gabri on 10/16/2025.
//

#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <string>
#include <tuple>

class TreeNode {
public:
    TreeNode(std::tuple<std::string, int> val) : left(nullptr), right(nullptr), value_(val) {}
    ~TreeNode() {
        delete left;
        delete right;
        //leftSubtree(nullptr);
        //rightSubtree(nullptr);
    }

    TreeNode* leftSubtree() { return left; }
    TreeNode* rightSubtree() { return right; }
    const TreeNode* leftSubtree() const { return left; }
    const TreeNode* rightSubtree() const { return right; }

    void leftSubtree(TreeNode *newLeft) { left = newLeft; }
    void rightSubtree(TreeNode *newRight) { right = newRight; }

    std::tuple<std::string, int>& value() { return value_; }
    const std::tuple<std::string, int>& value() const {return value_;}

private:
    TreeNode* left;
    TreeNode* right;
    std::tuple<std::string, int> value_;
};
#endif //TREENODE_HPP
