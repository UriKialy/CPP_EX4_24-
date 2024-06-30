#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "Complex.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Basic Operations and Iterators for tree<int>
TEST_CASE("Tree Basic Operations for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    CHECK(three_ary_tree.getRoot()->value == 1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);

    Node<int>* root = three_ary_tree.getRoot();
    CHECK(root->childrens.at(0)->value == 2);
    CHECK(root->childrens.at(1)->value == 3);
    CHECK(root->childrens.at(2)->value == 4);
}

TEST_CASE("Tree Add More than k childrens for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);
    CHECK_THROWS_AS(three_ary_tree.add_sub_node(1, 5), std::runtime_error); // Should throw an error

    Node<int>* root = three_ary_tree.getRoot();
    CHECK(root->childrens.at(0)->value == 2);
    CHECK(root->childrens.at(1)->value == 3);
    CHECK(root->childrens.at(2)->value == 4);
}

// Iterator Tests for tree<int>
TEST_CASE("BFS Iterator for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);
    three_ary_tree.add_sub_node(2, 5);
    three_ary_tree.add_sub_node(2, 6);

    std::vector<int> bfs_order = {1, 2, 3, 4, 5, 6};
    int i = 0;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);
    three_ary_tree.add_sub_node(2, 5);
    three_ary_tree.add_sub_node(2, 6);

    std::vector<int> dfs_order = {1, 2, 5, 6, 3, 4};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);
    three_ary_tree.add_sub_node(2, 5);
    three_ary_tree.add_sub_node(2, 6);

    std::vector<int> pre_order = {1, 2, 5, 6, 3, 4};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}


TEST_CASE("In-Order Iterator for int") {
    tree<int> binaryTree(2);
    binaryTree.add_root(1);
    binaryTree.add_sub_node(1, 2);
    binaryTree.add_sub_node(1, 3);
    binaryTree.add_sub_node(2, 4);
    binaryTree.add_sub_node(2, 5);

    std::vector<int> in_order = {4, 2, 5, 1, 3};
    int i = 0;
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        CHECK(*it == in_order[i]);
        ++i;
    }
}

TEST_CASE("Heap Iterator for int") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(5);
    three_ary_tree.add_sub_node(5, 3);
    three_ary_tree.add_sub_node(5, 8);
    three_ary_tree.add_sub_node(5, 7);
    three_ary_tree.add_sub_node(3, 1);
    three_ary_tree.add_sub_node(3, 2);

    std::vector<int> heap_order = {1, 2, 3, 5, 7, 8};
    int i = 0;
    for (auto it = three_ary_tree.begin_heap(); it != three_ary_tree.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}
TEST_CASE("Heap Iterator for int") {
    tree<int> binaryTree(2);
    binaryTree.add_root(5);
    binaryTree.add_sub_node(5, 3);
    binaryTree.add_sub_node(5, 8);
    binaryTree.add_sub_node(3, 1);
    binaryTree.add_sub_node(3, 2);

    std::vector<int> heap_order = {1, 2, 3, 5, 8};
    int i = 0;
    for (auto it = binaryTree.begin_heap(); it != binaryTree.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}


// Basic Operations and Iterators for tree<double>
TEST_CASE("Tree Basic Operations for double") {
    tree<double> three_ary_tree(3);
    three_ary_tree.add_root(1.1);
    CHECK(three_ary_tree.getRoot()->value == 1.1);
    three_ary_tree.add_sub_node(1.1, 2.2);
    three_ary_tree.add_sub_node(1.1, 3.3);
    three_ary_tree.add_sub_node(1.1, 4.4);

    Node<double>* root = three_ary_tree.getRoot();
    CHECK(root->childrens.at(0)->value == 2.2);
    CHECK(root->childrens.at(1)->value == 3.3);
    CHECK(root->childrens.at(2)->value == 4.4);
}

// Iterator Tests for tree<double>
TEST_CASE("BFS Iterator for double") {
    tree<double> three_ary_tree(3);
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 2.2);
    three_ary_tree.add_sub_node(1.1, 3.3);
    three_ary_tree.add_sub_node(1.1, 4.4);
    three_ary_tree.add_sub_node(2.2, 5.5);
    three_ary_tree.add_sub_node(2.2, 6.6);

    std::vector<double> bfs_order = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    int i = 0;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for double") {
    tree<double> three_ary_tree(3);
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 2.2);
    three_ary_tree.add_sub_node(1.1, 3.3);
    three_ary_tree.add_sub_node(1.1, 4.4);
    three_ary_tree.add_sub_node(2.2, 5.5);
    three_ary_tree.add_sub_node(2.2, 6.6);

    std::vector<double> dfs_order = {1.1, 2.2, 5.5, 6.6, 3.3, 4.4};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for double") {
    tree<double> three_ary_tree(3);
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 2.2);
    three_ary_tree.add_sub_node(1.1, 3.3);
    three_ary_tree.add_sub_node(1.1, 4.4);
    three_ary_tree.add_sub_node(2.2, 5.5);
    three_ary_tree.add_sub_node(2.2, 6.6);

    std::vector<double> pre_order = {1.1, 2.2, 5.5, 6.6, 3.3, 4.4};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}



