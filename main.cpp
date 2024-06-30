#include "Node.hpp"
#include <iostream>
using namespace std;
#include "tree.hpp" 
#include "iterators.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#include "Complex.hpp"



int main() {
    // Create a binary tree with integers
    tree<int> binaryTree(2);

    binaryTree.add_root(1);
    binaryTree.add_sub_node(1, 2); 
    binaryTree.add_sub_node(1, 3); 
    binaryTree.add_sub_node(2, 4); 
    binaryTree.add_sub_node(2, 5); 
    binaryTree.add_sub_node(3, 6); 
    binaryTree.add_sub_node(3, 7); 

    cout << "Pre-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it) {
        cout <<*it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_dfs_scan(); it != binaryTree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a binary tree with complex numbers
    tree<Complex> binaryComplexTree(2); 

    binaryComplexTree.add_root(Complex(1, 1));
    binaryComplexTree.add_sub_node(Complex(1, 1), Complex(2, 2)); 
    binaryComplexTree.add_sub_node(Complex(1, 1), Complex(3, 3)); 
    binaryComplexTree.add_sub_node(Complex(2, 2), Complex(4, 4)); 
    binaryComplexTree.add_sub_node(Complex(2, 2), Complex(5, 5)); 
    binaryComplexTree.add_sub_node(Complex(3, 3), Complex(6, 6)); 
    binaryComplexTree.add_sub_node(Complex(3, 3), Complex(7, 7)); 

    cout << "Pre-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_pre_order(); it != binaryComplexTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_post_order(); it != binaryComplexTree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_in_order(); it != binaryComplexTree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_bfs_scan(); it != binaryComplexTree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_dfs_scan(); it != binaryComplexTree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a k-3 tree with integers
    tree<int> threeAryTree(3);
    //Tree<Complex> binaryComplexTree; 


    threeAryTree.add_root(1);
    threeAryTree.add_sub_node(1, 2);
    threeAryTree.add_sub_node(1, 3);
    threeAryTree.add_sub_node(1, 4);
    threeAryTree.add_sub_node(2, 5);
    threeAryTree.add_sub_node(2, 6);
    threeAryTree.add_sub_node(3, 7);
    threeAryTree.add_sub_node(3, 8);
    threeAryTree.add_sub_node(4, 9);
    threeAryTree.add_sub_node(4, 10);

    cout << "Pre-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_pre_order(); it != threeAryTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_post_order(); it != threeAryTree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_in_order(); it != threeAryTree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_bfs_scan(); it != threeAryTree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-3 Tree): ";
    for (auto it = threeAryTree.begin_dfs_scan(); it != threeAryTree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the binary tree with integers
    sf::RenderWindow windowBinary(sf::VideoMode(1600, 1300), "Display Binary Tree"); 

    while (windowBinary.isOpen()) {
        sf::Event event;
        while (windowBinary.pollEvent(event)) {
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

    while (windowComplex.isOpen()) {
        sf::Event event;
        while (windowComplex.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowComplex.close();
        }

        windowComplex.clear(sf::Color::Black);
        binaryComplexTree.drawTree(windowComplex);
        windowComplex.display();
    }

    // Create a window to visualize the k-3 tree with integers
    sf::RenderWindow windowK3(sf::VideoMode(1600, 1300), "Display k-3 Tree"); 

    while (windowK3.isOpen()) {
        sf::Event event;
        while (windowK3.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowK3.close();
        }

        windowK3.clear(sf::Color::Black);
        threeAryTree.drawTree(windowK3);
        windowK3.display();
    }

    return 0;
}