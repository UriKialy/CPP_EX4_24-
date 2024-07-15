#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "iterators.hpp"

// Basic Operations and Iterators for tree<int>
TEST_CASE("Tree Basic Operations for int") {
    tree<int> three_ary_tree(3);
    Node<int>* root = new Node<int>(1);
    three_ary_tree.add_root(root);
    CHECK(three_ary_tree.getRoot()->value == 1);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    CHECK(root->childrens[0]->value == 2);
    CHECK(root->childrens[1]->value == 3);
    CHECK(root->childrens[2]->value == 4);
}

TEST_CASE("Tree Add More than k childrens for int") {
    tree<int> three_ary_tree(3);
    Node<int>* root = new Node<int>(1);
    three_ary_tree.add_root(root);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
    Node<int>* child4 = new Node<int>(5);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    CHECK_THROWS_AS(three_ary_tree.add_sub_node(root, child4), std::invalid_argument); // Should throw an error of type std::invalid_argument

    CHECK(root->childrens[0]->value == 2);
    CHECK(root->childrens[1]->value == 3);
    CHECK(root->childrens[2]->value == 4);
}

// Iterator Tests for tree<int>
TEST_CASE("BFS Iterator for int") {
    tree<int> three_ary_tree(3);
    Node<int>* root = new Node<int>(1);
    three_ary_tree.add_root(root);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
    Node<int>* child4 = new Node<int>(5);
    Node<int>* child5 = new Node<int>(6);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    three_ary_tree.add_sub_node(child1, child4);
    three_ary_tree.add_sub_node(child1, child5);

    std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
    std::vector<int> actual_order;

    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
        actual_order.push_back(*it);
    }
    // Compare sizes
    CHECK(actual_order.size() == expected_order.size());

    // Compare elements
    for (size_t i = 0; i < std::min(actual_order.size(), expected_order.size()); ++i) {
        CHECK(actual_order[i] == expected_order[i]);
    }
}

TEST_CASE("DFS Iterator for int") {
     tree<int> three_ary_tree(3);
    Node<int>* root = new Node<int>(1);
    three_ary_tree.add_root(root);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
     Node<int>* child4 = new Node<int>(5);
    Node<int>* child5 = new Node<int>(6);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
     three_ary_tree.add_sub_node(child1,child4);
    three_ary_tree.add_sub_node(child1,child5);
    std::vector<int> dfs_order = {1, 2, 5, 6, 3, 4};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for int") {
      tree<int> three_ary_tree(2);
    Node<int>* root = new Node<int>(1);
    three_ary_tree.add_root(root);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
     Node<int>* child4 = new Node<int>(5);
    Node<int>* child5 = new Node<int>(6);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(child1, child3);
     three_ary_tree.add_sub_node(child1,child4);
    three_ary_tree.add_sub_node(child2,child5);

    std::vector<int> pre_order = {1, 2, 4, 5, 3, 6};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}

TEST_CASE("In-Order Iterator for int") {
    tree<int> binaryTree(2);
    Node<int>* root = new Node<int>(1);
    binaryTree.add_root(root);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    binaryTree.add_sub_node(root, child1);
    binaryTree.add_sub_node(root, child2);
    binaryTree.add_sub_node(child1, new Node<int>(4));
    binaryTree.add_sub_node(child1, new Node<int>(5));

    std::vector<int> in_order = {4, 2, 5, 1, 3};
    int i = 0;
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        CHECK(*it == in_order[i]);
        ++i;
    }
}

