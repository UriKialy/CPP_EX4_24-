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
    Node(T val) : value(val) { }
   
    void   remove_childrens()
    {
        childrens.clear();
    }
};
