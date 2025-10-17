

#ifndef BST_HPP
#define BST_HPP
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include "TreeNode.hpp"

class TreeNode;

class BinSearchTree {
public:
    BinSearchTree() = default;
    ~BinSearchTree(); // calls destroy(root_)

    // Insert 'word'; if present, increment its count.
    void insert(const std::string& word);

    // Convenience: loop over insert(word) for each token.
    void bulkInsert(const std::vector<std::string>& words);

    // Queries
    [[nodiscard]] bool contains(std::string_view word) const noexcept;
    [[nodiscard]] std::optional<int> countOf(std::string_view word) const noexcept;

    // In-order traversal (word-lex order) -> flat list for next stage
    void inorderCollect(std::vector<std::pair<std::string,int>>& out) const;

    // Metrics
    [[nodiscard]] std::size_t size() const noexcept;  // distinct words
    [[nodiscard]] unsigned height() const noexcept;   // empty tree = 0

    //my functions
    std::pair<std::vector<std::tuple<std::string, int>>, int> creatingVector(const std::string &filename);
    std::vector<std::tuple<std::string, int>> insertPriorityQueue(std::vector<std::tuple<std::string, int >>tokenTuples);
    std::pair<int, int> getMinMaxFreq () const;

private:
    // TreeNode is defined elsewhere in the project
    TreeNode* root_ = nullptr;

    // Helpers
    static void destroy(TreeNode* node) noexcept;
    static TreeNode* insertHelper(TreeNode* node, const std::string& word);
    static const TreeNode* findNode(const TreeNode* node, std::string_view word) noexcept;
    static void inorderHelper(const TreeNode* node,
                              std::vector<std::pair<std::string,int>>& out);
    static std::size_t sizeHelper(const TreeNode* node) noexcept;
    static unsigned heightHelper(const TreeNode* node) noexcept;
    std::vector<std::tuple<std::string, int>> priorityQueue_;
};
#endif //BST_HPP
