#ifndef STRUKTURY_DANYCH_SNODE_H
#define STRUKTURY_DANYCH_SNODE_H

#include <iostream>

template< class T >
class SNode {
public:
    SNode(const T& key);
    SNode();
    ~SNode();

    SNode<T>* left;
    SNode<T>* right;
    SNode<T>* up;
    SNode<T>* down;

    int height = 0;
    int left_distance = 0;
    T k; // value

    int compare_keys(SNode<T>* node2);
    SNode<T>* find(SNode<T>* f);

    void insert_node(SNode<T>* node2, SNode<T>* lower, int insert_height, int distance);
    void update_distance(SNode<T>* temp, SNode<T>* node2); // do zmian
    void remove_node();

};



#endif//STRUKTURY_DANYCH_SNODE_H
