#pragma once
#include <vector>
#include <memory>
template <typename T>
class Node
{
public:
    T value;
    vector<unique_ptr<Node<T>>> childrens;

    Node<T>::Node(T val, int k) : value(val), childrens(k) {
        if(k < 0) {
            throw invalid_argument("Number of childrens must be non-negative");
        }
    }
};
