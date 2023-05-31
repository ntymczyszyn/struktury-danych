//
// Created by Natalia on 18.05.2023.
//

#ifndef STRUKTURY_DANYCH_NODE_S_H
#define STRUKTURY_DANYCH_NODE_S_H

#include <iostream>

template< class T >
class Node_S{
public:
    Node_S(const T& key);
    Node_S();
    ~Node_S();

    Node_S<T>* left;
    Node_S<T>* right;
    Node_S<T>* up;
    Node_S<T>* down;

    int height = 0;
    int left_distance = 0;
    T k; // value

    int compare_keys(Node_S<T>* node2);
    Node_S<T>* find(Node_S<T>* f);

    void insert_node(Node_S<T>* node2, Node_S<T>* lower, int insert_height, int distance);
    void update_distance(Node_S<T>* temp, Node_S<T>* node2); // do zmian
    void remove_node();

};




#endif//STRUKTURY_DANYCH_NODE_S_H
