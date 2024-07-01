#pragma once
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include "Node.hpp"
#include <iostream>
using namespace std;

// bfs_iterator
template <typename T>
class BFSIterator
{
private:
    queue<Node<T> *> nodeQueue;
    Node<T> *current;
    int k;

public:
    BFSIterator(Node<T> *root, int k) : current(root), k(k)
    {
        if (root)
        {
            nodeQueue.push(root);
        }
    }
    Node<T> *get_current()
    {
        return current;
    }

    T &operator*()
    {
        try
        {
            return current->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    BFSIterator<T> &operator++()
    {
        if (!nodeQueue.empty())
        {
            Node<T> *node = nodeQueue.front();
            nodeQueue.pop();

            for (auto &child : node->childrens)
            {
                if (child)
                {
                    nodeQueue.push(child.get());
                }
            }

            if (!nodeQueue.empty())
            {
                current = nodeQueue.front();
            }
            else
            {
                current = nullptr;
            }
        }
        return *this;
    }
    bool operator!=(const BFSIterator &other) const
    {
        return current != other.current;
    }
};

// dfs_iterator
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
    Node<T> *get_current()
    {
        return current;
    }

    T &operator*()
    {
        try
        {
            return current->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    dfs_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            Node<T> *node = nodeStack.top();
            nodeStack.pop();

            for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeStack.push(it->get());
                }
            }

            if (!nodeStack.empty())
            {
                current = nodeStack.top();
            }
            else
            {
                current = nullptr;
            }
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
    deque<Node<T> *> nodeQueue; ///< Queue to store nodes in post-order.
    Node<T> *current;           ///< The current node in the traversal.
    int k;


public:
    // root The root node of the tree to traverse.

    post_order_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        if (root)
        {
            push_most_left_child(root);
        }
    }
    bool hasNext() const
    {
        return !nodeQueue.empty();
    }
    Node<T> *next()
    {
        if (nodeQueue.empty())
        {
            throw out_of_range("No more elements in iterator");
        }

        current = nodeQueue.front();
        nodeQueue.pop_front();
        return current;
    }
    void push_most_left_child(Node<T> *node)
    {
        while (node)
        {
            nodeQueue.push_front(node);
            node = node->childrens.empty() ? nullptr : node->childrens.front().get();
        }
    }
    post_order_iterator<T> &operator++()
    {
        if (k > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
        {
            Node<T> *Node = nodeQueue.front();
            nodeQueue.pop_front();

            for (auto it = Node->childrens.rbegin(); it != Node->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeQueue.push_front(it->get());
                }
            }

            if (!nodeQueue.empty())
            {
                current = nodeQueue.front();
            }
            else
            {
                current = nullptr;
            }
        }
        else // if the tree is a binary tree we will do post-order traversal
        {
             if (!nodeQueue.empty()) {
                    Node<T>* node = nodeQueue.front();
                    nodeQueue.pop_front();

                    if (!nodeQueue.empty()) {
                        Node<T>* parent = nodeQueue.front();
                        bool isLastChild = false;
                        for (size_t i = 0; i < parent->childrens.size(); ++i) {
                            if (parent->childrens[i].get() == node && i == parent->childrens.size() - 1) {
                                isLastChild = true;
                                break;
                            }
                        }
                        if (!isLastChild) {
                            push_most_left_child(parent->childrens.back().get());
                        }
                    }

                    current = node;
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

    T &operator*()
    {
        try
        {
            return current->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    bool operator!=(const post_order_iterator &other) const
    {
        return (current != other.current);
    }
    Node<T> *get_current()
    {
        return current;
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
    Node<T> *get_current()
    {
        return current;
    }

    T &operator*()
    {
        try
        {
            return current->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    pre_order_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            Node<T> *node = nodeStack.top();
            nodeStack.pop();

            if (k > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
            {
                for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it)
                {
                    if (*it)
                    {
                        nodeStack.push(it->get());
                    }
                }

                if (!nodeStack.empty())
                {
                    current = nodeStack.top();
                }
                else
                {
                    current = nullptr;
                }
            }
            else // if the tree is a binary tree
            {
                for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it)
                {
                    if (*it)
                    {
                        nodeStack.push(it->get());
                    }
                }

                if (!nodeStack.empty())
                {
                    current = nodeStack.top();
                }
                else
                {
                    current = nullptr;
                }
            }
        }
        return *this;
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

public:
    in_order_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        push_most_left_child(root);
    }
    bool operator!=(const in_order_iterator &other) const
    {
        return current != other.current;
    }
    Node<T> *get_current()
    {
        return current;
    }

    // Consider returning a sentinel value (e.g., nullptr) for end of iteration
    T &operator*()
    {
        try
        {
            return current->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    void push_most_left_child(Node<T> *node)
    {
        while (node)
        {
            nodeStack.push(node);
            node = node->childrens.empty() ? nullptr : node->childrens.front().get();
        }
    }

    in_order_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            current = nodeStack.top();
            Node<T> *node = nodeStack.top();
            nodeStack.pop();

            if (k > 2)
            {
                // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
                {
                    for (auto it = node->childrens.rbegin(); it != node->childrens.rend(); ++it)
                    {
                        if (*it)
                        {
                            nodeStack.push(it->get());
                        }
                    }

                    if (!nodeStack.empty())
                    {
                        current = nodeStack.top();
                    }
                    else
                    {
                        current = nullptr;
                    }
                }
            }
            else if (current->childrens.front())
            { // Check for right child (binary tree)
                push_most_left_child(current->childrens.front().get());
            }
            current = nodeStack.empty() ? nullptr : nodeStack.top();
        }
        return *this;
    }
};

// Heap iterator
template <typename T>
class HeapIterator
{
private:
    vector<Node<T> *> heap;
    int k;
    int index;

public:
    HeapIterator(Node<T> *root, int k) :k(k)
    {
        if (k > 2)
        {
            throw invalid_argument(" Heap is only for a binary tree! ");
        }
        if (root == nullptr)
        {
            return;
        }
        heap.push_back(root);
        index = 0;
        
        // put all the nodes in the tree in a vector
        for (auto it = BFSIterator<T>(root,k); it != BFSIterator<T>(nullptr,k); ++it)
        {
            heap.push_back(it.get_current()); 
        }
        // make the vector a heap
        make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T>  *b){ return a->value > b->value; });
    }
    bool operator!=(const HeapIterator &other) const
    {
        bool answer = !(*this == other);
        return answer;
    }

    T&operator*()
    {
        try{
            return heap.at(index)->value;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    Node<T> *operator->()
    {
        return heap.at(0);
    }

    HeapIterator &operator++()
    {
        pop_heap(heap.begin(), heap.end() - index, [](Node<T> *a, Node<T> *b)
                      { return a->value > b->value; });
        index++;
        return *this;
    }

    bool operator==(const HeapIterator &other) const
    {
        return heap.size() - index== other.heap.size() - other.index;
    }
};
