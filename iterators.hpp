#pragma once
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include "Node.hpp"
using namespace std;

// bfs_iterator
template <typename T>
class BFSIterator
{
private:
    queue<Node<T> *> nodeQueue;
    Node<T> *current;

public:
    BFSIterator(Node<T> *root) : current(root)
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
            std::cerr << e.what() << '\n';
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

public:
    dfs_iterator(Node<T> *root) : current(root)
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
            std::cerr << e.what() << '\n';
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

    post_order_iterator(Node<T> *root) : current(nullptr)
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

private:
    deque<Node<T> *> nodeQueue; ///< Queue to store nodes in post-order.
    Node<T> *current;           ///< The current node in the traversal.
                                // Fills the queue with nodes in post-order.
    void fillQueue(Node<T> *root)
    {
        if (current->children.size() > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
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

            // Process children first
            bool allChildrenVisited = true;
            for (const auto &child : node->children)
            {
                if (child && visited.find(child.get()) == visited.end())
                {
                    q.push(child.get());
                    allChildrenVisited = false;
                }
            }

            // If all children are processed or the node is a leaf, add it to the result
            if (allChildrenVisited)
            {
                nodeQueue.push_front(node);
                visited.insert(node);
            }
            else
            {
                // Reinsert the node to process it later after its children
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

public:
    pre_order_iterator(Node<T> *root) : current(root)
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
            std::cerr << e.what() << '\n';
        }
    }

    pre_order_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            Node<T> *node = nodeStack.top();
            nodeStack.pop();

            if (current->children.size() > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
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
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
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

// in_order_iterator
template <typename T>
class in_oreder_iterator
{
private:
    stack<Node<T> *> nodeStack;
    Node<T> *current;

public:
    in_oreder_iterator(Node<T> *root) : current(root)
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
            std::cerr << e.what() << '\n';
        }
    }


    in_oreder_iterator<T> &operator++()
    {
        if (!nodeStack.empty())
        {
            Node<T> *node = nodeStack.top();
            nodeStack.pop();

            if (current->children.size() > 2) // if the tree is more than a binary tree i.e k-ary tree where as k>2 we will do dfs
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
                if(current->children.at(0)) // if the left child exists      
                {
                    nodeStack.push(current->children.at(0).get());
                }
                
            }
        }
        return *this;
    }

    bool operator!=(const in_oreder_iterator &other) const
    {
        return (current != other.current);
    }
};