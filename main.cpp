#include "Node.hpp"
#include <iostream>
using namespace std;
#include "tree.hpp"
#include "iterators.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#include "Complex.hpp"

int main()
{
    // Create a binary tree with integers
    tree<int> binaryTree(2);
    Node<int> *root = new Node<int>(555);
    Node<int> *node1 = new Node<int>(1);
    Node<int> *node2 = new Node<int>(2);
    Node<int> *node3 = new Node<int>(3);
    Node<int> *node4 = new Node<int>(4);
    Node<int> *node5 = new Node<int>(5);
    Node<int> *node6 = new Node<int>(6);
    Node<int> *node7 = new Node<int>(7);

    binaryTree.add_root(root);
    binaryTree.add_sub_node(root, node2);
    binaryTree.add_sub_node(root, node1);
    binaryTree.add_sub_node(node1, node3);
    binaryTree.add_sub_node(node1, node4);
    binaryTree.add_sub_node(node2, node5);
    binaryTree.add_sub_node(node2, node6);
    binaryTree.add_sub_node(node3, node7);

    cout << "Pre-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_dfs_scan(); it != binaryTree.end_dfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Create a binary tree with complex numbers
    tree<Complex> binaryComplexTree(2);

    Node<Complex> *ComplexRoot = new Node<Complex>(Complex(1, 1));
    Node<Complex> *nodeC1 = new Node<Complex>(Complex(1, 2));
    Node<Complex> *nodeC2 = new Node<Complex>(Complex(2, 2));
    Node<Complex> *nodeC3 = new Node<Complex>(Complex(3, 3));
    Node<Complex> *nodeC4 = new Node<Complex>(Complex(4, 4));
    Node<Complex> *nodeC5 = new Node<Complex>(Complex(5, 5));
    Node<Complex> *nodeC6 = new Node<Complex>(Complex(6, 6));
    Node<Complex> *nodeC7 = new Node<Complex>(Complex(7, 7));

    binaryComplexTree.add_root(ComplexRoot);
    binaryComplexTree.add_sub_node(nodeC1, nodeC2);
    binaryComplexTree.add_sub_node(nodeC1, nodeC3);
    binaryComplexTree.add_sub_node(nodeC2, nodeC4);
    binaryComplexTree.add_sub_node(nodeC2, nodeC5);
    binaryComplexTree.add_sub_node(nodeC3, nodeC6);
    binaryComplexTree.add_sub_node(nodeC3, nodeC7);

    cout << "Pre-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_pre_order(); it != binaryComplexTree.end_pre_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_post_order(); it != binaryComplexTree.end_post_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_in_order(); it != binaryComplexTree.end_in_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_bfs_scan(); it != binaryComplexTree.end_bfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_dfs_scan(); it != binaryComplexTree.end_dfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Create a k-3 tree with integers
    tree<int> threeAryTree(3);
    // Tree<Complex> binaryComplexTree;

    
    Node<int> *Troot = new Node<int>(1);
    Node<int> *nodeT1 = new Node<int>(1);
    Node<int> *nodeT2 = new Node<int>(2);
    Node<int> *nodeT3 = new Node<int>(3);
    Node<int> *nodeT4 = new Node<int>(4);
    Node<int> *nodeT5 = new Node<int>(5);
    Node<int> *nodeT6 = new Node<int>(6);
    Node<int> *nodeT7 = new Node<int>(7);
    Node<int> *nodeT8 = new Node<int>(8);
    Node<int> *nodeT9 = new Node<int>(9);
    Node<int> *nodeT10 = new Node<int>(10);

    threeAryTree.add_root(Troot);
    threeAryTree.add_sub_node(nodeT1, nodeT2);
    threeAryTree.add_sub_node(nodeT1, nodeT3);
    threeAryTree.add_sub_node(nodeT1, nodeT4);
    threeAryTree.add_sub_node(nodeT2, nodeT5);
    threeAryTree.add_sub_node(nodeT2, nodeT6);
    threeAryTree.add_sub_node(nodeT3, nodeT7);
    threeAryTree.add_sub_node(nodeT3, nodeT8);
    threeAryTree.add_sub_node(nodeT4, nodeT9);
    threeAryTree.add_sub_node(nodeT4, nodeT10);

    cout << "Pre-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_pre_order(); it != threeAryTree.end_pre_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_post_order(); it != threeAryTree.end_post_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_in_order(); it != threeAryTree.end_in_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_bfs_scan(); it != threeAryTree.end_bfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_dfs_scan(); it != threeAryTree.end_dfs_scan(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the binary tree with integers
    sf::RenderWindow windowBinary(sf::VideoMode(1600, 1300), "Display Binary Tree");

    while (windowBinary.isOpen())
    {
        sf::Event event;
        while (windowBinary.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowBinary.close();
        }

        windowBinary.clear(sf::Color::Black);
        // Call drawTree function for Tree<int>
        binaryTree.drawTree(windowBinary);
        windowBinary.display();
    }

    // Create a window to visualize the binary tree with complex numbers
    sf::RenderWindow windowComplex(sf::VideoMode(1600, 1300), "Display Binary Complex Tree");

    while (windowComplex.isOpen())
    {
        sf::Event event;
        while (windowComplex.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowComplex.close();
        }

        windowComplex.clear(sf::Color::Black);
        binaryComplexTree.drawTree(windowComplex);
        windowComplex.display();
    }

    // Create a window to visualize the k-3 tree with integers
    sf::RenderWindow windowK3(sf::VideoMode(1600, 1300), "Display k-3 Tree");

    while (windowK3.isOpen())
    {
        sf::Event event;
        while (windowK3.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowK3.close();
        }

        windowK3.clear(sf::Color::Black);
        threeAryTree.drawTree(windowK3);
        windowK3.display();
    }

    return 0;
}