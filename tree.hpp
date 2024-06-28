#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <type_traits>
#include "Node.hpp"
#include "iterators.hpp"
// export CPLUS_INCLUDE_PATH=/path/to/QGraphicsScene
// #include <QGraphicsEllipseItem>
// #include <QGraphicsTextItem>
// #include "complex.hpp"
using namespace std;

    template <typename T>
    class Tree
    {
    private:
        Node<T> *root;
        int k; // number of childrens
    public:
        void add_root(T val)
        {
            if (root != nullptr)
            {
                throw invalid_argument("Root already exists");
            }
            root = new Node<T>(val, 0);
        }
        void add_sub_node(T parent, T child)
        {
            if (child == nullptr)
            {
                return; // if there is no child nothing to do
            }
            else if (parent->childrens.size() >= k)
            {
                throw invalid_argument("Parent has max childrens");
            }
            else if (parent == nullptr)
            { // if there is no parent throw exception cause its invalid
                throw invalid_argument("Parent doesn't exist");
            }
            else if (root == nullptr)
            { // if there is no root make the parent the root and the child the root's child
                add_root(parent);
                add_sub_node(parent, child);
            }
            else
            {
                parent->childrens.emplace_back(unique_ptr<Node<T>>(new Node<T>(child, k))); // add the child to the parent's childrens
            }
        }
        pre_order_iterator<T> begin_pre_order()
        {
            return pre_order_iterator<T>(root);
        }
        pre_order_iterator<T> end_pre_order()
        {
            return pre_order_iterator<T>(nullptr);
        }
        post_order_iterator<T> begin_post_order()
        {
            return post_order_iterator<T>(root);
        }
        post_order_iterator<T> end_post_order()
        {
            return post_order_iterator<T>(nullptr);
        }

        in_order_iterator<T> begin_in_order()
        {
            return in_order_iterator<T>(root);
        }

        in_order_iterator<T> end_in_order()
        {
            return in_order_iterator<T>(nullptr);
        }

        dfs_iterator<T> begin_dfs_scan()
        {
            return dfs_iterator<T>(root);
        }

        dfs_iterator<T> end_dfs_scan()
        {
            return dfs_iterator<T>(nullptr);
        }

        BFSIterator<T> begin_bfs_scan()
        {
            return BFSIterator<T>(root);
        }

        BFSIterator<T> end_bfs_scan()
        {
            return BFSIterator<T>(nullptr);
        }
        ~Tree()
        {
            BFSIterator<T> it = begin_bfs_scan();
            BFSIterator<T> prev = it;
            BFSIterator<T> end = end_bfs_scan();
            while (it != end)
            {
                prev = it;
                ++it;
                prev->remove_children();
            }
            root = nullptr;
        }
    };

