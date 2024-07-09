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
    std::stack<std::pair<Node<T>*, bool>> nodeStack;

public:
    in_order_iterator(Node<T>* root, int k) {
        if (root) {
            pushLeftPath(root);
        }
    }

    void pushLeftPath(Node<T>* node) {
        while (node) {
            nodeStack.push({node, false});
            if (!node->childrens.empty()) {
                node = node->childrens[0].get();
            } else {
                break;
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
        if (nodeStack.empty()) {
            return *this;
        }

        auto [node, visited] = nodeStack.top();
        nodeStack.pop();

        if (visited) {
            return *this;
        }

        if (node->childrens.size() > 1) {
            pushLeftPath(node->childrens[1].get());
        }

        return *this;
    }

    bool operator!=(const in_order_iterator& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }
};

template <typename T>
class post_order_iterator {
private:
    std::stack<std::pair<Node<T>*, bool>> nodeStack;

public:
    post_order_iterator(Node<T>* root, int k) {
        if (root) {
            nodeStack.push({root, false});
        }
    }

    T& operator*() {
        if (nodeStack.empty()) {
            throw std::out_of_range("Post-order iterator is at end");
        }
        return nodeStack.top().first->value;
    }

    post_order_iterator<T>& operator++() {
        while (!nodeStack.empty()) {
            auto [node, visited] = nodeStack.top();
            nodeStack.pop();

            if (visited) {
                return *this;
            } else {
                nodeStack.push({node, true});
                for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it) {
                    if (*it) {
                        nodeStack.push({it->get(), false});
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
    std::vector<Node<T>*> heap;
    size_t index;

public:
    HeapIterator(Node<T>* root, int k) : index(0) {
        if (k > 2) {
            throw std::invalid_argument("Heap iterator is only for binary trees");
        }
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
            heap.push_back(node);
            for (auto& child : node->childrens) {
                if (child) {
                    q.push(child.get());
                }
            }
        }
        std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->value > b->value; });
    }

    bool operator!=(const HeapIterator& other) const {
        return index != other.index || index < heap.size();
    }

    T& operator*() {
        if (index >= heap.size()) {
            throw std::out_of_range("Heap iterator is at end");
        }
        return heap[0]->value;
    }

    HeapIterator& operator++() {
        if (!heap.empty()) {
            std::pop_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->value > b->value; });
            heap.pop_back();
            index++;
        }
        return *this;
    }
};