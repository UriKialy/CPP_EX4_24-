#pragma once
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include "Node.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

template <typename T>
class BFSIterator {
private:
    std::queue<Node<T>*> nodeQueue;

public:
    BFSIterator(Node<T>* root, int k) {
        if (root != nullptr) {
            nodeQueue.push(root);
        }
    }

    T& operator*() const {
        if (nodeQueue.empty()) {
            throw std::out_of_range("BFS iterator is at end");
        }
        return nodeQueue.front()->value;
    }
    Node<T>* get_node() const {
        return nodeQueue.front();
    }

    BFSIterator& operator++() {
        if (!nodeQueue.empty()) {
            Node<T>* current = nodeQueue.front();
            nodeQueue.pop();
            for (auto& child : current->childrens) {
                if (child != nullptr) {
                    nodeQueue.push(child.get());
                }
            }
        }
        return *this;
    }

    bool operator!=(const BFSIterator& other) const {
        return !nodeQueue.empty() || !other.nodeQueue.empty();
    }
};

template <typename T>
class dfs_iterator {
private:
    std::stack<Node<T>*> nodeStack;

public:
    dfs_iterator(Node<T>* root) {
        if (root) {
            nodeStack.push(root);
        }
    }

    T& operator*() {
        if (nodeStack.empty()) {
            throw std::out_of_range("DFS iterator is at end");
        }
        return nodeStack.top()->value;
    }

    dfs_iterator<T>& operator++() {
        if (!nodeStack.empty()) {
            Node<T>* curr = nodeStack.top();
            nodeStack.pop();

            for (auto it = curr->childrens.rbegin(); it != curr->childrens.rend(); ++it) {
                if (*it) {
                    nodeStack.push(it->get());
                }
            }
        }
        return *this;
    }

    bool operator!=(const dfs_iterator& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }
};

template <typename T>
class pre_order_iterator {
private:
    std::stack<Node<T>*> nodeStack;

public:
    pre_order_iterator(Node<T>* root, int k) {
        if (root) {
            nodeStack.push(root);
        }
    }

    T& operator*() {
        if (nodeStack.empty()) {
            throw std::out_of_range("Pre-order iterator is at end");
        }
        return nodeStack.top()->value;
    }

    pre_order_iterator& operator++() {
        if (!nodeStack.empty()) {
            Node<T>* current = nodeStack.top();
            nodeStack.pop();

            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it) {
                if (*it) {
                    nodeStack.push(it->get());
                }
            }
        }
        return *this;
    }

    bool operator!=(const pre_order_iterator& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }
};
template <typename T>
class in_order_iterator {
private:
    std::stack<std::pair<Node<T>*, size_t>> nodeStack;
    int k;

public:
    in_order_iterator(Node<T>* root, int k) : k(k) {
        if (root) {
            nodeStack.push({root, 0});
            if (k <= 2) {
                moveToFirstInOrder();
            }
        }
    }

    T& operator*() {
        if (nodeStack.empty()) {
            throw std::out_of_range("In-order iterator is at end");
        }
        return nodeStack.top().first->value;
    }

    in_order_iterator<T>& operator++() {
        if (!nodeStack.empty()) {
            if (k <= 2) {
                moveNextInOrder();
            } else {
                moveNextDFS();
            }
        }
        return *this;
    }

    bool operator!=(const in_order_iterator& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }

private:
    void moveToFirstInOrder() {
        while (!nodeStack.empty()) {
            auto [node, index] = nodeStack.top();
            if (index == 0 && !node->childrens.empty()) {
                nodeStack.push({node->childrens[0].get(), 0});
            } else {
                break;
            }
        }
    }

    void moveNextInOrder() {
        auto [node, index] = nodeStack.top();
        nodeStack.pop();

        if (index + 1 < node->childrens.size()) {
            nodeStack.push({node->childrens[index + 1].get(), 0});
            moveToFirstInOrder();
        }
    }

    void moveNextDFS() {
        auto [node, index] = nodeStack.top();
        nodeStack.pop();

        for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it) {
            if (*it) {
                nodeStack.push({it->get(), 0});
            }
        }
    }
};
template <typename T>
class post_order_iterator {
private:
    std::stack<Node<T>*> nodeStack;
    int k;

public:
    post_order_iterator(Node<T>* root, int k) : k(k) {
        if (root) {
            nodeStack.push(root);
        }
    }

    T& operator*() {
        if (nodeStack.empty()) {
            throw std::out_of_range("Post-order iterator is at end");
        }
        return nodeStack.top()->value;
    }

    post_order_iterator<T>& operator++() {
        if (!nodeStack.empty()) {
            Node<T>* current = nodeStack.top();
            nodeStack.pop();

            if (k > 2) {
                // For k > 2, use DFS-like traversal
                for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it) {
                    if (*it) {
                        nodeStack.push(it->get());
                    }
                }
            } else {
                // For k <= 2, use traditional post-order traversal
                if (!current->childrens.empty()) {
                    nodeStack.push(current->childrens[0].get());
                    if (current->childrens.size() > 1) {
                        nodeStack.push(current->childrens[1].get());
                    }
                }
            }
        }
        return *this;
    }

    bool operator!=(const post_order_iterator& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }
};

template <typename T>
class HeapIterator {
private:
    std::vector<T> heap;
    size_t currentIndex;

public:
    HeapIterator(Node<T>* root, int k) : currentIndex(0) {
        if (root != nullptr) {
            buildHeap(root);
        }
    }

    void buildHeap(Node<T>* root) {
        std::queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* node = q.front();
            q.pop();
            heap.push_back(node->value);
            for (auto& child : node->childrens) {
                if (child) {
                    q.push(child.get());
                }
            }
        }
        std::sort(heap.begin(), heap.end());
    }

    bool operator!=(const HeapIterator& other) const {
        return currentIndex < heap.size();
    }

    T& operator*() {
        if (currentIndex >= heap.size()) {
            throw std::out_of_range("Heap iterator is at end");
        }
        return heap[currentIndex];
    }

    HeapIterator& operator++() {
        if (currentIndex < heap.size()) {
            currentIndex++;
        }
        return *this;
    }
};