//
// Created by antalix on 20.04.23.
//

#ifndef STRUKTURY_DANYCH_AVLTREE_H
#define STRUKTURY_DANYCH_AVLTREE_H

#include <iostream>
#include <memory>
#include "Node.h"
#include "../src/Node.cpp"

template < typename T>
class AVLtree {
public:
    AVLtree();
    ~AVLtree();
    Node<T>* root;
    int node_count;
    int height() const;
    int size() const;
    bool isEmpty() const;
    bool contains(const T& value);
    bool insert(const T& value);
    bool remove(const T& value);
    void displayBinaryTree(Node<T> *root, std::string indent, bool last);

private:
    friend class Node<T>;  // <-nie jestem pewna czy ma być

    bool contains(Node<T>* node, const T& value);
    auto insert(Node<T>* node, const T& value);
    auto remove(Node<T>* node, const T& value);

    void update(Node<T>* node);
    auto balance(Node<T>* node);
    auto left_left_case(Node<T>* node);
    auto left_right_case(Node<T>* node);
    auto right_left_case(Node<T>* node);
    auto right_right_case(Node<T>* node);
    auto left_rotation(Node<T>* node);
    auto right_rotation(Node<T>* node);
    T find_min(Node<T>* node) const;
    T find_max(Node<T>* node) const;
};


















// TODO: add iterator class
// TODO: add printing function
// TODO: add validation function

#endif //STRUKTURY_DANYCH_AVLTREE_H
