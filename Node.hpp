#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;


template <typename T>
class Node
{
public:
    T value;
    vector<unique_ptr<Node<T>>> childrens;

    Node(T val, int k) : value(val), childrens(k) {
        if(k < 0) {
            throw invalid_argument("Number of childrens must be non-negative");
        }
    }
};
