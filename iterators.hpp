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
public:
    // root The root node of the tree to traverse.

    post_order_iterator(Node<T> *root, int k) : current(root), k(k)
    {
        if (root)
        {
            fillQueue(root);
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
            if (!nodeQueue.empty())
            {
                Node<T> *node = nodeQueue.front();
                nodeQueue.pop_front();
                if (!nodeQueue.empty())
                {
                    Node<T> *parent = nodeQueue.front();
                    if (parent->childrens.size() > 1 && node == parent->childrens.at(0).get())
                    {
                        pushLeftmostPath(parent->childrens[1].get());
                    }
                }
                current = node;
            }
            else
            {
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

private:
    deque<Node<T> *> nodeQueue; ///< Queue to store nodes in post-order.
    Node<T> *current;           ///< The current node in the traversal.
    int k;

    void fillQueue(Node<T> *root) // Fills the queue with nodes in post-order.
    {
        if (k > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
        {

            nodeQueue.pop_front();
            for (auto it = current->childrens.rbegin(); it != current->childrens.rend(); ++it)
            {
                if (*it)
                {
                    nodeQueue.pop_front(it->get());
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
        queue<Node<T> *> q;               ///< Queue for BFS-like traversal.
        unordered_set<Node<T> *> visited; ///< Set to track visited nodes.

        q.push(root);
        while (!q.empty())
        {
            Node<T> *node = q.front();
            q.pop();

            // Process childrens first
            bool allchildrensVisited = true;
            for (const auto &child : node->childrens)
            {
                if (child && visited.find(child.get()) == visited.end())
                {
                    q.push(child.get());
                    allchildrensVisited = false;
                }
            }

            // If all childrens are processed or the node is a leaf, add it to the result
            if (allchildrensVisited)
            {
                nodeQueue.push_front(node);
                visited.insert(node);
            }
            else
            {
                // Reinsert the node to process it later after its childrens
                q.push(node);
            }
        }
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
    std::stack<Node<T> *> nodeStack;
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
