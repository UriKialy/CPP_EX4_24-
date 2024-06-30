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
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
// export CPLUS_INCLUDE_PATH=/path/to/QGraphicsScene
// #include <QGraphicsEllipseItem>
// #include <QGraphicsTextItem>
// #include "complex.hpp"
using namespace std;

template <typename T>
class tree
{
private:
    Node<T> *root;
    int k; // number of childrens
public:
    tree(int k = 2) : root(nullptr), k(k) {}

    void add_root(T val)
    {
        if (root != NULL)
        {
            throw invalid_argument("Root already exists");
        }
        root = new Node<T>(val, 0);
    }
    void add_sub_node(T parent, T child)
    {
        if (child == NULL)
        {
            return; // if there is no child nothing to do
        }
        else if (parent->childrens.size() >= k)
        {
            throw invalid_argument("Parent has max childrens");
        }
        else if (parent == NULL)
        { // if there is no parent throw exception cause its invalid
            throw invalid_argument("Parent doesn't exist");
        }
        else if (root == NULL)
        { // if there is no root make the parent the root and the child the root's child
            add_root(parent);
            add_sub_node(parent, child);
        }
        else
        {
            parent->childrens.emplace_back(make_unique<Node<T>>(child, k)); // add the child to the parent's childrens
        }
    }
    int getK()
    {
        return k;
    }
    pre_order_iterator<T > begin_pre_order()
    {
        return pre_order_iterator<T>(root,k);
    }
    pre_order_iterator<T> end_pre_order()
    {
        return pre_order_iterator<T>(nullptr,k);
    }
    post_order_iterator<T> begin_post_order()
    {
        return post_order_iterator<T>(root,k);
    }
    post_order_iterator<T> end_post_order()
    {
        return post_order_iterator<T>(nullptr,k);
    }

    in_order_iterator<T> begin_in_order()
    {
        return in_order_iterator<T>(root,k);
    }

    in_order_iterator<T> end_in_order()
    {
        return in_order_iterator<T>(nullptr,k);
    }

    dfs_iterator<T> begin_dfs_scan()
    {
        return dfs_iterator<T>(root,k);
    }

    dfs_iterator<T> end_dfs_scan()
    {
        return dfs_iterator<T>(nullptr,k);
    }

    BFSIterator<T> begin_bfs_scan()
    {
        return BFSIterator<T>(root,k);
    }

    BFSIterator<T> end_bfs_scan()
    {
        return BFSIterator<T>(nullptr,k);
    }
    ~tree()
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
    // Template function to draw the tree nodes and edges
    void drawTreeNodes_Edges(sf::RenderWindow &window, Node<T> *node, sf::Vector2f position, float horizontalSpacing, float verticalSpacing)
    {
        if (!node)
            return;

        int childSize = node->children.size();
        float startAngle = -90.0f - (childSize - 1) * 15.0f;
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color(100, 100, 255));
        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
        window.draw(circle);

        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        {
            cerr << "Could not load font" << endl;
            return;
        }

        sf::Text text;
        text.setFont(font);

        ostringstream oss;
        oss << node->value;
        text.setString(oss.str());

        text.setCharacterSize(14);
        text.setFillColor(sf::Color(255, 255, 255));
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position);
        window.draw(text);


        for (int i = 0; i < childSize; ++i)
        {
            auto &child = node->children.at(i);
            if (child)
            {
                float angle = startAngle + i * 30.0f;
                float radianAngle = angle * M_PI / 180.0f;
                sf::Vector2f childPos = position + sf::Vector2f(cos(radianAngle) * horizontalSpacing, verticalSpacing);
                sf::Vertex line[] = {
                    sf::Vertex(position + sf::Vector2f(0, 20)),
                    sf::Vertex(childPos + sf::Vector2f(0, -20))};
                line->color = sf::Color(255, 165, 0);
                window.draw(line, 2, sf::Lines);

                drawTreeNodes_Edges(window, child.get(), childPos, horizontalSpacing / 2.0f, verticalSpacing * 1.2f);
            }
        }
    }

    // Template function to calculate the total levels in the tree
    int calcHight(Node<T> *node)
    {
        if (!node)
        {
            return 0;
        }
        else
        {
            int hight = 0;
            for (auto &child : node->children)
            {
                hight = max(hight, calcHight(child.get()));
            }
            return hight + 1;
        }
    }

    Node<T> *getRoot()
    {
        return root;
    }
    // Template function to draw the tree
    void drawTree(sf::RenderWindow &window)
    {
        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        {
            cerr << "Could not load font" << endl;
            return;
        }

        Node<T> *root = this->getRoot();
        int totalLevels = calcHight(root);

        sf::Vector2f startPosition(window.getSize().x / 2, 50);
        float horizontalSpacing = window.getSize().x / (pow(2, totalLevels - 1) + 1) * 2.5;
        float verticalSpacing = window.getSize().y / (totalLevels + 1) * 1.5;

        drawTreeNodes_Edges(window, root, startPosition, horizontalSpacing, verticalSpacing);
    }

    bool  operator!=(const tree<T> &other) const
    {
        return (root != other.root);
    }
};