TEST_CASE("Heap Iterator for double") {
    tree<double> three_ary_tree(3);
    three_ary_tree.add_root(5.5);
    three_ary_tree.add_sub_node(5.5, 3.3);
    three_ary_tree.add_sub_node(5.5, 8.8);
    three_ary_tree.add_sub_node(5.5, 7.7);
    three_ary_tree.add_sub_node(3.3, 1.1);
    three_ary_tree.add_sub_node(3.3, 2.2);

    std::vector<double> heap_order = {1.1, 2.2, 3.3, 5.5, 7.7, 8.8};
    int i = 0;
    for (auto it = three_ary_tree.begin_heap(); it != three_ary_tree.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

// Basic Operations and Iterators for tree<Complex>
TEST_CASE("Tree Basic Operations for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(1, 1));
    CHECK(three_ary_tree.getRoot()->value == Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(4, 4));

    Node<Complex>* root = three_ary_tree.getRoot();
    CHECK(root->childrens.at(0)->value == Complex(2, 2));
    CHECK(root->childrens.at(1)->value == Complex(3, 3));
    CHECK(root->childrens.at(2)->value == Complex(4, 4));
}

TEST_CASE("Tree Add More than k childrens for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    CHECK_THROWS_AS(three_ary_tree.add_sub_node(Complex(1, 1), Complex(5, 5)), std::runtime_error); // Should throw an error

    Node<Complex>* root = three_ary_tree.getRoot();
    CHECK(root->childrens.at(0)->value == Complex(2, 2));
    CHECK(root->childrens.at(1)->value == Complex(3, 3));
    CHECK(root->childrens.at(2)->value == Complex(4, 4));
}

// Iterator Tests for tree<Complex>
TEST_CASE("BFS Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> bfs_order = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6)};
    int i = 0;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> dfs_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3), Complex(4, 4)};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    three_ary_tree.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> pre_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3), Complex(4, 4)};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}



TEST_CASE("Heap Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    three_ary_tree.add_root(Complex(5, 5));
    three_ary_tree.add_sub_node(Complex(5, 5), Complex(3, 3));
    three_ary_tree.add_sub_node(Complex(5, 5), Complex(8, 8));
    three_ary_tree.add_sub_node(Complex(5, 5), Complex(7, 7));
    three_ary_tree.add_sub_node(Complex(3, 3), Complex(1, 1));
    three_ary_tree.add_sub_node(Complex(3, 3), Complex(2, 2));

    std::vector<Complex> heap_order = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(5, 5), Complex(7, 7), Complex(8, 8)};
    int i = 0;
    for (auto it = three_ary_tree.begin_heap(); it != three_ary_tree.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}
TEST_CASE("Post-Order Iterator for int") {
    tree<int> tr(2);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2); // Left child of root
    three_ary_tree.add_sub_node(1, 3); // Right child of root
    three_ary_tree.add_sub_node(2, 4); // Left child of node 2
    three_ary_tree.add_sub_node(2, 5); // Right child of node 2
    three_ary_tree.add_sub_node(3, 6); // Left child of node 3
    three_ary_tree.add_sub_node(3, 7); // Right child of node 3

    std::vector<int> post_order = {4, 5, 2, 6, 7, 3, 1};
    int i = 0;
    for (auto it = three_ary_tree.begin_post_order(); it != three_ary_tree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Post-Order Iterator Tests for tree<double>
TEST_CASE("Post-Order Iterator for double") {
    tree<double> tr(2);
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 2.2); // Left child of root
    three_ary_tree.add_sub_node(1.1, 3.3); // Right child of root
    three_ary_tree.add_sub_node(2.2, 4.4); // Left child of node 2
    three_ary_tree.add_sub_node(2.2, 5.5); // Right child of node 2
    three_ary_tree.add_sub_node(3.3, 6.6); // Left child of node 3
    three_ary_tree.add_sub_node(3.3, 7.7); // Right child of node 3

    std::vector<double> post_order = {4.4, 5.5, 2.2, 6.6, 7.7, 3.3, 1.1};
    int i = 0;
    for (auto it = three_ary_tree.begin_post_order(); it != three_ary_tree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Post-Order Iterator Tests for tree<Complex>
TEST_CASE("Post-Order Iterator for Complex") {
    tree<Complex> BinaryTree(2);
    BinaryTree.add_root(Complex(1, 1));
    BinaryTree.add_sub_node(Complex(1, 1), Complex(2, 2)); // Left child of root
    BinaryTree.add_sub_node(Complex(1, 1), Complex(3, 3)); // Right child of root
    BinaryTree.add_sub_node(Complex(2, 2), Complex(4, 4)); // Left child of node 2
    BinaryTree.add_sub_node(Complex(2, 2), Complex(5, 5)); // Right child of node 2
    BinaryTree.add_sub_node(Complex(3, 3), Complex(6, 6)); // Left child of node 3
    BinaryTree.add_sub_node(Complex(3, 3), Complex(7, 7)); // Right child of node 3

    std::vector<Complex> post_order = {Complex(4, 4), Complex(5, 5), Complex(2, 2), Complex(6, 6), Complex(7, 7), Complex(3, 3), Complex(1, 1)};
    int i = 0;
    for (auto it = BinaryTree.begin_post_order(); it != BinaryTree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Pre-Order Iterator Tests for tree<int> with k=3
TEST_CASE("Pre-Order Iterator for k-3 Tree") {
    tree<int> three_ary_tree(3);
    three_ary_tree.add_root(1);
    three_ary_tree.add_sub_node(1, 2);
    three_ary_tree.add_sub_node(1, 3);
    three_ary_tree.add_sub_node(1, 4);
    three_ary_tree.add_sub_node(2, 5);
    three_ary_tree.add_sub_node(2, 6);
    three_ary_tree.add_sub_node(3, 7);
    three_ary_tree.add_sub_node(3, 8);
    three_ary_tree.add_sub_node(4, 9);
    three_ary_tree.add_sub_node(4, 10);

    std::vector<int> pre_order = {1, 2, 5, 6, 3, 7, 8, 4, 9, 10};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}