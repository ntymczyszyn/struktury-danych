#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include "../src/SNode.cpp"
#include "SNode.h"
#include <iostream>
#include <memory>
#include <random>
#include <string>
// to nadal nie jest do końca dobrze, ale idzie w dobrym kierunku


template<class T>
class SkipList{
public:
    SkipList();
    SkipList(int height_);
    ~SkipList();

    void insert_element(const T& value);
    void remove_element(const T& value);
    int get_element_rank(const T& value);
    void show_list();

private:
    SNode<T>* find(SNode<T>* node, SNode<T>*nodeToFind);
    void insert_node(SNode<T>* node, SNode<T>*nodeToAdd, SNode<T>* lower, int insert_height, int distance);
    void update_distance(SNode<T>* node);
    void remove_node(SNode<T>* node);

    SNode<T>* head;
    int height;
    int numberOfElements;
    std::random_device rd;
    std::mt19937 rand;
};



#endif //STRUKTURY_DANYCH_SKIPLIST_H
