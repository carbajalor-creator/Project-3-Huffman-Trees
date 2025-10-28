//
// Created by gabri on 10/23/2025.
//

#include "PriorityQueue.hpp"
#include <iostream>
#include <fstream>
#include <iosfwd>


PriorityQueue::PriorityQueue(std::vector<TreeNode *> nodes) {
    for (TreeNode* node : nodes) {
        items_.push_back(node);
    }
}

std::size_t PriorityQueue::size() const noexcept {
    return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

TreeNode* PriorityQueue::findMin() const noexcept {
    return items_.back(); //min will be last element in list
}

TreeNode *PriorityQueue::extractMin() noexcept {
    if (items_.empty()) { //if empty no min
      return nullptr;
    }
    TreeNode* min = items_.back(); //min will be last element in list
    items_.pop_back(); //delete min
    return min;
}

void PriorityQueue::deleteMin() noexcept {
    items_.pop_back();
}

void PriorityQueue::insert(TreeNode *node) {
    new TreeNode(*node);
    items_.push_back(node);
}

void PriorityQueue::print(std::ostream &os) const {
    os << "PriorityQueue{";
    for (TreeNode* node : items_) { //looping through items_
      os << node->word << " " << node->freq << "\n"; //printing word space frequency
    }
    os << "}\n";
}

bool PriorityQueue::higherPriority(const TreeNode *a, const TreeNode *b) noexcept {
    if (a->freq > b->freq) { //if a frequency is greater than b frequency true
        return true;
    }
    else if (a->freq == b->freq) { //if frequencies are the same check words
        return a->word > b->word; //if word a is greater than word b then true
    }
    return false;
}

bool PriorityQueue::isSorted() const {
    for (std::size_t i = 0; i < items_.size(); i++) {
        if (items_.at(i) < items_.at(i + 1)) {
            return false;
        }
    }
    return true;
}





