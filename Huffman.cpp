//
// Created by gabri on 10/20/2025.
//
#include "Huffman.hpp"
#include <queue>
#include <utility>

struct Comparater {
    bool operator() (const TreeNode* a, const TreeNode* b) {
        if (a->freq == b->freq) {
            return a->word > b->word;
        }
        return a->freq > b->freq;
    }
};

HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string, int> > &counts) {
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, Comparater> pq;
    for (std::size_t i = 0; i < counts.size(); i++) {
        pq.push(new TreeNode{counts[i].first, counts[i].second, nullptr, nullptr});
    }
    while (pq.size() > 1) {
        TreeNode* leftChild = pq.top(); //assigning left child
        pq.pop();
        TreeNode* rightChild = pq.top(); //assigning right child
        pq.pop();

        int parent_freq = leftChild->freq + rightChild->freq; //merging frequencies for parent node
        std::string parent_word = std::min(leftChild->word, rightChild->word); //assigning min word to parent node
        //std::pair<std::string, int> new_pair = std::make_pair(parent_word, parent_freq); //creating parent node
        TreeNode* new_node = new TreeNode(parent_word, parent_freq); //adding node to tree
        pq.push(new_node);
    }
    return HuffmanTree(pq.top()); //assigning last element in priority queue as the root of tree
}
HuffmanTree::HuffmanTree(TreeNode *root) : root_(root) {}

void HuffmanTree::assignCodesDFS(const TreeNode *n, std::string &prefix, std::vector<std::pair<std::string, std::string> > &out) {
    if (n == nullptr) {
        return;
    }
    if ((n->left == nullptr) && (n->right == nullptr)) { //checking if it is a leaf before assigning code
        out.emplace_back(n->word, prefix);
        return;
    }
    prefix.push_back('0');
    assignCodesDFS(n->left, prefix, out); //assigning zero if left subtree
    prefix.pop_back();
    prefix.push_back('1');
    assignCodesDFS(n->right, prefix, out); //assigning one if right subtree
    prefix.pop_back();
}

void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string> > &out) const {
    std::string prefix; //creating string for prefixes
    assignCodesDFS(root_, prefix, out);
}

void HuffmanTree::writeHeaderPreorder(const TreeNode *n, std::ostream &os, std::string &prefix) {
    if (n == nullptr) {
        return;
    }
    if ((n->left == nullptr) && (n->right == nullptr)) {
        os << n->word << " " << prefix; //outputting word space code
        return;
    }
    prefix.push_back('0');
    writeHeaderPreorder(n->left, os, prefix); //assigning zeros if going left
    prefix.push_back('1');
    writeHeaderPreorder(n->right, os, prefix); //assigning ones if going right
    prefix.pop_back();
}

error_type HuffmanTree::writeHeader(std::ostream &os) const {
    std::string prefix; //creating prefix string
    writeHeaderPreorder(root_, os, prefix); //calling to helper function
    os << "\n"; //outputting to file
    return error_type::NO_ERROR;
}

error_type HuffmanTree::encode(const std::vector<std::string> &tokens, std::ostream &os_bits, int wrap_cols) const {
    std::vector<std::pair<std::string, std::string> > codebook; //creating codebook vector
    assignCodes(codebook);
    int charCount = 0; //variable to keep track of characters in a line

    for (std::size_t i = 0; i < tokens.size(); i++) { //loops through tokens file for words
        std::string token = tokens[i];
        std::string code;

        for (std::size_t j = 0; j < codebook.size(); j++) {
            if (codebook[j].first == token) { //checking if codebook word is the same as token
                code = codebook[j].second; //if so variable code gets assigned to current tokens code
                break;
            }
        }
        for (std::size_t k = 0; k < code.size(); k++) { //loops through code and outputs it
            os_bits << code[k];
            charCount++; //increases character count
            if (charCount == wrap_cols) { //if character count is equal to 80 then new line
                os_bits << "\n";
                charCount = 0; //reset counter
            }
        }
    }
    os_bits << "\n";
    return error_type::NO_ERROR;
}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

void HuffmanTree::destroy(TreeNode *n) noexcept {
    if (n == nullptr) {
        return;
    }
    destroy (n->left);
    destroy (n->right);
    delete (n);
}
