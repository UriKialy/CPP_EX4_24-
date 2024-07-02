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

using namespace std;

// BFS iterator
template <typename T>
class BFSIterator
{
private:
    queue<Node<T> *> NodeQueue;

public:
    BFSIterator(Node<T> *root, int k)
    {
        if (root != nullptr)
        {
            NodeQueue.push(root);
        }
    }
    T &operator*() const
    {
        try
        {
            return NodeQueue.front()->value;
        }
        catch (const std::exception &e)
        {
            cout << e.what() << endl;
        }
    }

    Node<T> *operator->() const
    {
        return NodeQueue.front();
    }

    BFSIterator &operator++()
    {
        if (!NodeQueue.empty())
        {
            Node<T> *current = NodeQueue.front();
            NodeQueue.pop();
            while (current == nullptr && !NodeQueue.empty())
            {
                current = NodeQueue.front();
                NodeQueue.pop();
            }
            for (size_t i = 0; i < current->childrens.size(); ++i)
            {
                if (current->childrens[(size_t)i] != nullptr)
                {
                    NodeQueue.push(current->childrens[(size_t)i].get());
                }
            }
        }
        return *this;
    }
    bool operator==(const BFSIterator &other) const
    {
        bool bothEmpty = NodeQueue.empty() && other.NodeQueue.empty();
        bool bothNotEmpty = !NodeQueue.empty() && !other.NodeQueue.empty();
        bool frontEqual = NodeQueue.front() == other.NodeQueue.front();
        
        return bothEmpty || (bothNotEmpty && frontEqual);
    }
    BFSIterator operator++(int)
    {
        BFSIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator!=(const BFSIterator &other) const
    {
        return !(*this == other);
    }
};

// DFS iterator
template <typename T>
class dfs_iterator
{
private:
    stack<Node<T> *> nodeStack;
    Node<T> *current;
    int k;

public:
    dfs_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        if (root)
        {
            nodeStack.push(root);
        }
    }

    Node<T> *operator->() const
    {
        return current;
    }

    T &operator*()
    {
        return current->value;
    }

    dfs_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            current = nodeStack.top();
            nodeStack.pop();
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }
        }
        else
        {
            current = nullptr;
        }
        return *this;
    }

    bool operator!=(const dfs_iterator &other) const
    {
        return (current != other.current);
    }
};

// Post-order iterator
template <typename T>
class post_order_iterator
{
private:
    stack<Node<T> *> nodeStack;
    Node<T> *current;
    Node<T> *lastVisited;
    int k;

public:
    post_order_iterator(Node<T> *root, int k) : current(root), lastVisited(nullptr), k(k)
    {
        if (root)
        {
            pushLeftmostPath(root);
        }
    }

    Node<T> *operator->() const
    {
        return current;
    }

    T &operator*()
    {
        return current->value;
    }

    void pushLeftmostPath(Node<T> *node)
    {
        while (node)
        {
            nodeStack.push(node);
            if (!node->childrens.empty())
            {
                node = node->childrens[0].get();
            }
            else
            {
                break;
            }
        }
    }

    post_order_iterator<T> &operator++()
    {
        if (nodeStack.empty())
        {
            current = nullptr;
            return *this;
        }
        if (k > 2)
        { // if k>2 we will do dfs
            current = nodeStack.top();
            nodeStack.pop();
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }
            return *this;
        }
        else
        { // binary tree
            Node<T> *top = nodeStack.top();
            if (top->childrens.empty() || top->childrens.back().get() == lastVisited)
            {
                current = top;
                nodeStack.pop();
                lastVisited = current;
            }
            else
            {
                for (auto it = top->childrens.rbegin(); it != top->childrens.rend(); ++it)
                {
                    if (*it && it->get() != lastVisited)
                    {
                        pushLeftmostPath(it->get());
                        break;
                    }
                }
            }

            return *this;
        }
    }

    bool operator!=(const post_order_iterator &other) const
    {
        return (current != other.current);
    }
};

// Pre-order iterator
template <typename T>
class pre_order_iterator
{
private:
    stack<Node<T> *> nodeStack;
    Node<T> *current;
    int k;

public:
    pre_order_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        if (root)
        {
            nodeStack.push(root);
        }
    }

    Node<T> *operator->() const
    {
        return current;
    }

    T &operator*()
    {
        return current->value;
    }

    pre_order_iterator<T> &operator++()
    {
        if (nodeStack.empty())
        {
            current = nullptr;
            return *this;
        }
        if (k > 2)
        { // if k>2 we will do dfs
            current = nodeStack.top();
            nodeStack.pop();
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }
            return *this;
        }
        else // binary tree we will do pre-order
        {
            current = nodeStack.top();
            nodeStack.pop();
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }
            return *this;
        }
    }
    bool operator!=(const pre_order_iterator &other) const
    {
        return (current != other.current);
    }
};

// In-order iterator
template <typename T>
class in_order_iterator
{
private:
    stack<Node<T> *> nodeStack;
    Node<T> *current;
    int k;
    unordered_set<Node<T> *> visited;

public:
    in_order_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        pushLeftmostPath(root);
    }

    bool operator!=(const in_order_iterator &other) const
    {
        return current != other.current;
    }

    Node<T> *operator->() const
    {
        return current;
    }

    T &operator*()
    {
        return current->value;
    }

    void pushLeftmostPath(Node<T> *node)
    {
        while (node)
        {
            nodeStack.push(node);
            if (!node->childrens.empty())
            {
                node = node->childrens[0].get();
            }
            else
            {
                break;
            }
        }
    }

    in_order_iterator<T> &operator++()
    {
        if (nodeStack.empty())
        {
            current = nullptr;
            return *this;
        }
        if (k > 2)
        { // if k>2 we will do dfs
            current = nodeStack.top();
            nodeStack.pop();
            if (!current->childrens.empty())
            {
                pushLeftmostPath(current->childrens[0].get());
            }
            return *this;
        }

        if (!current->childrens.empty() && !visited.count(current))
        {
            visited.insert(current);
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }
            return *this;
        }

        current = nodeStack.top();
        nodeStack.pop();

        return *this;
    }
};

// Heap iterator
template <typename T>
class HeapIterator
{
private:
    vector<Node<T> *> heap;
    size_t index;
    int k;

public:
    HeapIterator(Node<T> *root, int k_) : index(0), k(k_)
    {
        if (k > 2)
        {
            throw invalid_argument("Heap iterator is only for binary trees");
        }
        if (root == nullptr)
        {
            return;
        }
        buildHeap(root);
    }

    void buildHeap(Node<T> *root)
    {
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *node = q.front();
            q.pop();
            heap.push_back(node);
            for (auto &child : node->childrens)
            {
                if (child)
                {
                    q.push(child.get());
                }
            }
        }
        make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                  { return a->value > b->value; });
    }

    bool operator!=(const HeapIterator &other) const
    {
        return index != other.index;
    }

    T &operator*()
    {
        return heap[0]->value;
    }

    Node<T> *operator->() const
    {
        return heap[0];
    }

    HeapIterator &operator++()
    {
        if (!heap.empty())
        {
            pop_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                     { return a->value > b->value; });
            heap.pop_back();
        }
        return *this;
    }
};