TEST_CASE("Heap Iterator for int") {
    tree<int> BinaryTreeInt(2);
    Node<int>* root = new Node<int>(5);
    BinaryTreeInt.add_root(root);
    Node<int>* child1 = new Node<int>(3);
    Node<int>* child2 = new Node<int>(8);
    Node<int>* child3 = new Node<int>(7);
    BinaryTreeInt.add_sub_node(root, child1);
    BinaryTreeInt.add_sub_node(root, child2);
    BinaryTreeInt.add_sub_node(child1, child3);
    BinaryTreeInt.add_sub_node(child1, new Node<int>(1));
    BinaryTreeInt.add_sub_node(child2, new Node<int>(2));

    std::vector<int> heap_order = {1, 2, 3, 5, 7, 8};
    int i = 0;
    for (auto it = BinaryTreeInt.begin_heap_scan(); it != BinaryTreeInt.end_heap_scan(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

TEST_CASE("Heap Iterator for int") {
    tree<int> binaryTree(2);
    Node<int>* root = new Node<int>(5);
    binaryTree.add_root(root);
    Node<int>* child1 = new Node<int>(3);
    Node<int>* child2 = new Node<int>(8);
    binaryTree.add_sub_node(root, child1);
    binaryTree.add_sub_node(root, child2);
    binaryTree.add_sub_node(child1, new Node<int>(1));
    binaryTree.add_sub_node(child1, new Node<int>(2));

    std::vector<int> heap_order = {1, 2, 3, 5, 8};
    int i = 0;
    for (auto it = binaryTree.begin_heap_scan(); it != binaryTree.end_heap_scan(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

// Basic Operations and Iterators for tree<double>
TEST_CASE("Tree Basic Operations for double") {
    tree<double> three_ary_tree(3);
    Node<double>* root = new Node<double>(1.1);
    three_ary_tree.add_root(root);
    CHECK(three_ary_tree.getRoot()->value == 1.1);
    Node<double>* child1 = new Node<double>(4.2);
    Node<double>* child2 = new Node<double>(6.9);
    Node<double>* child3 = new Node<double>(9.6);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);

    CHECK(root->childrens[0]->value == 4.2);
    CHECK(root->childrens[1]->value == 6.9);
    CHECK(root->childrens[2]->value == 9.6);
}

TEST_CASE("Tree Add More than k childrens for double") {
    tree<double> three_ary_tree(3);
    Node<double>* root = new Node<double>(1.1);
    three_ary_tree.add_root(root);
    Node<double>* child1 = new Node<double>(2.4);
    Node<double>* child2 = new Node<double>(4.2);
    Node<double>* child3 = new Node<double>(6.9);
     Node<double>* child4 = new Node<double>(9.6);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    CHECK_THROWS_AS(three_ary_tree.add_sub_node(root, child4), std::invalid_argument); // Should throw an error

    CHECK(root->childrens[0]->value == 2.4);
    CHECK(root->childrens[1]->value == 4.2);
    CHECK(root->childrens[2]->value == 6.9);
}


TEST_CASE("DFS Iterator for double") {
   tree<double> three_ary_tree(3);
    Node<double>* root = new Node<double>(1.1);
    three_ary_tree.add_root(root);
    Node<double>* child1 = new Node<double>(2.4);
    Node<double>* child2 = new Node<double>(4.2);
    Node<double>* child3 = new Node<double>(6.9);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    three_ary_tree.add_sub_node(child1, new Node<double>(9.9));
    three_ary_tree.add_sub_node(child1, new Node<double>(6.6));

    std::vector<double> dfs_order = {1.1, 2.4, 9.9, 6.6, 4.2, 6.9};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}



TEST_CASE("Heap Iterator for double") {
    tree<double> BinaryTreeDouble(2);
    Node<double>* root = new Node<double>(5.5);
    BinaryTreeDouble.add_root(root);
    Node<double>* child1 = new Node<double>(420.2);
    Node<double>* child2 = new Node<double>(88.8);
    Node<double>* child3 = new Node<double>(69.69);
    BinaryTreeDouble.add_sub_node(root, child1);
    BinaryTreeDouble.add_sub_node(root, child2);
    BinaryTreeDouble.add_sub_node(child1, child3);
    BinaryTreeDouble.add_sub_node(child1, new Node<double>(1.1));
    BinaryTreeDouble.add_sub_node(child2, new Node<double>(2.2));

    std::vector<double> heap_sorted = {1.1, 2.2,5.5,69.69,88.8,420.2};
    int i = 0;
    for (auto it = BinaryTreeDouble.begin_heap_scan(); it != BinaryTreeDouble.end_heap_scan(); ++it) {
        CHECK(*it == heap_sorted[i]);
        ++i;
    }
}


TEST_CASE("Tree Basic Operations for Complex") {
    tree<Complex> three_ary_tree(3);
    Node<Complex>* root = new Node<Complex>({1, 1});
    three_ary_tree.add_root(root);
    CHECK(three_ary_tree.getRoot()->value == (Complex{1, 1}));
    Node<Complex>* child1 = new Node<Complex>({20, 12});
    Node<Complex>* child2 = new Node<Complex>({3, 99});
    Node<Complex>* child3 = new Node<Complex>({4,2});
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);

    CHECK(root->childrens[0]->value == (Complex{20, 12}));
    CHECK(root->childrens[1]->value == (Complex{3, 99}));
    CHECK(root->childrens[2]->value == (Complex{4, 2}));
}


TEST_CASE("BFS Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    Node<Complex>* root = new Node<Complex>({10, 20});
    three_ary_tree.add_root(root);
    Node<Complex>* child1 = new Node<Complex>({30, 40});
    Node<Complex>* child2 = new Node<Complex>({50, 60});
    Node<Complex>* child3 = new Node<Complex>({70, 80});
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    three_ary_tree.add_sub_node(child1, new Node<Complex>({90, 100}));
    three_ary_tree.add_sub_node(child1, new Node<Complex>({110, 120}));

    vector<Complex> bfs_order = {{10, 20}, {30, 40}, {50, 60}, {70, 80}, {90, 100}, {110, 120}};
    int i = 0;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for Complex") {
    tree<Complex> three_ary_tree(3);
    Node<Complex>* root = new Node<Complex>({10, 20});
    three_ary_tree.add_root(root);
    Node<Complex>* child1 = new Node<Complex>({30, 40});
    Node<Complex>* child2 = new Node<Complex>({50, 60});
    Node<Complex>* child3 = new Node<Complex>({70, 80});
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(root, child3);
    three_ary_tree.add_sub_node(child1, new Node<Complex>({90, 100}));
    three_ary_tree.add_sub_node(child1, new Node<Complex>({110, 120}));

    vector<Complex> dfs_order = {{10, 20}, {30, 40}, {90, 100}, {110, 120}, {50, 60}, {70, 80}};
    int i = 0;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for Complex") {
    tree<Complex> three_ary_tree(2);
    Node<Complex>* root = new Node<Complex>({10, 20});
    three_ary_tree.add_root(root);
    Node<Complex>* child1 = new Node<Complex>({30, 40});
    Node<Complex>* child2 = new Node<Complex>({50, 60});
    Node<Complex>* child3 = new Node<Complex>({70, 80});
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child2);
    three_ary_tree.add_sub_node(child1, child3);
    three_ary_tree.add_sub_node(child1, new Node<Complex>({90, 100}));
    three_ary_tree.add_sub_node(child2, new Node<Complex>({110, 120}));

    vector<Complex> pre_order = {{10, 20}, {30, 40}, {70, 80}, {90, 100}, {50, 60}, {110, 120}};
    int i = 0;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}

TEST_CASE("In-Order Iterator for Complex") {
    tree<Complex> binaryTree(2);
    Node<Complex>* root = new Node<Complex>({10, 20});
    binaryTree.add_root(root);
    Node<Complex>* child1 = new Node<Complex>({30, 40});
    Node<Complex>* child2 = new Node<Complex>({50, 60});
    binaryTree.add_sub_node(root, child1);
    binaryTree.add_sub_node(root, child2);
    binaryTree.add_sub_node(child1, new Node<Complex>({70, 80}));
    binaryTree.add_sub_node(child1, new Node<Complex>({90, 100}));

    vector<Complex> in_order = {{70, 80}, {30, 40}, {90, 100}, {10, 20}, {50, 60}};
    int i = 0;
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        CHECK(*it == in_order[i]);
        ++i;
    }
}

TEST_CASE("Heap Iterator for Complex") {
    tree<Complex> BinaryTreeComlex(2);
    Node<Complex>* root = new Node<Complex>({10, 20});
    BinaryTreeComlex.add_root(root);
    Node<Complex>* child1 = new Node<Complex>({30, 40});
    Node<Complex>* child2 = new Node<Complex>({50, 60});
    Node<Complex>* child3 = new Node<Complex>({70, 80});
    BinaryTreeComlex.add_sub_node(root, child1);
    BinaryTreeComlex.add_sub_node(root, child2);
    BinaryTreeComlex.add_sub_node(child1, child3);
    BinaryTreeComlex.add_sub_node(child1, new Node<Complex>({90, 100}));
    BinaryTreeComlex.add_sub_node(child2, new Node<Complex>({110, 120}));

    vector<Complex> heap_order = {{10, 20}, {30, 40}, {50, 60},{70, 80},  {90, 100}, {110, 120}};
    int i = 0;
    for (auto it = BinaryTreeComlex.begin_heap_scan(); it != BinaryTreeComlex.end_heap_scan(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}