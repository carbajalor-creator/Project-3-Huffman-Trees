//Gabriela Carbajal Ortiz
#include "bst.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <iosfwd>
#include <optional>
#include <string>
#include <algorithm>
#include "Scanner.hpp"

std::pair<std::vector<std::tuple<std::string, int>>, int> BinSearchTree::creatingVector(const std::string& filename) {
//creating a vector to create tuples of tokens and their frequency count
    std::vector<std::tuple<std::string, int>> tokenTuples;
    std::ifstream inputFile(filename); //reads in tokens file
    std::string token;
    int totalTokens = 0; //variable to count total tokens

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        return {tokenTuples, totalTokens};
    }

    while (std::getline(inputFile, token)) {
        totalTokens++; //token counter increases when there is a token
        bool found = false;
        for (size_t i = 0; i < tokenTuples.size(); i++) {
            if (token == std::get<0>(tokenTuples[i])) { //checks if token is already in tuple vector
                std::get<1>(tokenTuples[i]) += 1; //increases frequency count of token
                found = true;
                break;
            }
        }
        if (!found) { //if not already in tuple vector then it gets added with frequency of 1
            tokenTuples.push_back(std::make_tuple(token, 1));
        }
    }
    return {tokenTuples, totalTokens}; //returns tuples vector and number of total tokens
}


std::vector<std::tuple<std::string, int> > BinSearchTree::insertPriorityQueue(std::vector<std::tuple<std::string, int>> tokenTuples) {
//creates priority queue
    priorityQueue_.clear();
    if (tokenTuples.size() == 0) { //checking if tuples vector is empty if so returns empty priority queue
        return priorityQueue_;
    }
    priorityQueue_.push_back(tokenTuples[0]); //adds first tuple from tokens tuple to priority vector
    for (size_t i = 0; i < tokenTuples.size(); i++) { //iterates through tokenTuples vector
        const auto& token = tokenTuples[i];
        bool inserted = false; //marker to check if tuple gets inserted later
        for (size_t j = 0; j < priorityQueue_.size(); j++) { // iterates through priority queue to check where to insert tuple
            int freqToken = std::get<1>(token);
            int freqQueue = std::get<1>(priorityQueue_[j]);
            if (freqToken > freqQueue || freqToken == freqQueue) { //finding spot to insert tuple in correct order
                priorityQueue_.insert(priorityQueue_.begin() + j, token); //inserted
                inserted = true; //marks as inserted
                break;
            }
        }
        if (!inserted) { //if not inserted before inserted now
            priorityQueue_.push_back(token);
        }

    }
    return priorityQueue_;
}

TreeNode *BinSearchTree::insertHelper(TreeNode *node, const std::string &word) {

    if( node == nullptr ) //if empty then creates a new node for a tuple
        return new TreeNode( std::make_tuple(word, 1) );
    if( std::get<0>(node->value()) < word ) //if word is bigger goes to right subtree
        node->rightSubtree( insertHelper( node->rightSubtree(), word ) );
    else if ( std::get<0>(node->value()) == word ) { //if word is the same frequency count goes up
        std::get<1>(node->value()) += 1;
    }
    else
        node->leftSubtree( insertHelper( node->leftSubtree(), word ) ); //if word is smaller it goes to left subtree
    return node;
}



void BinSearchTree::insert(const std::string& word) {
//inserts word if it is not in tree already
    if( ! findNode(root_, word) ) {
        root_ = insertHelper(root_, word);
    }
}

void BinSearchTree::bulkInsert(const std::vector<std::string> &words) {
    for (size_t i = 0; i < words.size(); i++) { //iterates through words vector and calls on insert to insert them
        insert(words[i]);
    }
}

const TreeNode * BinSearchTree::findNode(const TreeNode *node, std::string_view word) noexcept {
    if (node == nullptr) {
        return nullptr;
    }
    if ( std::get<0>(node->value()) == word ) { //if node is word returns node
        return node;
    }
    if (std::get<0>(node->value()) < word ) { //if word is greater than node it searches right
        return findNode( node->rightSubtree(), word );
    }
    return findNode( node->leftSubtree(), word ); //otherwise searches left
}

bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(root_, word); //calls on findNode to search
}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    const TreeNode* node = findNode(root_, word);
    return std::get<1>(node->value()); //finds node and returns its frequency count
}

void BinSearchTree::inorderHelper(const TreeNode *node, std::vector<std::pair<std::string, int> > &out) {
    if (node == nullptr) {
        return;
    }
    inorderHelper( node->leftSubtree(), out ); //checks left subtree to print out in alphabetical order
    auto[word, count] = node->value();
    std::cout << word << ": " << count << std::endl;
    inorderHelper( node->rightSubtree(), out ); //then checks right subtree
}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int>>& out) const {
    return inorderHelper(root_, out); //calls on inOrderHelper and gives it a node to start at
}

std::size_t BinSearchTree::sizeHelper(const TreeNode *node) noexcept {
    if (node == nullptr) {
        return 0; //if null size is 0
    }
    //increases count when encountering nodes
    return 1 + sizeHelper(node->leftSubtree()) + sizeHelper(node->rightSubtree());
}

std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(root_);
}

unsigned BinSearchTree::heightHelper(const TreeNode *node) noexcept {
    if (node == nullptr) {
        return 0;
    }
    //uses max to pick the higher number
    return 1 + std::max(heightHelper(node->leftSubtree()), heightHelper(node->rightSubtree()));
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}

void BinSearchTree::destroy(TreeNode *node) noexcept {
    if (node == nullptr) {
        return;
    }
    destroy( node->leftSubtree() ); //deletes left subtree
    destroy( node->rightSubtree() ); //deletes right subtree
    destroy( node );
}

BinSearchTree::~BinSearchTree() {
    destroy(root_);
}

std::pair<int, int> BinSearchTree::getMinMaxFreq() const {
    //uses priority queue to get the max and min frequencies
    int maxFreq = std::get<1>(priorityQueue_.front()); //max freq is at the beginning of the vector
    int minFreq = std::get<1>(priorityQueue_.back()); //min freq is at the end of the vector

    return {minFreq, maxFreq};
}


